#include <iostream>
#include "DSD_Core/DSDObject.h"

class Obj : public DSDObject
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
