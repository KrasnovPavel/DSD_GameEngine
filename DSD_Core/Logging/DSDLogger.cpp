//
// Created by pavel on 10/31/17.
//
#include <ctime>
#include <fstream>
#include <iomanip>
#include <iostream>
#include "DSDLogger.h"

DSDLoggerTimestampType DSDLogger::m_timestampType = DSDLoggerTimestampType::ENGINE_LOCAL_TIME;
std::chrono::time_point<std::chrono::steady_clock> DSDLogger::m_initTimePoint = std::chrono::steady_clock::now();

void DSDLogger::Log(const std::string &message,
                    const DSDLoggerMessageType &messageType,
                    const DSDLoggerOutput &output)
{
    std::string timestamp;

    switch (m_timestampType)
    {
        case DSDLoggerTimestampType::ENGINE_LOCAL_TIME:
            timestamp = GetEngineLocalTimeString();
            break;
        case DSDLoggerTimestampType::GLOBAL_TIME:
            timestamp = GetGlobalTimeString();
            break;
    }

    Write("[" + timestamp + "] " + GetMessageTypeString(messageType) + ": " + message, output);
}

void DSDLogger::Write(const std::string &message, const DSDLoggerOutput &output)
{
    switch (output.GetOutputType())
    {
        case DSDLoggerOutput::STDOUT:
            std::cout << message << std::endl;
            break;
        case DSDLoggerOutput::STDERR:
            std::cerr << message << std::endl;
            break;
        case DSDLoggerOutput::FILE:
            WriteToFile(message, output.GetFileName());
            break;
        default:
            std::cerr << "Not create yet!" << std::endl; //TODO: make logging for graphics mode
            break;
    }

}

const std::string &DSDLogger::GetMessageTypeString(const DSDLoggerMessageType &messageType)
{
    static std::string mType;
    switch (messageType)
    {
        case DSDLoggerMessageType::INFORMATION:
            mType = "Info";
            break;
        case DSDLoggerMessageType::WARNING:
            mType = "Warning";
            break;
        case DSDLoggerMessageType::ERROR:
            mType = "Error";
            break;
    }
    return mType;
}

void DSDLogger::WriteToFile(const std::string &message, const std::string& fileName)
{
    std::ofstream outputFile;   //TODO: Do not open file every time
    outputFile.open(fileName);
    outputFile << message << std::endl;
    outputFile.close();
}

std::string DSDLogger::GetEngineLocalTimeString()
{
    std::chrono::duration<double> diffS = std::chrono::steady_clock::now() - m_initTimePoint;
    auto diffM = std::chrono::duration_cast<std::chrono::minutes>(std::chrono::steady_clock::now() - m_initTimePoint);
    auto diffH = std::chrono::duration_cast<std::chrono::hours>(std::chrono::steady_clock::now() - m_initTimePoint);

    std::string result = std::to_string(diffH.count()) + ":" +
                         std::to_string(diffM.count()) + ":" +
                         std::to_string(diffS.count());

    return result;
}

std::string DSDLogger::GetGlobalTimeString()
{
    std::time_t time = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    char str[25];
    std::strftime(str, sizeof(str), "%F %T", localtime(&time));
    return std::string(str);
}
