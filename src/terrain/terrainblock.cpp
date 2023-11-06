#include <cstddef>

#include "base_objects/water_vertex.h"
#include "math/math.h"
#include "terrain/terrainblock.h"

#include "primitives/ebo_setupers/from_grid_setuper.h"
#include "primitives/terrain_frame_model.h"
#include "primitives/terrain_polygon_model.h"

static const vec3<> defaultNormal = { 0.f, 0.f, 0.f };
static const vec3<> defaultFrameColor = { 1.f, 1.f, 1.f };

static const vec3<> materialAmbient = { 1.f, 1.f, 1.f };
static const vec3<> materialDiffuse = { 1.f, 1.f, 1.f };
static const vec3<> materialSpecular = { 1.f, 1.f, 1.f };

static const vec3<> defaultTerrainColor = { 0.f, 1.f, 0.f };
static const vec3<> defaultWaterColor = { 0.f, 0.f, 1.f };

TerrainBlock::TerrainBlock()
{
}

vec3<> TerrainBlock::getNormal(size_t row, size_t col)
{
    if (row == 0 && col == 0) {
        return math<>::calculateFaceNormal(
            { 0, 0, (*_grid)[0][0] * _maxHeight },
            { 0, 1, (*_grid)[1][0] * _maxHeight },
            { 1, 0, (*_grid)[0][1] * _maxHeight });
    }

    if (row == 0 && col == _grid->width() - 1) {
        return math<>::calculateFaceNormal(
            { (float)col, 0, (*_grid)[0][col] * _maxHeight },
            { (float)col - 1, 0, (*_grid)[0][col - 1] * _maxHeight },
            { (float)col, 1, (*_grid)[1][col] * _maxHeight });
    }

    if (row == _grid->height() - 1 && col == 0) {
        return math<>::calculateFaceNormal(
            { 0, (float)row, (*_grid)[row][0] * _maxHeight },
            { 1, (float)row, (*_grid)[row][1] * _maxHeight },
            { 0, (float)row - 1, (*_grid)[row - 1][0] * _maxHeight });
    }

    if (row == _grid->height() - 1 && col == _grid->width() - 1) {
        return math<>::calculateFaceNormal(
            { (float)col - 1, (float)row, (*_grid)[row][col - 1] * _maxHeight },
            { (float)col, (float)row, (*_grid)[row][col] * _maxHeight },
            { (float)col, (float)row - 1, (*_grid)[row - 1][col] * _maxHeight });
    }

    if (row == 0) {
        vec3<> downVec = { 0.f, 1.f, ((*_grid)[row + 1][col] - (*_grid)[row][col]) * _maxHeight };
        vec3<> leftVec = { -1.f, 0.f, ((*_grid)[row][col - 1] - (*_grid)[row][col]) * _maxHeight };
        vec3<> rigthVec = { 1.f, 0.f, ((*_grid)[row][col + 1] - (*_grid)[row][col]) * _maxHeight };
        vec3<> _output = { 0.f, 0.f, 0.f };

        _output += math<>::cross(leftVec, downVec);
        _output += math<>::cross(downVec, rigthVec);
        return _output * 0.5f;
    }

    if (col == 0) {
        vec3<> upVec = { 0.f, -1.f, ((*_grid)[row - 1][col] - (*_grid)[row][col]) * _maxHeight };
        vec3<> rightVec = { 1.f, 0.f, ((*_grid)[row][col + 1] - (*_grid)[row][col]) * _maxHeight };
        vec3<> downVec = { 0.f, 1.f, ((*_grid)[row + 1][col] - (*_grid)[row][col]) * _maxHeight };
        vec3<> _output = { 0.f, 0.f, 0.f };

        _output += math<>::cross(downVec, rightVec);
        _output += math<>::cross(rightVec, upVec);
        return _output * 0.5f;
    }

    if (row == _grid->height() - 1) {
        vec3<> leftVec = { -1.f, 0.f, ((*_grid)[row][col - 1] - (*_grid)[row][col]) * _maxHeight };
        vec3<> rightVec = { 1.f, 0.f, ((*_grid)[row][col + 1] - (*_grid)[row][col]) * _maxHeight };
        vec3<> upVec = { 0.f, -1.f, ((*_grid)[row - 1][col] - (*_grid)[row][col]) * _maxHeight };
        vec3<> _output = { 0.f, 0.f, 0.f };

        _output += math<>::cross(upVec, leftVec);
        _output += math<>::cross(rightVec, upVec);
        return _output * 0.5f;
    }

    if (col == _grid->width() - 1) {
        vec3<> upVec = { 0.f, -1.f, ((*_grid)[row - 1][col] - (*_grid)[row][col]) * _maxHeight };
        vec3<> downVec = { 0.f, 1.f, ((*_grid)[row + 1][col] - (*_grid)[row][col]) * _maxHeight };
        vec3<> leftVec = { -1.f, 0.f, ((*_grid)[row][col - 1] - (*_grid)[row][col]) * _maxHeight };
        vec3<> _output = { 0.f, 0.f, 0.f };

        _output += math<>::cross(upVec, leftVec);
        _output += math<>::cross(leftVec, downVec);
        return _output * 0.5f;
    }

    vec3<> _output = { 0.f, 0.f, 0.f };
    vec3<> upVec = { 0.f, -1.f, ((*_grid)[row - 1][col] - (*_grid)[row][col]) * _maxHeight };
    vec3<> downVec = { 0.f, 1.f, ((*_grid)[row + 1][col] - (*_grid)[row][col]) * _maxHeight };
    vec3<> leftVec = { -1.f, 0.f, ((*_grid)[row][col - 1] - (*_grid)[row][col]) * _maxHeight };
    vec3<> rightVec = { 1.f, 0.f, ((*_grid)[row][col + 1] - (*_grid)[row][col]) * _maxHeight };

    _output += math<>::cross(upVec, leftVec);
    _output += math<>::cross(leftVec, downVec);
    _output += math<>::cross(downVec, rightVec);
    _output += math<>::cross(rightVec, upVec);
    return _output * 0.25;
}

