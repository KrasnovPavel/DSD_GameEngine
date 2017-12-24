//
// Created by Pavel Krasnov (krasnovpavel0@gmail.com) on 13.11.17.
//

#ifndef DSD_GAMEENGINE_FILECONTROLLER_H
#define DSD_GAMEENGINE_FILECONTROLLER_H

#include <fstream>
#include <string>

#include "Core/Exceptions.h"
#include "ReadByteArray.h"
#include "WriteByteArray.h"

/**
 * @addtogroup Serialization
 * @{
 */

/**
 * @brief The FileController class
 * @details Class for reading and writing Serialised data form/in file.
 */
class FileController
{
public:
    /**
     * @brief writeToFile Writes given byte array @a data in file
     * @param filename File to write
     * @param data Data to write
     */
    static void writeToFile(std::string filename, const WriteByteArray& data);

    /**
     * @brief readFromFile Reads byte array from file
     * @param filename File to read from
     * @return Byte array
     */
    static ReadByteArray readFromFile(std::string filename);
};

/**
 * @}
 */

#endif //DSD_GAMEENGINE_FILECONTROLLER_H
