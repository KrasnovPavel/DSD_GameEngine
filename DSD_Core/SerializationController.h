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

typedef std::function<DSDBaseObject*()> creator;

class SerializationController
{
public:
    void AddSerializableObject(DSDBaseObject* object);
    void AddSerializableObject(DSDBaseObject* object, const unsigned& ID);
    void RemoveSerializableObject(DSDBaseObject* object);
    const WriteByteArray& Serialize();
    void Deserialize(ReadByteArray& data);
    const std::vector<DSDBaseObject*>& newObjects();
    const std::vector<DSDBaseObject*>& objectsToRemove();

private:
    void RemoveObject(const unsigned& ID);
    std::size_t sizeOfObjects();
    std::unordered_map<unsigned, DSDBaseObject*> m_objects{};
    unsigned m_counter = 1;
    WriteByteArray m_warray;
    std::vector<DSDBaseObject*> m_newObjects{};
    std::vector<DSDBaseObject*> m_objectsToRemove{};
    std::vector<unsigned> m_removedObjects{};
};

#endif //DSD_GAMEENGINE_SERIALIZATIONCONTROLLER_H
