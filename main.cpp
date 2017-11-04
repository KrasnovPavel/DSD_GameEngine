#include <string>
#include <thread>
#include <iostream>
#include "DSD_Core/DSDBaseObject.h"

class Obj : public DSDBaseObject
{
public:
    std::string ToString() const override
    {
        return "Obj{Hello, world!}";
    }
};

int main()
{
    Obj o;
    std::chrono::steady_clock::time_point t = std::chrono::steady_clock::now();
    Logger::Log("Hello, world!");
    std::this_thread::__sleep_for(std::chrono::seconds{10},std::chrono::nanoseconds{2});
    Logger::Log("Error msg", LoggerMessageType::ERROR, LoggerOutput(LoggerOutput::STDERR));
    Logger::Log("Log to file output.txt", LoggerMessageType::WARNING, LoggerOutput(LoggerOutput::FILE, "output.txt"));

    o.LogObject();
    auto nt = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::steady_clock::now() - t);

    std::cout << nt.count() << std::endl;

    Logger::JoinThread();

    return 0;
}
