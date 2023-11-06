#ifndef FILE_GRID_SAVER_H
#define FILE_GRID_SAVER_H

#include <string>

#include "base_objects/rectangle.h"
#include "terrain/grid_saver.h"

enum class EImageFileExtension
{
    PNG,
    BMP,
    JPG
};

class FileGridSaver : public GridSaver
{
public:
    FileGridSaver(const std::string &filename, EImageFileExtension ext);

    void save_grid(const Grid &grid, Rectangle rect) override;

private:
    std::string _filename;
    EImageFileExtension _ext;
};

#endif