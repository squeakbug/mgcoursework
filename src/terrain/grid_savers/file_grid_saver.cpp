#include <iostream>

#include "errors/runtime_exceptions.h"
#include "terrain/grid_savers/file_grid_saver.h"
#include "terrain/grid_savers/stb_image_write.h"

FileGridSaver::FileGridSaver(const std::string &filename, EImageFileExtension ext)
{
    if (filename.size() == 0)
    {
        throw EmptyFilenameException(__FILE__, typeid(*this).name(), __LINE__,
            "Не задано название файла");
    }
    _filename = filename;
    _ext = ext;
}

void cutArray(uint8_t *byteArray, size_t gridWidth, const Rectangle &rect)
{
    size_t di = rect.y, dj = rect.x;
    for (size_t i = 0; i < rect.height; i++)
    {
        for (size_t j = 0; j < rect.width; j++)
        {
            byteArray[j + rect.width * i] = byteArray[dj + di * gridWidth];
            dj++;
        }
        di++;
        dj = rect.x;
    }
}

void FileGridSaver::save_grid(const Grid &grid, Rectangle rect)
{
    if (grid.height() < 2 || grid.width() < 2)
    {
        throw NoGridYetException(__FILE__, typeid(*this).name(), __LINE__,
            "Попытка сохранить пустую карту");
    }

    size_t dataSize = grid.height() * grid.width();
    uint8_t *byteArray = new uint8_t [dataSize];
    if (byteArray == nullptr)
    {
        throw BadAllocException(__FILE__, typeid(*this).name(), __LINE__,
            "Ошибка при выделении памяти под массив байт для сохранения изображения");
    }

    const float *data = grid.data();
    const float NORMALIZED_COORDS_TO_BYTE_RATIO = 255.f;
    for (size_t i = 0; i < dataSize; i++)
        byteArray[i] = uint8_t(data[i] * NORMALIZED_COORDS_TO_BYTE_RATIO);

    if (grid.width() < rect.x + rect.width || grid.height() < rect.y + rect.height)
    {
        throw BadHeightmapRectangleException(__FILE__, typeid(*this).name(), __LINE__,
            "Неправильно заданы размеры отсекателя карты");
    }
    cutArray(byteArray, grid.width(), rect);

    int rc = 0;
    const unsigned int channelsCnt = 1;
    const unsigned int imgQuality = 100;
    switch (_ext)
    {
    case EImageFileExtension::JPG:
        rc = stbi_write_jpg(_filename.c_str(), rect.width, rect.height, channelsCnt, (void*)byteArray, imgQuality);
        break;
    case EImageFileExtension::PNG:
        rc = stbi_write_png(_filename.c_str(), rect.width, rect.height, channelsCnt, (void*)byteArray, grid.width() * channelsCnt);
        break;
    case EImageFileExtension::BMP:
        rc = stbi_write_bmp(_filename.c_str(), rect.width, rect.height, channelsCnt, (void*)byteArray);
        break;
    default:
        break;
    }

    delete [] byteArray;

    const int WRITE_FAILURE = 0;
    if (rc == WRITE_FAILURE)
    {
        throw WritingDataException(__FILE__, typeid(*this).name(), __LINE__,
            "Ошибка при попытке сохранения изображения");
    }
}