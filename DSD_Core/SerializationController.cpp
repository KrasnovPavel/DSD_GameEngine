//
// Created by Pavel Krasnov (krasnovpavel0@gmail.com) on 05/11/2017.
//

#include "SerializationController.h"

std::unordered_map<unsigned, DSDBaseObject* const> SerializationController::m_objects;
unsigned SerializationController::m_counter = 1;
WriteByteArray SerializationController::m_warray(0);
//std::vector<std::size_t> SerializationController::m_creators;

const WriteByteArray&  SerializationController::Serialize()
{
    m_warray.reset(sizeOfObjects());
    for (auto& obj: m_objects)
    {
        obj.second->Serialize(m_warray);
    }
    return m_warray;
}

void SerializationController::Deserialize(ReadByteArray& data)
{
    for (auto& obj: m_objects)
    {
        obj.second->Deserialize(data);
    }
}

unsigned long SerializationController::AddSerializableObject(DSDBaseObject *const object)
{
    m_objects.insert(std::make_pair(m_counter, object));
    ++m_counter;
    return m_counter - 1;
}

void SerializationController::RemoveSerializableObject(DSDBaseObject *const object)
{

}

std::size_t SerializationController::sizeOfObjects()
{
    std::size_t result = sizeof(unsigned) * m_objects.size(); //TODO: count deleting object
    for (auto& obj: m_objects)
    {
        result += obj.second->SerializedSize();
    }
    return result;
}
