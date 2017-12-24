//
// Created by Pavel Krasnov (krasnovpavel0@gmail.com) on 01.11.2017.
//

#ifndef DSD_GAMEENGINE_LOGGEROUTPUT_H
#define DSD_GAMEENGINE_LOGGEROUTPUT_H

#include <exception>
#include <string>

/**
 * @addtogroup Logger
 * @{
 */

/**
 * @brief "File not specified" exception
 */
class FileNameNotSpecified: public std::exception
{
    const char* what() const throw() override
    {
        return "File name not specified";
    }
};

/**
 * @brief Class defining output stream
 */
class LoggerOutput
{
public:
    /// Defines where to log message
    enum Type
    {
        FILE, ///< Log to file
        STDOUT, ///< Log to std::cout
        STDERR, ///< Log to std::cerr
        LOG_SCREEN, ///< Log to special created log screen
        MAIN_SCREEN ///< Log to program main screen
    };

    /**
     * @brief Constructor
     * @param outputType Defines where to log message
     * @param fileName Specifies file to log if necessary
     * @throw FileNameNotSpecified If outputType == FILE, but file wasn't specified
     */
    explicit LoggerOutput(const LoggerOutput::Type& outputType, const std::string& fileName = std::string())
    {
        m_outputType = outputType;
        m_fileName = fileName;
        if (m_outputType == FILE && m_fileName.empty()) throw FileNameNotSpecified();
    }

    /**
     * @brief Returns where to log message
     */
    const LoggerOutput::Type& outputType() const
    {
        return m_outputType;
    }

    /**
     * @brief Returns name of file to log if specified
     */
    const std::string& fileName() const
    {
        return m_fileName;
    }

private:
    LoggerOutput::Type m_outputType;
    std::string m_fileName;
};

/**
 * @}
 */

#endif //DSD_GAMEENGINE_LOGGEROUTPUT_H
