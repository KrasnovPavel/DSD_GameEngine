//
// Created by Pavel Krasnov (krasnovpavel0@gmail.com) on 11.12.17.
//

#include "DSDBaseObject.h"

using namespace DSD;

std::vector<DSDBaseObject*(*)()> ObjectRegistrator::classCreators{};
const unsigned DSDBaseObject::m_classID = ObjectRegistrator::registry(&DSDBaseObject::createInstance);
