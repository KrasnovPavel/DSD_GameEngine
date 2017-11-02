//
// Created by pavel on 11/1/17.
//

#ifndef DSD_GAMEENGINE_LOGGEROUTPUT_H
#define DSD_GAMEENGINE_LOGGEROUTPUT_H

#include <string>

class LoggerOutput
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

    explicit LoggerOutput(const LoggerOutput::OutputType& outputType)
    {
        m_outputType = outputType;
    }

    explicit LoggerOutput(const std::string& fileName)
    {
        m_outputType = FILE;
        m_fileName = fileName;
    }

    const LoggerOutput::OutputType& GetOutputType() const
    {
        return m_outputType;
    }

    const std::string& GetFileName() const
    {
        return m_fileName;
    }

private:
    LoggerOutput::OutputType m_outputType;
    std::string m_fileName;
};


#endif //DSD_GAMEENGINE_LOGGEROUTPUT_H
