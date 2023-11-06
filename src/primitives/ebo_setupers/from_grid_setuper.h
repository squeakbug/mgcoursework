#ifndef FROM_GRID_SETUPER_H
#define FROM_GRID_SETUPER_H

#include "../ebo_setuper.h"

class FromGridSetuper : public EBOSetuper
{
public:
    FromGridSetuper(std::size_t width, std::size_t height);

    void setupEBO(std::vector<std::size_t> &ebo) override;

private:
    std::size_t _width;
    std::size_t _height;
};

#endif