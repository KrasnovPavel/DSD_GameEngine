//
// Created by Pavel Krasnov (krasnovpavel0@gmail.com) on 10/30/17.
//

#ifndef DSD_GAMEENGINE_DSDOBJECT_H
#define DSD_GAMEENGINE_DSDOBJECT_H

#include <string>

class DSDBaseObject
{
public:
    virtual std::string ToString() const = 0;
};


#endif //DSD_GAMEENGINE_DSDOBJECT_H
