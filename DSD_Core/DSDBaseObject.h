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

//#include "Logging/Logger.h"
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

typedef std::function<void(WriteByteArray&)> s_func;
typedef std::function<void(ReadByteArray&)>  d_func;
typedef std::function<std::size_t()> sizeof_func;


class DSDBaseObject
{
private:
    template <typename T>
    static constexpr bool isA = std::is_base_of<DSDBaseObject, T>() &&
                                                std::is_convertible<T, DSDBaseObject>();

public:
    ~DSDBaseObject()
    {
        m_deserializationFunctions.clear();
        m_serializationFunctions.clear();
        m_sizeofFunctions.clear();
    }

    virtual std::string ToString() const
    {
        return "{}";
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

protected:
    template <typename T, std::enable_if_t<!(isA<T>)>* = nullptr>
    void serializeVar(const T& var, WriteByteArray& data)
    {
        data.write<T>(var);
    }

    template <typename T, std::enable_if_t<isA<T>>* = nullptr>
    void serializeVar(const T& var, WriteByteArray& data)
    {
        var.Serialize(data);
    }

    template <typename T, std::enable_if_t<!(isA<T>)>* = nullptr>
    void deserializeVar(T& var, ReadByteArray& data)
    {
        var = data.read<T>();
    }

    template <typename T, std::enable_if_t<isA<T>>* = nullptr>
    void deserializeVar(T& var, ReadByteArray& data)
    {
        var.Deserialize(data);
    }

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

    std::vector<s_func> m_serializationFunctions{};
    std::vector<d_func> m_deserializationFunctions{};
    std::vector<sizeof_func> m_sizeofFunctions{};
};

template <typename t>
std::size_t DSDBaseObject::varSize(t& var)
{
    return sizeof(t);
}

template <>
std::size_t DSDBaseObject::varSize(DSDBaseObject& var)
{
    return var.SerializedSize();
}

template <>
std::size_t DSDBaseObject::varSize(std::string& var)
{
    return var.size() + sizeof(std::size_t);
};

#endif //DSD_GAMEENGINE_DSDBASEOBJECT_H
