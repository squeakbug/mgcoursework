#include <iostream>

#include "errors/runtime_exceptions.h"
#include "terrain/grid_loaders/file_grid_loader.h"
#include "terrain/grid_loaders/stb_image.h"

FileGridLoader::FileGridLoader()
{

}

void FileGridLoader::readData(const std::string &filename)
{
    int width, height, channels;
    const unsigned int desiredChannels = 0;
    uint8_t *data = stbi_load(filename.c_str(), &width, &height, &channels, desiredChannels);

    if (data == nullptr)
    {
        throw ReadingDataException(__FILE__, typeid(*this).name(), __LINE__,
            "Ошибка чтения файла: " + filename);
    }

    _data = data;
    _width = (size_t) width;
    _height = (size_t) height;
}

void FileGridLoader::cutData(Rectangle rect)
{
    if (_width < rect.x + rect.width || _height < rect.y + rect.height)
    {
        throw BadHeightmapRectangleException(__FILE__, typeid(*this).name(), __LINE__,
            "Неправильно заданы размеры отсекателя карты");
    }

    size_t di = rect.y, dj = rect.x;
    for (size_t i = 0; i < rect.height; i++)
    {
        for (size_t j = 0; j < rect.width; j++)
        {
            _data[j + rect.width * i] = _data[dj + di * _width];
            dj++;
        }
        di++;
        dj = rect.x;
    }

    _height = rect.height;
    _width = rect.width;
}

void FileGridLoader::transformDataToGrid()
{
    const float NORMALIZED_COORDS_TO_BYTE_RATIO = 255.f;
    
    _output = std::shared_ptr<Grid>(new Grid(_height, _width));
    for (size_t i = 0; i < _height; i++)
    {
        for (size_t j = 0; j < _width; j++)
            (*_output)[i][j] = (float) _data[j + _width * i] / NORMALIZED_COORDS_TO_BYTE_RATIO;
    }

    stbi_image_free(_data);
}

std::shared_ptr<Grid> FileGridLoader::getGrid()
{
    return _output;
}