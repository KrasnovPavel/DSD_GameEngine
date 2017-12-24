//
// Created by Pavel Krasnov (krasnovpavel0@gmail.com) on 17.12.17.
//

#ifndef DSD_GAMEENGINE_MESHPARCERSTL_H
#define DSD_GAMEENGINE_MESHPARCERSTL_H

#include "MeshParcer.h"

#include <string>
#include <sstream>

class MeshParcerSTL : public MeshParcer
{
public:
    explicit MeshParcerSTL(const std::string &filename);

    std::vector<Triangle> parce() const override;

private:
    mutable std::stringstream m_ss;
};


#endif //DSD_GAMEENGINE_MESHPARCERSTL_H
