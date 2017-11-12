//
// Created by Pavel Krasnov (krasnovpavel0@gmail.com) on 05/11/2017.
//

#ifndef DSD_GAMEENGINE_SERIALIZATIONCONTROLLER_H
#define DSD_GAMEENGINE_SERIALIZATIONCONTROLLER_H

#include <unordered_map>
#include <utility>
#include <vector>

#include "DSDBaseObject.h"
#include "ReadByteArray.h"
#include "WriteByteArray.h"

class SerializationController
{
public:
    static unsigned long AddSerializableObject(DSDBaseObject* object);
    static void RemoveSerializableObject(DSDBaseObject* object);
    static const WriteByteArray& Serialize();
    static void Deserialize(ReadByteArray& data);

private:
    static std::size_t sizeOfObjects();
    static std::unordered_map<unsigned, DSDBaseObject* const> m_objects;
    static unsigned m_counter;
    static WriteByteArray m_warray;
    //static std::vector<std::size_t> m_creators;
};

#endif //DSD_GAMEENGINE_SERIALIZATIONCONTROLLER_H
