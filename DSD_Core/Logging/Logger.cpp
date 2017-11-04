//
// Created by Pavel Krasnov (krasnovpavel0@gmail.com) on 31/10/2017.
//
#include <ctime>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <thread>
#include "Logger.h"

std::unordered_map<std::string, std::ofstream> Logger::m_files;
std::thread Logger::m_thread = std::thread(LoggerControl);
std::queue<typename Logger::LoggingData> Logger::m_tasks;
std::mutex Logger::m_mutex;
bool Logger::m_wantJoin = false;
std::condition_variable Logger::m_CV;
LoggerTimestamp::Type Logger::m_timestampType = LoggerTimestamp::ENGINE_LOCAL_TIME;

void Logger::Log(const std::string &message,
                 const LoggerMessageType &messageType,
                 const LoggerOutput &output)
{
    // We don't want to fall if thread was closed
    if (!m_thread.joinable())
    {
        m_wantJoin = false;
        m_thread = std::thread(LoggerControl);
    }
    m_mutex.lock();
    m_tasks.push(LoggingData(message, LoggerTimestamp(m_timestampType), messageType, output));
    m_mutex.unlock();
    m_CV.notify_one();
}

void Logger::Write(const std::string &message, const LoggerOutput &output)
{
    switch (output.outputType())
    {
        case LoggerOutput::STDOUT:
            std::cout << message << std::endl;
            break;
        case LoggerOutput::STDERR:
            std::cerr << message << std::endl;
            break;
        case LoggerOutput::FILE:
            WriteToFile(message, output.fileName());
            break;
        default:
            std::cerr << "Not create yet!" << std::endl; //TODO: make logging for graphics mode
            break;
    }

}

const std::string &Logger::GetMessageTypeString(const LoggerMessageType &messageType)
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

void Logger::WriteToFile(const std::string &message, const std::string& fileName)
{
    PrepareFile(fileName) << message << std::endl;
}

std::ofstream &Logger::PrepareFile(const std::string &filename)
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

void Logger::LogInThread(const LoggingData& data)
{
    Write("[" + data.m_time.GetString() + "] " +
          GetMessageTypeString(data.m_messageType) +
          ": " + data.m_message, data.m_output);
}

void Logger::JoinThread()
{
    m_wantJoin = true;
    m_thread.join();
}

void Logger::LoggerControl()
{
    while (!m_wantJoin || !m_tasks.empty())
    {
        std::unique_lock<std::mutex> locker(m_mutex);
        while(m_tasks.empty()) m_CV.wait(locker);

        while (!m_tasks.empty())
        {
            LogInThread(m_tasks.front());
            m_tasks.pop();
        }
    }
}

void Logger::SetTimestampType(LoggerTimestamp::Type timestampType)
{
    m_timestampType = timestampType;
}
