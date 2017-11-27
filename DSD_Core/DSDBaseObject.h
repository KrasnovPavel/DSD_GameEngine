//
// Created by Pavel Krasnov (krasnovpavel0@gmail.com) on 30/10/2017.
//

#ifndef DSD_GAMEENGINE_DSDBASEOBJECT_H
#define DSD_GAMEENGINE_DSDBASEOBJECT_H

#include <functional>
#include <string>
#include <type_traits>
#include <utility>
#include <vector>

#include "Logging/Logger.h"
#include "ReadByteArray.h"
#include "WriteByteArray.h"

#define serializable(varType, varName, varInit) varType varName = AddVar \
    ( \
        [this](WriteByteArray& data) \
            { \
                serializeVar((varName), data); \
            }, \
        [this](ReadByteArray& data) \
            { \
                deserializeVar((varName), data); \
            }, \
        [this]()->std::size_t \
            { \
                return varSize((varName)); \
            }, \
        varInit \
    )

#define REFLECTION(className) \
    private: \
        const static unsigned m_classID; \
    public: \
        static DSDBaseObject* createInstance();\
        virtual const unsigned& classID() const override \
        { \
            return className::m_classID; \
        } \
    private:


#define INIT_REFLECTION(className) \
    DSDBaseObject* className::createInstance() {return new className(); }; \
    const unsigned className::m_classID = ObjectRegistrator::registry(&className::createInstance);

typedef std::function<void(WriteByteArray&)> s_func;
typedef std::function<void(ReadByteArray&)>  d_func;
typedef std::function<std::size_t()> sizeof_func;

class DSDBaseObject;

class ObjectRegistrator
{
public:
    static const unsigned registry(DSDBaseObject*(*creator)())
    {
        classCreators.push_back(creator);
        return classCreators.size() - 1;
    }
    static DSDBaseObject* instantiateByID(unsigned ID)
    {
        return classCreators.at(ID)();
    }
private:
    static std::vector<DSDBaseObject*(*)()> classCreators;
};
std::vector<DSDBaseObject*(*)()> ObjectRegistrator::classCreators{};

/**
 * @defgroup Core
 * @brief Core library for the engine
 * @{
 */

/**
 * @brief Base class for engine hierarchy
 */
class DSDBaseObject
{
private:
    template <typename T>
    static constexpr bool isA = std::is_base_of<DSDBaseObject, T>() &&
                                                std::is_convertible<T, DSDBaseObject>();
    const static unsigned m_classID;
public:
    DSDBaseObject() {}
    DSDBaseObject(DSDBaseObject&& other)
    {
        m_objectID = other.objectID();
    }
    /**
     * @brief Represents class data as std::string
     * @return string reprisents class data
     */
    virtual std::string toString() const
    {
        return "{}";
    }

    virtual void logObject(const LoggerMessageType& type = LoggerMessageType::INFORMATION,
                           const LoggerOutput& output = LoggerOutput(LoggerOutput::STDOUT))
    {
        Logger::Log(toString(), type, output);
    }

    /**
     * @brief Calculate size in bytes for this class serialized data.
     * @return size in bytes for this class serialized data
     */
    std::size_t serializedSize()
    {
        std::size_t result = 0;
        for (auto& func: m_sizeofFunctions)
        {
            result += func();
        }
        return result;
    }

    /**
     * @brief Serializes this class.
     * @param [out] data Variable where serialized data will be written
     */
    void serialize(WriteByteArray& data) const
    {
        for (auto sFunc: m_serializationFunctions)
        {
            sFunc(data);
        }
    }

    /**
     * @brief Deserializes data to this class.
     * @param [in] data Data for deserialization
     */
    void deserialize(ReadByteArray& data)
    {
        for (auto dFunc: m_deserializationFunctions)
        {
            dFunc(data);
        }
    }

    virtual const unsigned& classID() const
    {
        return DSDBaseObject::m_classID;
    }

    static DSDBaseObject* createInstance()
    {
        return new DSDBaseObject();
    }

    const unsigned& objectID() const
    {
        return m_objectID;
    }

    void setObjectID(const unsigned& newID)
    {
        m_objectID = newID;
    }

protected:
    /**
     * @brief Serializes only given variable
     * @tparam T Type of variable
     * @param var Variable for serialization
     * @param [out] data Variable where serialized data will be written
     */
    template <typename T, std::enable_if_t<!(isA<T>)>* = nullptr>
    void serializeVar(const T& var, WriteByteArray& data)
    {
        data.write<T>(var);
    }

    template <typename T, std::enable_if_t<isA<T>>* = nullptr>
    void serializeVar(const T& var, WriteByteArray& data)
    {
        var.serialize(data);
    }

    /**
     * @brief Deserializes only one variable
     * @tparam T Type of variable
     * @param var Variable for deserialization
     * @param data Data for deserialization 
     */
    template <typename T, std::enable_if_t<!(isA<T>)>* = nullptr>
    void deserializeVar(T& var, ReadByteArray& data)
    {
        var = data.read<T>();
    }

    template <typename T, std::enable_if_t<isA<T>>* = nullptr>
    void deserializeVar(T& var, ReadByteArray& data)
    {
        var.deserialize(data);
    }

    template <typename t>
    t AddVar(s_func serializationFunction, d_func deserializationFunction, sizeof_func sizeofFunction, t varInit)
    {
        m_serializationFunctions.push_back(serializationFunction);
        m_deserializationFunctions.push_back(deserializationFunction);
        m_sizeofFunctions.push_back(sizeofFunction);
        return varInit;
    }

    template <typename T, std::enable_if_t<isA<T>>* = nullptr>
    std::size_t varSize(T& var)
    {
        return var.serializedSize();
    }

    template <typename T, std::enable_if_t<!(isA<T>)>* = nullptr>
    std::size_t varSize(T& var)
    {
        return sizeof(T);
    }

    std::vector<s_func> m_serializationFunctions{};
    std::vector<d_func> m_deserializationFunctions{};
    std::vector<sizeof_func> m_sizeofFunctions{};
    unsigned m_objectID;
};

const unsigned DSDBaseObject::m_classID = ObjectRegistrator::registry(&DSDBaseObject::createInstance);

template <>
std::size_t DSDBaseObject::varSize(std::string& var)
{
    return var.size() + sizeof(std::size_t);
};

/**
 * @}
 */

#endif //DSD_GAMEENGINE_DSDBASEOBJECT_H
