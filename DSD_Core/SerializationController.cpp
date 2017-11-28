//
// Created by Pavel Krasnov (krasnovpavel0@gmail.com) on 05/11/2017.
//

#include "SerializationController.h"

unsigned SerializationController::m_counter = 1;

const WriteByteArray& SerializationController::serialize()
{
    m_warray.reset(sizeOfObjects());
    m_warray.write<unsigned>(m_counter);
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

void SerializationController::deserialize(ReadByteArray& data)
{
    m_newObjects.clear();
    m_objectsToRemove.clear();
    m_counter = data.read<unsigned>();
    std::size_t count = data.read<std::size_t>();
    for (int i = 0; i < count; ++i)
    {
        removeObject(data.read<unsigned>());
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
            DSDBaseObject* obj = ObjectRegistrator::instantiateByID(classID);
            addSerializableObject(obj);
            obj->deserialize(data);
            m_newObjects.push_back(obj);
        }
    }
}

void SerializationController::addSerializableObject(DSDBaseObject * object)
{
    unsigned ID = object->objectID();
    if (ID == 0)
    {
        object->setObjectID(m_counter);
        ID = m_counter;
    }
    m_objects.insert(std::make_pair(ID, object));
    m_counter = (m_counter>ID)?m_counter:(ID+1);
}

void SerializationController::removeSerializableObject(DSDBaseObject * object)
{
    m_removedObjects.push_back(object->objectID());
    object->setObjectID(0); // TODO:
    m_objects.erase(object->objectID());
}

std::size_t SerializationController::sizeOfObjects()
{
    std::size_t result = 12 + (m_removedObjects.size() << 2) + (m_objects.size() << 3); //TODO: count deleting object
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

void SerializationController::removeObject(const unsigned &ID)
{
    if (m_objects.count(ID) > 0)
    {
        DSDBaseObject * obj = m_objects.at(ID);
        m_objectsToRemove.push_back(obj);
        obj->setObjectID(0);
        m_objects.erase(ID);
    }
}
