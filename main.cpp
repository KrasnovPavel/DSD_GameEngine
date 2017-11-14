#include <string>
#include <thread>
#include <iostream>

#include "DSD_Core/DSDBaseObject.h"
#include "DSD_Core/FileController.h"
#include "DSD_Core/SerializationController.h"

class Vector : public DSDBaseObject
{
public:
    Vector() : m_x(0), m_y(0), m_z(0) {}

    Vector(Vector &&other)
    {
        m_x = other.x();
        m_y = other.y();
        m_z = other.z();
    }

    Vector(const double& x, const double& y, const double& z)
    {
        m_x = x;
        m_y = y;
        m_z = z;
    }

    std::string ToString() const override
    {
        std::string result;
        result.reserve(100);
        result.append("Vector{");
        result.append(std::to_string(m_x));
        result.append(" ");
        result.append(std::to_string(m_y));
        result.append(" ");
        result.append(std::to_string(m_z));
        result.append("}");
        return result;
    }

    const double& x() const
    {
        return m_x;
    }

    const double& y() const
    {
        return m_y;
    }

    const double& z() const
    {
        return m_z;
    }

    const Vector& operator=(const Vector& other)
    {
        m_x = other.x();
        m_y = other.y();
        m_z = other.z();
        return *this;
    }

private:
    serializable(double, m_x, 0);
    serializable(double, m_y, 0);
    serializable(double, m_z, 0);
};

class Obj : public DSDBaseObject
{
public:
    void set(const std::string& name, const Vector& vec)
    {
        this->name = name;
        this->vec = vec;
    }

    std::string ToString() const override
    {
        return name + "{" + vec.ToString() + "}";
    }

private:
    serializable(std::string, name, "");
    serializable(Vector, vec, Vector());
};

int main()
{
    Obj o;
    o.set("Obj", Vector(5.5, 100000180.564, 1212.1351578));
    std::chrono::steady_clock::time_point t = std::chrono::steady_clock::now();
    std::cout << o.ToString() << std::endl;
    SerializationController::AddSerializableObject(&o);
    FileController::writeToFile("test.sav", SerializationController::Serialize());
    o.set("", Vector());
    std::cout << o.ToString() << std::endl;
    ReadByteArray rarr = FileController::readFromFile("test.sav");
    SerializationController::Deserialize(rarr);
    std::cout << o.ToString() << std::endl;

    auto nt = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::steady_clock::now() - t);

    std::cout << nt.count() << std::endl;

//    Logger::JoinThread();

    return 0;
}
