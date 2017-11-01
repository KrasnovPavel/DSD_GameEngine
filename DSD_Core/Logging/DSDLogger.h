//
// Created by pavel on 10/31/17.
//

#ifndef DSD_GAMEENGINE_DSDLOGGER_H
#define DSD_GAMEENGINE_DSDLOGGER_H

#include <chrono>
#include <fstream>
#include <string>
#include <unordered_map>

class DSDLoggerOutput
{
public:
    enum OutputType
    {
        FILE,
        STDOUT,
        STDERR,
        LOG_SCREEN,
        MAIN_SCREEN
    };

    explicit DSDLoggerOutput(const DSDLoggerOutput::OutputType& outputType)
    {
        m_outputType = outputType;
    }

    explicit DSDLoggerOutput(const std::string& fileName)
    {
        m_outputType = FILE;
        m_fileName = fileName;
    }

    const DSDLoggerOutput::OutputType& GetOutputType() const
    {
        return m_outputType;
    }

    const std::string& GetFileName() const
    {
        return m_fileName;
    }

private:
    DSDLoggerOutput::OutputType m_outputType;
    std::string m_fileName;

};

enum class DSDLoggerMessageType
{
    INFORMATION,
    WARNING,
    ERROR
};

enum class DSDLoggerTimestampType
{
    ENGINE_LOCAL_TIME,
    GLOBAL_TIME
};

class DSDLogger // TODO: Launch in separate thread
{
public:
    static void Log(const std::string &message,
                    const DSDLoggerMessageType &messageType = DSDLoggerMessageType::INFORMATION,
                    const DSDLoggerOutput &output = DSDLoggerOutput(DSDLoggerOutput::STDOUT));

    static void SetTimestampType(const DSDLoggerTimestampType timestampType)
    {
        m_timestampType = timestampType;
    };

private:
    static void Write(const std::string &message, const DSDLoggerOutput &output);

    static const std::string &GetMessageTypeString(const DSDLoggerMessageType &messageType);

    static void WriteToFile(const std::string &message, const std::string &fileName);

    static std::string GetEngineLocalTimeString();

    static std::string GetGlobalTimeString();

    static std::ofstream& PrepareFile(const std::string& filename);

    static DSDLoggerTimestampType m_timestampType;
    static std::chrono::time_point<std::chrono::steady_clock> m_initTimePoint;
    static std::unordered_map<std::string, std::ofstream> m_files;
};

#endif //DSD_GAMEENGINE_DSDLOGGER_H
