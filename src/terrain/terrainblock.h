#ifndef TERRAINBLOCK_H
#define TERRAINBLOCK_H

#include <memory>
#include <vector>
#include <string>

#include "terrain/grid.h"
#include "terrain/grid_saver.h"
#include "terrain/grid_loader_director.h"
#include "terrain/grid_generator.h"
#include "terrain/ilandscape_mask.h"

#include "scene/scene.h"
#include "primitives/polygonmodel.h"
#include "primitives/framemodel.h"
#include "base_objects/rectangle.h"

#include "visitors/visitor.h"
#include "painter/base_painter.h"

//TODO remove from here
#include "painter/gradient_painter.h"

class TerrainFrameModel;
class TerrainPolygonModel;

using std::size_t;

class TerrainBlock : public std::enable_shared_from_this<TerrainBlock>
{
    friend class DrawVisitor;

public:
    TerrainBlock();

    std::shared_ptr<TerrainPolygonModel> to_polygon_model();
    std::shared_ptr<TerrainFrameModel> to_frame_model();

    void setMaxHeight(float maxHeight);
    void setWaterLevel(float waterLevel);
    void setWaterRequired(bool newState);

    void setPainter(std::shared_ptr<BasePainter> painter);

    void setLandscapeMask(std::shared_ptr<ILandscapeMask> landscapeMask);

    void set_generator(std::shared_ptr<GridGenerator> gen);
    void generate_grid(size_t width, size_t height);

    void load_grid(std::shared_ptr<GridLoaderDirector> loader);

    void save_grid(std::shared_ptr<GridSaver> saver, Rectangle rect);
    void save_grid(std::shared_ptr<GridSaver> saver);

    std::shared_ptr<Grid> get_grid();

    void accept(Visitor &visitor);

    void makeErrosion();

private:
    void deformGrid(size_t x, size_t y);
    void paintWaterErosion(Vertex &v, size_t x, size_t y);
    int getSnawBallsCount();

protected:
    vec3<> getNormal(size_t row, size_t col);

private:
    std::shared_ptr<GridGenerator> _generator;
    std::shared_ptr<Grid> _grid;
    std::shared_ptr<Grid> _waterIntecities;
    float _waterLevel;
    bool _isWaterRequired;
    float _maxHeight;
    std::shared_ptr<ILandscapeMask> _landscapeMask;
    std::shared_ptr<BasePainter> _painter;
};

#endif // TERRAINBLOCK_H
