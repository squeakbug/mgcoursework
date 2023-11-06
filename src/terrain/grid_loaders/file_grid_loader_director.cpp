#include "terrain/grid_loaders/file_grid_loader_director.h"
#include "errors/runtime_exceptions.h"

FileGridLoaderDirector::FileGridLoaderDirector(std::shared_ptr<FileGridLoader> loader, const std::string &filename, Rectangle rect)
{
    _loader = loader;
    _filename = filename;

    _isDefaultRectangle = false;
    _rect = rect;
}

FileGridLoaderDirector::FileGridLoaderDirector(std::shared_ptr<FileGridLoader> loader, const std::string &filename)
    : _rect(Rectangle())
{
    _loader = loader;

    if (filename.size() == 0)
    {
        throw EmptyFilenameException(__FILE__, typeid(*this).name(), __LINE__,
            "Не задано название файла");
    }
    _filename = filename;

    _isDefaultRectangle = true;
}

void FileGridLoaderDirector::loadGrid()
{
    _loader->readData(_filename);

    if (!_isDefaultRectangle)
        _loader->cutData(_rect);

    _loader->transformDataToGrid();
}

std::shared_ptr<Grid> FileGridLoaderDirector::getGrid()
{
    return _loader->getGrid();
}