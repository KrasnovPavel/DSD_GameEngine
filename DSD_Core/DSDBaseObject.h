//
// Created by Pavel Krasnov (krasnovpavel0@gmail.com) on 30/10/2017.
//

#ifndef DSD_GAMEENGINE_DSDBASEOBJECT_H
#define DSD_GAMEENGINE_DSDBASEOBJECT_H

#include <functional>
#include <string>
#include <utility>
#include <vector>

#include "Logging/Logger.h"
#include "ReadByteArray.h"
#include "WriteByteArray.h"

#define serializable(varType, varName, varInit) varType varName = AddVar \
    ( \
        [this](WriteByteArray& data) \
            { \
                data.write<varType>((varName)); \
            }, \
        [this](ReadByteArray& data) \
            { \
                (varName) = data.read<varType>(); \
            }, \
        [this]()->std::size_t \
            { \
                return varSize((varName)); \
            }, \
        varInit \
    )

typedef std::function<void(WriteByteArray&)> s_func;
typedef std::function<void(ReadByteArray&)>  d_func;
typedef std::function<std::size_t()> sizeof_func;

class SerializationController;

class DSDBaseObject
{
    friend SerializationController;

public:
    virtual std::string ToString() const
    {
        return "{}";
    }

    void LogObject(const LoggerMessageType& messageType = LoggerMessageType::INFORMATION,
                   const LoggerOutput& output = LoggerOutput(LoggerOutput::STDOUT)) const
    {
        Logger::Log(ToString(), messageType, output);
    }

    std::size_t SerializedSize()
    {
        std::size_t result = sizeof(unsigned);
        for (auto& func: m_sizeofFunctions)
        {
            result += func();
        }
        return result;
    }

protected:
    template <typename t>
    t AddVar(s_func serializationFunction, d_func deserializationFunction, sizeof_func sizeofFunction, t varInit)
    {
        m_serializationFunctions.push_back(serializationFunction);
        m_deserializationFunctions.push_back(deserializationFunction);
        m_sizeofFunctions.push_back(sizeofFunction);
        return varInit;
    }

    template <typename t>
    std::size_t varSize(t& var);

    void Serialize(WriteByteArray& data) const
    {
        for (auto sFunc: m_serializationFunctions)
        {
            sFunc(data);
        }
    }

    void Deserialize(ReadByteArray& data)
    {
        for (auto dFunc: m_deserializationFunctions)
        {
            dFunc(data);
        }
    }

    std::vector<s_func> m_serializationFunctions{};
    std::vector<d_func> m_deserializationFunctions{};
    std::vector<sizeof_func> m_sizeofFunctions{};
};

template <typename t>
std::size_t DSDBaseObject::varSize(t& var)
{
    return sizeof(t);
};

template <>
std::size_t DSDBaseObject::varSize(std::string& var)
{
    return var.size() + 1;
};

//template <>
//std::size_t DSDBaseObject::varSize(std::vector& var)
//{
//    return (var.size()==0)?0:var.size()*sizeof(var[0]);
//};

#endif //DSD_GAMEENGINE_DSDBASEOBJECT_H
