#include <string>
#include <thread>
#include <iostream>

#include "DSD_Core/DSDBaseObject.h"
#include "DSD_Core/FileController.h"
#include "DSD_Core/SerializationController.h"


int main()
{
    SerializationController sc;

    FileController::writeToFile("test.sav", sc.serialize());

    ReadByteArray rarr = FileController::readFromFile("test.sav");
    sc.deserialize(rarr);

    std::vector<DSDBaseObject*> newObjects = sc.newObjects();

    Logger::JoinThread();

    return 0;
}
