//
// Created by pavel on 10/31/17.
//

#ifndef DSD_GAMEENGINE_DSDLOGGER_H
#define DSD_GAMEENGINE_DSDLOGGER_H

#include <chrono>
#include <condition_variable>
#include <fstream>
#include <mutex>
#include <string>
#include <queue>
#include <unordered_map>

#include "LoggerOutput.h"

enum class LoggerMessageType
{
    INFORMATION,
    WARNING,
    ERROR
};

typedef std::chrono::duration<double> EngineLocalTime;
typedef std::chrono::system_clock::time_point GlobalTime;

template <class T = EngineLocalTime>
class Logger
{
public:
    static void Log(const std::string &message,
                    const LoggerMessageType &messageType = LoggerMessageType::INFORMATION,
                    const LoggerOutput &output = LoggerOutput(LoggerOutput::STDOUT));

    static void JoinThread();

private:
    static void Write(const std::string &message, const LoggerOutput &output);

    static const std::string &GetMessageTypeString(const LoggerMessageType &messageType);

    static void WriteToFile(const std::string &message, const std::string &fileName);

    static std::string TimeToString(const T& time);

    static std::ofstream& PrepareFile(const std::string& filename);

    static std::chrono::time_point<std::chrono::steady_clock> m_initTimePoint;
    static std::unordered_map<std::string, std::ofstream> m_files;

    //Multithreading

    class LoggingData
    {
    public:
        LoggingData(const std::string& message,
                    const T& time,
                    const LoggerMessageType& messageType,
                    const LoggerOutput& output)
        : m_message(message), m_time(time), m_messageType(messageType), m_output(output) {}

        const std::string m_message;
        const T m_time;
        const LoggerMessageType m_messageType;
        const LoggerOutput m_output;
    };

    static void LogInThread(const LoggingData& data);
    static void LoggerControl();
    static void AddTask(const LoggingData &data);
    static std::mutex m_mutex;
    static std::thread m_thread;
    static bool m_wantJoin, m_isFirstTime;
    static std::queue<LoggingData> m_Tasks;
    static std::condition_variable m_CV;
};

#endif //DSD_GAMEENGINE_DSDLOGGER_H
