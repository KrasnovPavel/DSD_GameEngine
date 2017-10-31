#include <iostream>
#include "DSD_Core/DSDBaseObject.h"

class Obj : public DSDBaseObject
{
public:
    std::string ToString() const override
    {
        return "Hello, world!";
    }
};

int main()
{
    Obj o;

    std::cout << o.ToString() << std::endl;

    return 0;
}
