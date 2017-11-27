//
// Created by Pavel Krasnov (krasnovpavel0@gmail.com) on 13.11.17.
//

#include "FileController.h"

void FileController::writeToFile(std::string filename, const WriteByteArray &data)
{
    std::ofstream out(filename, std::ios::out|std::ios::binary);
    if (out.is_open())
    {
        out.write(data.data(), data.length());
        out.close();
    }
    else throw (FileOpeningFaliure(filename));
}

ReadByteArray FileController::readFromFile(std::string filename)
{
    std::ifstream in(filename, std::ios::ate|std::ios::in|std::ios::binary);
    if (in.is_open())
    {
        auto size = in.tellg();
        char* data = new char[size];
        in.seekg(0, std::ios::beg);
        in.read(data, size);
        in.close();
        return ReadByteArray(data, (std::size_t)size);
    }
    else throw (FileOpeningFaliure(filename));
}
