#include <string>
#include <thread>
#include <iostream>
#include "DSD_Core/DSDBaseObject.h"
#include "DSD_Core/SerializationController.h"

class Obj : public DSDBaseObject
{
public:
    std::string ToString() const override
    {
        return "{" + std::to_string(x) + " " + std::to_string(y) + " " + std::to_string(z) + "}";
    }
    void set(double x, double y, double z)
    {
        this->x = x;
        this->y = y;
        this->z = z;
    }

private:
    serializable(double, x, 0);
    serializable(double, y, 0);
    serializable(double, z, 0);
};

int main()
{
    Obj o;
    o.set(5.5, 100000180.564, 1212.1351578);
    std::chrono::steady_clock::time_point t = std::chrono::steady_clock::now();
    o.LogObject();
    SerializationController::AddSerializableObject(&o);
    WriteByteArray arr = SerializationController::Serialize();
    o.set(0, 0, 0);
    o.LogObject();
    ReadByteArray rarr(arr.data(), arr.length());
    SerializationController::Deserialize(rarr);
    o.LogObject();

    auto nt = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::steady_clock::now() - t);

    std::cout << nt.count() << std::endl;

    Logger::JoinThread();

    return 0;
}
