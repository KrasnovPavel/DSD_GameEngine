#include <string>
#include <thread>
#include <iostream>

#include "DSD_Core/DSDBaseObject.h"
#include "DSD_Core/FileController.h"
#include "DSD_Core/SerializationController.h"

class Vector : public DSDBaseObject
{
    REFLECTION(Vector);
public:
    Vector() : Vector(0.0,0.0,0.0) {}

    Vector(Vector &&other) noexcept
    {
        m_objectID = other.objectID();
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

    std::string toString() const override
    {
        return "(" + std::to_string(classID()) + ":" + std::to_string(objectID())
                + "){" + std::to_string(m_x) + " " + std::to_string(m_y)
                + " " + std::to_string(m_z) + "}";
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

    Vector& operator=(const Vector& other)
    {
        m_x = other.x();
        m_y = other.y();
        m_z = other.z();
        return *this;
    }

    void set(double x, double y, double z)
    {
        m_x = x;
        m_y = y;
        m_z = z;
    }

private:
    SERIALIZABLE(double, m_x, 0);
    SERIALIZABLE(double, m_y, 0);
    SERIALIZABLE(double, m_z, 0);
};
INIT_REFLECTION(Vector);

class Obj : public DSDBaseObject
{
    REFLECTION(Obj);
public:
    Obj() {}

    Obj(Obj&& other) noexcept
    {
        m_objectID = other.objectID();
        m_name = other.name();
        m_vec = other.vec();
    }

    void set(const std::string& name, const Vector& vec)
    {
        m_name = name;
        m_vec = vec;
    }

    const std::string& name() const
    {
        return m_name;
    }

    const Vector& vec() const
    {
        return m_vec;
    }

    std::string toString() const override
    {
        return m_name + "(" + std::to_string(classID()) + ":" + std::to_string(objectID()) + "){" + m_vec.toString() + "}";
    }

private:
    SERIALIZABLE(std::string, m_name, "");
    SERIALIZABLE(Vector, m_vec, Vector());
};
INIT_REFLECTION(Obj);

int main()
{
    SerializationController sc;
    Obj o, o1;
    Vector v;
    o.set("Obj", Vector(5.5, 100000180.564, 1212.1351578));
    o1.set("Obj1", Vector(55.5, 100180.564, 1212.1));
    std::chrono::steady_clock::time_point t = std::chrono::steady_clock::now();
    sc.addSerializableObject(&o);
    sc.addSerializableObject(&o1);
    sc.addSerializableObject(&v);
    FileController::writeToFile("test.sav", sc.serialize());
    o.set("", Vector());
    o1.set("", Vector());
    v.set(0,0,0);
    ReadByteArray rarr = FileController::readFromFile("test.sav");
    sc.deserialize(rarr);
    o.logObject();
    o1.logObject();
    v.logObject();
    sc.removeSerializableObject(&o);
    FileController::writeToFile("test.sav", sc.serialize());
    Logger::Log("Removing");
    ReadByteArray rarr1 = FileController::readFromFile("test.sav");
    sc.deserialize(rarr1);
    std::vector<DSDBaseObject*> r = sc.objectsToRemove();
    for (auto* ob: r)
    {
        ob->logObject();
    }

    std::vector<DSDBaseObject*> newObjects = sc.newObjects();

    auto nt = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::steady_clock::now() - t);

    std::cout << nt.count() << std::endl;

    Logger::JoinThread();

    return 0;
}
