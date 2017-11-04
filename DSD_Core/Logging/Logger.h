//
// Created by Pavel Krasnov (krasnovpavel0@gmail.com) on 31/10/2017.
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
#include "LoggerTimestamp.h"

/**
 * @defgroup Logger Logger
 * @brief Multithreading logging library
 * @{
 */

/**
 *  @brief Defines importance of message
 */
enum class LoggerMessageType
{
    INFORMATION, ///< Information message
    WARNING, ///< Warning message
    ERROR ///< Error message
};

/**
 * @brief Class for logging data
 * @details Class implements
 */
class Logger
{
public:
    /**
     * @brief Logs given message
     *
     * Prints given message in output stream in format:
     * "[timestamp] messageType: message"
     * @param message string to log
     * @param messageType importance of message
     * @param output where to log message
     */
    static void Log(const std::string &message,
                    const LoggerMessageType &messageType = LoggerMessageType::INFORMATION,
                    const LoggerOutput &output = LoggerOutput(LoggerOutput::STDOUT));

    /**
     * @brief Waits until all messages have written and joins thread
     *
     * Please use it only in main() after all code
     */
    static void JoinThread();

    /**
     * @brief Sets timestamp format using for all messages
     *
     * By default Logger timestamp type is ENGINE_LOCAL_TIME
     * @param timestampType
     */
    static void SetTimestampType(LoggerTimestamp::Type timestampType);

private:
    static void Write(const std::string &message, const LoggerOutput &output);

    static const std::string &GetMessageTypeString(const LoggerMessageType &messageType);

    static void WriteToFile(const std::string &message, const std::string &fileName);

    static std::ofstream& PrepareFile(const std::string& filename);

    static std::unordered_map<std::string, std::ofstream> m_files;

    static LoggerTimestamp::Type m_timestampType;

    //Multithreading

    class LoggingData
    {
    public:
        LoggingData(const std::string& message,
                    const LoggerTimestamp& time,
                    const LoggerMessageType& messageType,
                    const LoggerOutput& output)
        : m_message(message), m_time(time), m_messageType(messageType), m_output(output) {}

        const std::string m_message;
        const LoggerTimestamp m_time;
        const LoggerMessageType m_messageType;
        const LoggerOutput m_output;
    };

    static void LogInThread(const LoggingData& data);
    static void LoggerControl();
    static std::mutex m_mutex;
    static std::thread m_thread;
    static bool m_wantJoin;
    static std::queue<LoggingData> m_tasks;
    static std::condition_variable m_CV;
};

/**
 * @}
 */
#endif //DSD_GAMEENGINE_DSDLOGGER_H
