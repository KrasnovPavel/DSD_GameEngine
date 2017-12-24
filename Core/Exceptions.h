//
// Created by Pavel Krasnov (krasnovpavel0@gmail.com) on 17.12.17.
//

#ifndef DSD_GAMEENGINE_EXCEPTIONS_H
#define DSD_GAMEENGINE_EXCEPTIONS_H

#endif //DSD_GAMEENGINE_EXCEPTIONS_H

#include <exception>
#include <string>

/**
 * @brief The FileOpeningFaliure class
 */
class FileOpeningFaliure : public std::exception
{
public:
    explicit FileOpeningFaliure(const std::string& filename)
    {
        m_str = "Unable to open file: " + filename;
    }

    const char *what() const noexcept override
    {
        return m_str.c_str();
    }

private:
    std::string m_str;
};


/**
 * @brief The FileFormatError class
 *
 * @details This exception throws if file format isn't supported.
 */
class FileFormatError : public std::exception
{
public:
    explicit FileFormatError(const std::string& filename)
    {   //TODO: list of supported formats
        m_str = "Format of: " + filename + "is not supported. \n Supported formats:\n ASCII STL.";
    }

    const char *what() const noexcept override
    {
        return m_str.c_str();
    }

private:
    std::string m_str;
};


/**
 * @brief The FileParcingError class
 *
 * @details This exception throws if program can't parce file.
 */
class FileParcingError : public std::exception
{
public:
    explicit FileParcingError(const std::string& filename, const std::string& errorName = "")
    {   //TODO: list of supported formats
        m_str = "Error" + (!errorName.empty()?" \""+errorName+"\"":"") + " occurred while parcing: " + filename;
    }

    const char *what() const noexcept override
    {
        return m_str.c_str();
    }

private:
    std::string m_str;
};