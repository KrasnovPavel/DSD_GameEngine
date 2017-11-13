//
// Created by Pavel Krasnov (krasnovpavel0@gmail.com) on 13.11.17.
//

#ifndef DSD_GAMEENGINE_FILECONTROLLER_H
#define DSD_GAMEENGINE_FILECONTROLLER_H

#include <exception>
#include <fstream>
#include <string>

#include "ReadByteArray.h"
#include "WriteByteArray.h"

class FileOpeningFaliure : public std::exception
{
public:
    explicit FileOpeningFaliure(std::string filename)
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

class FileController
{
public:
    static void writeToFile(std::string filename, const WriteByteArray& data);
    static ReadByteArray readFromFile(std::string filename);

};


#endif //DSD_GAMEENGINE_FILECONTROLLER_H
