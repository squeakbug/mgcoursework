#ifndef EBO_SETUPER
#define EBO_SETUPER

#include <vector>

#include "base_objects/vertex.h"

class EBOSetuper
{
public:
    virtual void setupEBO(std::vector<std::size_t> &ebo) = 0;

    virtual ~EBOSetuper() = 0;
};

#endif