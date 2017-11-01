//
// Created by Pavel Krasnov (krasnovpavel0@gmail.com) on 10/30/17.
//

#ifndef DSD_GAMEENGINE_DSDOBJECT_H
#define DSD_GAMEENGINE_DSDOBJECT_H

#include <string>

#include "Logging/DSDLogger.h"

class DSDBaseObject
{
public:
    virtual std::string ToString() const = 0;

    void LogObject(const DSDLoggerMessageType& messageType = DSDLoggerMessageType::INFORMATION,
                   const DSDLoggerOutput& output = DSDLoggerOutput(DSDLoggerOutput::STDOUT)) const
    {
        DSDLogger::Log(ToString(), messageType, output);
    }
};


#endif //DSD_GAMEENGINE_DSDOBJECT_H
