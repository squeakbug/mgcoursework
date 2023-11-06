#ifndef FILE_GRID_LOADER_DIRECTOR_H
#define FILE_GRID_LOADER_DIRECTOR_H

#include <memory>
#include <string>

#include "file_grid_loader.h"
#include "../grid_loader_director.h"

class FileGridLoaderDirector : public GridLoaderDirector
{
public:
    FileGridLoaderDirector(std::shared_ptr<FileGridLoader> loader, const std::string &_filename, Rectangle rect);
    FileGridLoaderDirector(std::shared_ptr<FileGridLoader> loader, const std::string &_filename);

    void loadGrid() override;
    std::shared_ptr<Grid> getGrid() override;

private:
    std::shared_ptr<FileGridLoader> _loader;
    std::string _filename;
    Rectangle _rect;

    bool _isDefaultRectangle;
};

#endif