void TerrainBlock::paintWaterErosion(Vertex& v, size_t x, size_t y)
{
    if ((*_waterIntecities)[y][x] > 0) {
        v.color = defaultWaterColor;
    }
}

// TODO Подумать над тем, как сделать из полигональной модели объемную модель
//  или сделать вид, что она является объемной моделью
std::shared_ptr<TerrainPolygonModel> TerrainBlock::to_polygon_model()
{
    std::shared_ptr<TerrainPolygonModel> model(new TerrainPolygonModel(shared_from_this()));

    // TODO move material choosing on intarface level
    model->setMaterial(std::shared_ptr<MaterialProperty>(new MaterialProperty(
        materialAmbient, materialDiffuse, materialSpecular)));

    if (_grid->height() < 2 || _grid->width() < 2) {
        throw NoGridYetException(__FILE__, typeid(*this).name(), __LINE__,
            "Карта еще не загружена либо она имеет недопустимые для преобразования размеры");
    }

    for (size_t i = 0; i < _grid->height(); ++i) {
        for (size_t j = 0; j < _grid->width(); ++j) {
            vec3<> color = defaultTerrainColor;
            vec3<> normal = -getNormal(i, j);
            vec3<> position = vec3<>(float(j) - _grid->width() / 2, float(i) - _grid->height() / 2, (*_grid)[i][j] * _maxHeight);
            std::shared_ptr<Vertex> vertex;
            if ((*_waterIntecities)[i][j] > 0)
                vertex = std::shared_ptr<Vertex>(new WaterVertex(color, position, normal));
            else
                vertex = std::shared_ptr<Vertex>(new Vertex(color, position, normal));
            vertex->texCoords = { float(j) / _grid->width(), float(i) / _grid->height(), 0 }; // TODO change to vec2
            model->addVertex(vertex);
        }
    }

    _painter->paint(*model);
    std::vector<std::shared_ptr<Vertex>>& VBO = model->getVBO();
    if (_isWaterRequired) {
        for (auto& vertex : VBO) {
            vertex->position.z = math<>::clamp(vertex->position.z, _waterLevel);
            if (vertex->position.z < _waterLevel + math<>::eps) {
                // TODO определить "центр Земли"
                vertex->normal = { 0.f, 0.f, 1.f };
                vertex->color = defaultWaterColor;
            }
        }
    }

    // TODO move EBO setuper creating on interface level
    model->setupEBO(std::shared_ptr<EBOSetuper>(new FromGridSetuper(_grid->width(), _grid->height())));

    return model;
}

