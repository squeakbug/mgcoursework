#ifndef FILE_GRID_LOADER_H
#define FILE_GRID_LOADER_H

#include <string>
#include <fstream>

#include "../grid_loader.h"

class FileGridLoader : public GridLoader
{
public:
    FileGridLoader();

    void readData(const std::string &filename);
    void cutData(Rectangle rect);
    void transformDataToGrid();

    std::shared_ptr<Grid> getGrid() override;

private:
    std::shared_ptr<Grid> _output;

    uint8_t *_data;
    size_t _width, _height;
};

#endif