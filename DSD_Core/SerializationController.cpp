//
// Created by Pavel Krasnov (krasnovpavel0@gmail.com) on 05/11/2017.
//

#include "SerializationController.h"

const WriteByteArray& SerializationController::Serialize()
{
    m_warray.reset(sizeOfObjects());
    m_warray.write<std::size_t>(m_removedObjects.size());
    for (auto& obj: m_removedObjects)
    {
        m_warray.write<unsigned>(obj);
    }
    for (auto& obj: m_objects)
    {
        m_warray.write<unsigned>(obj.first);
        m_warray.write<unsigned>(obj.second->classID());
        obj.second->serialize(m_warray);
    }
    m_removedObjects.clear();
    return m_warray;
}

void SerializationController::Deserialize(ReadByteArray& data)
{
    m_newObjects.clear();
    m_objectsToRemove.clear();
    std::size_t count = data.read<std::size_t>();
    for (int i = 0; i < count; ++i)
    {
        RemoveObject(data.read<unsigned>());
    }
    while (!data.isFinished())
    {
        unsigned number = data.read<unsigned>();
        unsigned classID = data.read<unsigned>();
        if (m_objects.count(number) > 0)
        {
            if (m_objects.at(number)->classID() == classID)
            {
                m_objects.at(number)->deserialize(data);
            }
            else
            {
//                TODO: Error message
            }
        }
        else
        {
            AddSerializableObject(ObjectRegistrator::instantiateByID(classID), number);
            m_newObjects.back()->deserialize(data);
        }
    }
}

void SerializationController::AddSerializableObject(DSDBaseObject * object)
{
    object->setObjectID(m_counter);
    m_objects.insert(std::make_pair(m_counter, object));
    ++m_counter;
}

void SerializationController::AddSerializableObject(DSDBaseObject *object, const unsigned &ID)
{
    m_newObjects.push_back(object);
    object->setObjectID(ID);
    m_objects.insert(std::make_pair(ID, object));
    m_counter = (m_counter>ID)?m_counter:(ID+1);
}

void SerializationController::RemoveSerializableObject(DSDBaseObject * object)
{
    m_removedObjects.push_back(object->objectID());
    object->setObjectID(0);
    m_objects.erase(object->objectID());
}

std::size_t SerializationController::sizeOfObjects()
{
    std::size_t result = 8 + (m_removedObjects.size() << 2) + (m_objects.size() << 3); //TODO: count deleting object
    for (auto& obj: m_objects)
    {
        result += obj.second->serializedSize();
    }
    return result;
}


const std::vector<DSDBaseObject*>& SerializationController::newObjects()
{
    return m_newObjects;
}

const std::vector<DSDBaseObject*>& SerializationController::objectsToRemove()
{
    return m_objectsToRemove;
}

void SerializationController::RemoveObject(const unsigned &ID)
{
    DSDBaseObject * obj = m_objects.at(ID);
    m_objectsToRemove.push_back(obj);
    obj->setObjectID(0);
    m_objects.erase(ID);
}