std::shared_ptr<TerrainFrameModel> TerrainBlock::to_frame_model()
{
    std::shared_ptr<TerrainFrameModel> model(new TerrainFrameModel(shared_from_this()));
    std::shared_ptr<Details> details(new Details);

    /* Добавление вершин */
    for (size_t i = 0; i < _grid->height(); ++i) {
        for (size_t j = 0; j < _grid->width(); ++j) {
            float height = (*_grid)[i][j] * _maxHeight;
            if (_isWaterRequired)
                height = math<>::clamp(height, _waterLevel);
            details->add_vertex(
                Vertex(defaultFrameColor, vec3<>(float(j) - _grid->width() / 2, float(i) - _grid->height() / 2, height), defaultNormal));
        }
    }

    /* Добавление горизонтальных и вертикальных ребер */
    size_t grid_width = _grid->width();
    for (std::size_t i = 0; i < _grid->height(); ++i) {
        for (std::size_t j = 0; j < grid_width - 1; ++j)
            details->add_rib(Rib(j + i * grid_width, j + i * grid_width + 1));
    }

    for (std::size_t i = 0; i < _grid->width(); ++i) {
        for (std::size_t j = 0; j < _grid->height() - 1; ++j)
            details->add_rib(Rib(i + j * grid_width, i + (j + 1) * grid_width));
    }

    /* Добавление косых ребер */
    for (size_t i = 1; i < _grid->height(); ++i) {
        for (size_t j = 0; j < i; ++j)
            details->add_rib(Rib(j + (i - j) * grid_width, j + (i - j - 1) * grid_width + 1));
    }

    for (size_t i = 1; i < _grid->height() - 1; ++i) {
        for (size_t j = 0; j < i; ++j)
            details->add_rib(Rib(grid_width - j - 1 + i * grid_width, grid_width - j - 2 + (i + 1) * grid_width));
    }

    model->set_details(details);

    return model;
}

void TerrainBlock::setMaxHeight(float maxHeight)
{
    _maxHeight = maxHeight;
}

void TerrainBlock::setWaterLevel(float waterLevel)
{
    _waterLevel = waterLevel;
}

void TerrainBlock::setWaterRequired(bool newState)
{
    _isWaterRequired = newState;
}

void TerrainBlock::setPainter(std::shared_ptr<BasePainter> painter)
{
    _painter = painter;
}

void TerrainBlock::setLandscapeMask(std::shared_ptr<ILandscapeMask> landscapeMask)
{
    _landscapeMask = landscapeMask;
}

void TerrainBlock::set_generator(std::shared_ptr<GridGenerator> gen)
{
    _generator = gen;
}

#include <iostream>

static int lim(int value, int min, int max)
{
    if (value >= max)
        value = max - 1;
    if (value < min)
        value = min;
    return value;
}

static void smoothGrid(std::shared_ptr<Grid> grid)
{
    size_t _repeatCnt = 1;
    size_t _radius = 1;

    size_t h = grid->height();
    size_t w = grid->width();
    for (size_t r = 0; r < _repeatCnt; ++r) {
        for (size_t i = 0; i < h; i++) {
            for (size_t j = 0; j < w; j++) {
                float kernelSum = (*grid)[i][j];

                for (size_t k = 1; k <= _radius; ++k) {
                    kernelSum += (*grid)[lim(i - k, 0, h)][j];
                    kernelSum += (*grid)[lim(i + k, 0, h)][j];
                    for (size_t ik = 1; ik <= k; ++ik) {
                        kernelSum += (*grid)[lim(i - k, 0, h)][lim(j + ik, 0, h)];
                        kernelSum += (*grid)[lim(i - k, 0, h)][lim(j - ik, 0, w)];
                        kernelSum += (*grid)[lim(i + k, 0, h)][lim(j + ik, 0, h)];
                        kernelSum += (*grid)[lim(i + k, 0, h)][lim(j - ik, 0, w)];
                    }

                    kernelSum += (*grid)[i][lim(j + k, 0, w)];
                    kernelSum += (*grid)[i][lim(j - k, 0, w)];
                    for (size_t ik = 1; ik < k; ++ik) {
                        kernelSum += (*grid)[lim(i + ik, 0, h)][lim(j + k, 0, w)];
                        kernelSum += (*grid)[lim(i - ik, 0, h)][lim(j + k, 0, w)];
                        kernelSum += (*grid)[lim(i + ik, 0, h)][lim(j - k, 0, w)];
                        kernelSum += (*grid)[lim(i - ik, 0, h)][lim(j - k, 0, w)];
                    }
                }

                (*grid)[i][j] = kernelSum / size_t(pow(2 * _radius + 1, 2) + math<>::eps);
            }
        }
    }
}

