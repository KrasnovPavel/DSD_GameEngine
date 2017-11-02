//
// Created by pavel on 10/31/17.
//
#include <ctime>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <thread>
#include "Logger.h"

template <class T>
std::chrono::time_point<std::chrono::steady_clock> Logger<T>::m_initTimePoint = std::chrono::steady_clock::now();
template <class T>
std::unordered_map<std::string, std::ofstream> Logger<T>::m_files;
template <class T>
std::thread Logger<T>::m_thread;
template <class T>
std::queue<typename Logger<T>::LoggingData> Logger<T>::m_Tasks;
template <class T>
std::mutex Logger<T>::m_mutex;
template <class T>
bool Logger<T>::m_wantJoin = false;
template <class T>
bool Logger<T>::m_isFirstTime = true;
template <class T>
std::condition_variable Logger<T>::m_CV;

template <>
void Logger<EngineLocalTime>::Log(const std::string &message,
                                  const LoggerMessageType &messageType,
                                  const LoggerOutput &output)
{
    auto time = std::chrono::steady_clock::now() - m_initTimePoint;
    AddTask(LoggingData(message, time, messageType, output));
}

template <>
void Logger<GlobalTime>::Log(const std::string &message,
                             const LoggerMessageType &messageType,
                             const LoggerOutput &output)
{
    auto time = std::chrono::system_clock::now();
    AddTask(LoggingData(message, time, messageType, output));
}

template <class T>
void Logger<T>::Write(const std::string &message, const LoggerOutput &output)
{
    switch (output.GetOutputType())
    {
        case LoggerOutput::STDOUT:
            std::cout << message << std::endl;
            break;
        case LoggerOutput::STDERR:
            std::cerr << message << std::endl;
            break;
        case LoggerOutput::FILE:
            WriteToFile(message, output.GetFileName());
            break;
        default:
            std::cerr << "Not create yet!" << std::endl; //TODO: make logging for graphics mode
            break;
    }

}

template <class T>
const std::string &Logger<T>::GetMessageTypeString(const LoggerMessageType &messageType)
{
    static std::string mType;
    switch (messageType)
    {
        case LoggerMessageType::INFORMATION:
            mType = "Info";
            break;
        case LoggerMessageType::WARNING:
            mType = "Warning";
            break;
        case LoggerMessageType::ERROR:
            mType = "Error";
            break;
    }
    return mType;
}

template <class T>
void Logger<T>::WriteToFile(const std::string &message, const std::string& fileName)
{
    PrepareFile(fileName) << message << std::endl;
}

template <>
std::string Logger<EngineLocalTime>::TimeToString(const EngineLocalTime& engineLocalTime)
{
    auto diffM = std::chrono::duration_cast<std::chrono::minutes>(engineLocalTime);
    auto diffH = std::chrono::duration_cast<std::chrono::hours>(engineLocalTime);

    std::string result = std::to_string(diffH.count()) + ":" +
                         std::to_string(diffM.count()) + ":" +
                         std::to_string(engineLocalTime.count());

    return result;
}

template <>
std::string Logger<GlobalTime>::TimeToString(const GlobalTime& globalTime)
{
    std::time_t time = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    char str[25];
    std::strftime(str, sizeof(str), "%F %T", localtime(&time));
    return std::string(str);
}

template <class T>
std::ofstream &Logger<T>::PrepareFile(const std::string &filename)
{
    if (m_files.find(filename) == m_files.end())
    {
        m_files.insert(std::make_pair(filename, std::ofstream()));
        std::ofstream& stream = m_files.at(filename);
        stream.open(filename);
        return stream;
    }
    else
    {
        return m_files.at(filename);
    }
}

template <class T>
void Logger<T>::LogInThread(const LoggingData& data)
{
    std::string timestamp;
    timestamp = TimeToString(data.m_time);
    Write("[" + timestamp + "] " + GetMessageTypeString(data.m_messageType) + ": " + data.m_message, data.m_output);
}

template <>
void Logger<EngineLocalTime>::JoinThread()
{
    m_wantJoin = true;
    if (m_thread.joinable() && !m_isFirstTime) m_thread.join();
}

template <>
void Logger<GlobalTime>::JoinThread()
{
    m_wantJoin = true;
    if (m_thread.joinable() && !m_isFirstTime) m_thread.join();
}

template <class T>
void Logger<T>::LoggerControl()
{
    while (!m_wantJoin || !m_Tasks.empty())
    {
        std::unique_lock<std::mutex> locker(m_mutex);
        while(m_Tasks.empty()) m_CV.wait(locker);

        while (!m_Tasks.empty())
        {
            LogInThread(m_Tasks.front());
            m_Tasks.pop();
        }
    }
}

template <class T>
void Logger<T>::AddTask(const LoggingData &data)
{
    if (m_isFirstTime)
    {
        m_thread = std::thread(LoggerControl);
        m_isFirstTime = false;
    }
    m_mutex.lock();
    m_Tasks.push(data);
    m_mutex.unlock();
    m_CV.notify_one();
}
