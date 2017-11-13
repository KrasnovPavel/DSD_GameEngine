#include <string>
#include <thread>
#include <iostream>

#include "DSD_Core/DSDBaseObject.h"
#include "DSD_Core/FileController.h"
#include "DSD_Core/SerializationController.h"

class Obj : public DSDBaseObject
{
public:
    std::string ToString() const override
    {
        return name + "{" + std::to_string(x) + " " + std::to_string(y) + " " + std::to_string(z) + "}";
    }

    void set(const std::string& name, double x, double y, double z)
    {
        this->name = name;
        this->x = x;
        this->y = y;
        this->z = z;
    }

private:
    serializable(std::string, name, "");
    serializable(double, x, 0);
    serializable(double, y, 0);
    serializable(double, z, 0);
};

int main()
{
    Obj o;
//    o.set("Obj", 5.5, 100000180.564, 1212.1351578);
    std::chrono::steady_clock::time_point t = std::chrono::steady_clock::now();
//    std::cout << o.ToString() << std::endl;
    SerializationController::AddSerializableObject(&o);
//    FileController::writeToFile("test.sav", SerializationController::Serialize());
    o.set("null", 0, 0, 0);
    std::cout << o.ToString() << std::endl;
    ReadByteArray rarr = FileController::readFromFile("test.sav");
    SerializationController::Deserialize(rarr);
    std::cout << o.ToString() << std::endl;

    auto nt = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::steady_clock::now() - t);

    std::cout << nt.count() << std::endl;

//    Logger::JoinThread();

    return 0;
}
