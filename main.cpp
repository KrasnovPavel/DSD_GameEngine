#include <string>
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
    DSDLogger::SetTimestampType(DSDLoggerTimestampType::GLOBAL_TIME);
    DSDLogger::Log("Hello, world!");
    DSDLogger::Log("Error msg", DSDLoggerMessageType::ERROR, DSDLoggerOutput(DSDLoggerOutput::STDERR));
    DSDLogger::Log("Log to file output.txt", DSDLoggerMessageType::WARNING, DSDLoggerOutput("output.txt"));

    Obj o;
    o.LogObject();

    return 0;
}
