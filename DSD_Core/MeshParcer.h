//
// Created by Pavel Krasnov (krasnovpavel0@gmail.com) on 17.12.17.
//

#ifndef DSD_GAMEENGINE_MESHPARCER_H
#define DSD_GAMEENGINE_MESHPARCER_H

#include <fstream>
#include <string>
#include <vector>

#include "Exceptions.h"
#include "Triangle.h"

class MeshParcer
{
public:
    explicit MeshParcer(const std::string& filename);

    virtual ~MeshParcer();

    virtual std::vector<Triangle> parce() const = 0;

protected:
    bool checkFormat() const;

    char* m_data;
    std::size_t m_dataSize;

    std::string m_format, m_filename;
};

#endif //DSD_GAMEENGINE_MESHPARCER_H