void TerrainBlock::deformGrid(size_t x, size_t y)
{
    const int maxIteration = 250;
    float dx = 0.5f;
    float dy = 0.5f;
    float fx = x, fy = y;
    size_t px = x;
    size_t py = y;

    const float friction = 0.2f;
    const float depositRatio = 0.01f;
    const float erosionRatio = 0.01f;
    const float iterationRation = 0.5f / maxIteration;
    const float speed = 0.1f;

    float deposit = 0.f;
    float erosion = 0.f;
    float sediment = 1.f;
    for (int i = 0; i < maxIteration; ++i) {
        vec3<> normal = math<>::normalize(getNormal(y, x));

        if (fabs(normal.z - 1) < math<>::eps)
            return;

        deposit = depositRatio * sediment * normal.z;
        erosion = erosionRatio * (1 - normal.z) * std::min(1.f, i * iterationRation);

        // std::cout << "X,Y: [" << x << ' ' << y << "]\n";
        // std::cout << "Deposit: " << deposit << "; Erosion: " << erosion << std::endl;
        // std::cout << "Normal: [" << normal.x << ' ' << normal.y << ' ' << normal.z << "]\n";

        (*_grid)[py][px] += deposit - erosion;
        (*_waterIntecities)[py][px] += 1;
        sediment += erosion - deposit;

        if ((*_grid)[py][px] < 0.f)
            (*_grid)[py][px] = 0.f;
        if ((*_grid)[py][px] > 1.f)
            (*_grid)[py][px] = 1.f;
        dx = dx * friction + normal.x * speed;
        dy = dy * friction + normal.y * speed;
        px = std::ceil(fx);
        py = std::ceil(fy);
        fx += dx;
        fy += dy;
        x = std::ceil(fx);
        y = std::ceil(fy);

        if (x < 0 || x >= _grid->width() || y < 0 || y >= _grid->height())
            return;
    }
}

int TerrainBlock::getSnawBallsCount()
{
    const float square2countRatio = 0.005;
    return _grid->height() * _grid->width() * square2countRatio;
}

void TerrainBlock::makeErrosion()
{
    if (_grid == nullptr) {
        throw NoGridYetException(__FILE__, typeid(*this).name(), __LINE__,
            "Карта высот еще не сформирована");
    }

    int snowBalls = getSnawBallsCount();

    for (int i = 0; i < snowBalls; ++i)
        deformGrid(rand() % _grid->width(), rand() % _grid->height());

    smoothGrid(_grid);
}

void TerrainBlock::generate_grid(size_t height, size_t width)
{
    _grid = _generator->generate(height, width);
    _waterIntecities = std::shared_ptr<Grid>(new Grid(height, width, 0.f));

    _landscapeMask->updateTerrain(_grid);
}

void TerrainBlock::load_grid(std::shared_ptr<GridLoaderDirector> loader)
{
    loader->loadGrid();
    _grid = loader->getGrid();
}

void TerrainBlock::save_grid(std::shared_ptr<GridSaver> saver, Rectangle rect)
{
    saver->save_grid(*_grid, rect);
}

void TerrainBlock::save_grid(std::shared_ptr<GridSaver> saver)
{
    Rectangle rect;
    rect.x = 0;
    rect.y = 0;
    rect.width = _grid->width();
    rect.height = _grid->height();

    saver->save_grid(*_grid, rect);
};

std::shared_ptr<Grid> TerrainBlock::get_grid()
{
    return _grid;
}

void TerrainBlock::accept(Visitor& visitor)
{
    visitor.visit(*this);
}
