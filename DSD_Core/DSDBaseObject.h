//
// Created by Pavel Krasnov (krasnovpavel0@gmail.com) on 30/10/2017.
//

#ifndef DSD_GAMEENGINE_DSDOBJECT_H
#define DSD_GAMEENGINE_DSDOBJECT_H

#include <string>

#include "Logging/Logger.h"

class DSDBaseObject
{
public:
    virtual std::string ToString() const = 0;

    void LogObject(const LoggerMessageType& messageType = LoggerMessageType::INFORMATION,
                   const LoggerOutput& output = LoggerOutput(LoggerOutput::STDOUT)) const
    {
        Logger::Log(ToString(), messageType, output);
    }
};


#endif //DSD_GAMEENGINE_DSDOBJECT_H
