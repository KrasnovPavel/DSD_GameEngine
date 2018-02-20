//
// Created by Pavel Krasnov (krasnovpavel0@gmail.com) on 05/11/2017.
//

#ifndef DSD_GAMEENGINE_SERIALIZATIONCONTROLLER_H
#define DSD_GAMEENGINE_SERIALIZATIONCONTROLLER_H

#include <unordered_map>
#include <utility>
#include <vector>

#include "Core/DSDBaseObject.h"
#include "ReadByteArray.h"
#include "WriteByteArray.h"

namespace DSD
{
    typedef std::function<DSDBaseObject *()> creator;

/**
 * @defgroup Serialization
 * @brief Classes for serialization implementation
 * @{
 */

    /**
     * @brief The SerializationController class
     * @details Does all serialisation and deserialization.
     */
    class SerializationController
    {
    public:
        /**
         * @brief addSerializableObject Add new @a object for serialization.
         * @details This @a object will be automaticaly serialized and deserialized
         * when functions SerializationController::serialize() and
         * SerializationController::deserialize(ReadByteArray& data) called.
         * New ID will be assigned to this @a object if it has no one.
         * @param object
         */
        void addSerializableObject(DSDBaseObject *object);

        /**
         * @brief removeSerializableObject Removes object
         * @details Removes @a object previously added by
         * SerializationController::addSeializableObject(DSDBaseObject* object)
         * function. If @a object removed from all SerializationController instanties
         * then @a object ID will be set to 0.
         * @param object
         */
        void removeSerializableObject(DSDBaseObject *object);

        /**
         * @brief serialize Serialises all objects
         * @details Serialises all objects previously added by
         * SerializationController::addSeializableObject(DSDBaseObject* object)
         * function.
         * @return
         */
        const WriteByteArray &serialize();

        /**
         * @brief deserialize Deserialises given @class ReadByteArray
         * @details This function can instantiate new objects,
         * and remove objects if needed.
         * @param data
         */
        void deserialize(ReadByteArray &data);

        /**
         * @brief newObjects Objects were added by
         * SerialisationController::deserialize(ReadByteArray& data) function.
         * @return
         */
        const std::vector<DSDBaseObject *> &newObjects();

        /**
         * @brief objectsToRemove Objects were removed by
         * SerialisationController::deserialize(ReadByteArray& data) function.
         * @return
         */
        const std::vector<DSDBaseObject *> &objectsToRemove();

    private:
        void removeObject(const unsigned &ID);

        std::size_t sizeOfObjects();

        std::unordered_map<unsigned, DSDBaseObject *> m_objects{};
        static unsigned m_counter;
        WriteByteArray m_warray;
        std::vector<DSDBaseObject *> m_newObjects{};
        std::vector<DSDBaseObject *> m_objectsToRemove{};
        std::vector<unsigned> m_removedObjects{};
    };
}
/**
 * @}
 */

#endif //DSD_GAMEENGINE_SERIALIZATIONCONTROLLER_H
