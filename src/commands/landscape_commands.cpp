#include <algorithm>

#include "commands/landscape_commands.h"

#include "managers/scenemanager.h"
#include "managers/terrainmanager.h"
#include "primitives/terrain_frame_model.h"
#include "primitives/terrain_polygon_model.h"

#include "terrain/grid_loaders/file_grid_loader_director.h"
#include "terrain/landscape_masks/default_landscape_mask.h"
#include "terrain/landscape_masks/hill_mask_decorator.h"
#include "terrain/landscape_masks/torus_mask_decorator.h"
#include "terrain/landscape_masks/smooth_mask_decorator.h"
#include "terrain/generators/spngenerator.h"
#include "terrain/generators/new_dsgenerator.h"

UpdadeLandscapeCommand::UpdadeLandscapeCommand()
{

}

void UpdadeLandscapeCommand::execute()
{
    std::shared_ptr<SceneManager> scene_manager = SceneManager::instance();
    std::shared_ptr<TerrainManager> terrain_manager = TerrainManager::instance();
    std::shared_ptr<Scene> scene = scene_manager->get_scene();

    std::shared_ptr<TerrainBlock> terrain =  terrain_manager->get_terrain_block();
    if (terrain->get_grid() == nullptr)
    {
        throw NoGridYetException(__FILE__, typeid(*this).name(), __LINE__,
            "Матрица высот еще не сформирована");
    }

    _scene = scene;
    _terrain = terrain;
}

AddFrameLandscapeCommand::AddFrameLandscapeCommand()
{

}

void AddFrameLandscapeCommand::execute()
{
    UpdadeLandscapeCommand::execute();
    std::shared_ptr<SceneObject> model = _terrain->to_frame_model();
    _scene->add_obj(model);
    model = _terrain->to_polygon_model();
    model->disable();
    _scene->add_obj(model);
}

AddPolygonLandscapeCommand::AddPolygonLandscapeCommand()
{

}

void AddPolygonLandscapeCommand::execute()
{
    UpdadeLandscapeCommand::execute();
    std::shared_ptr<SceneObject> model = _terrain->to_polygon_model();
    _scene->add_obj(model);
    model = _terrain->to_frame_model();
    model->disable();
    _scene->add_obj(model);
}

/* ========== FormLandscapeCommand ========== */

FormLandscapeCommand::FormLandscapeCommand(std::size_t height, std::size_t width)
{
    _height = height;
    _width = width;
}

/* ========== FormMDSLandscapeCommand ========== */

FormMDSLandscapeCommand::FormMDSLandscapeCommand(std::size_t height, std::size_t width, float roughness, float delta, const CornerHeights &heights)
    : FormLandscapeCommand(height, width)
{
    _roughness = roughness;
    _delta = delta;
    _heights = heights;
}

void FormMDSLandscapeCommand::execute()
{
    std::shared_ptr<TerrainManager> terrain_manager = TerrainManager::instance();
    std::shared_ptr<TerrainBlock> terrain = terrain_manager->get_terrain_block();

    std::shared_ptr<GridGenerator> generator(new MDSGenerator(_roughness, _delta, _heights));

    terrain->set_generator(generator);
    terrain->generate_grid(_height, _width);
}

/* ========== FormPNLandscapeCommand ========== */

FormPNLandscapeCommand::FormPNLandscapeCommand(std::size_t height, std::size_t width, std::size_t octavesCnt)
    : FormLandscapeCommand(height, width)
{
    _octavesCnt = octavesCnt;
}

void FormPNLandscapeCommand::execute()
{
    std::shared_ptr<TerrainManager> terrain_manager = TerrainManager::instance();
    std::shared_ptr<TerrainBlock> terrain = terrain_manager->get_terrain_block();

    std::shared_ptr<GridGenerator> generator(new SPNGenerator(_octavesCnt));

    terrain->set_generator(generator);
    terrain->generate_grid(_width, _height);
}

/* ========== FormPNLandscapeCommand ========== */

FormDSLandscapeCommand::FormDSLandscapeCommand(std::size_t height, std::size_t width, float roughness, float delta, SurfaceType type, const CornerHeights &heights)
    : FormLandscapeCommand(height, width)
{
    _roughness = roughness;
    _delta = delta;
    _heights = heights;
    _type = type;
}

void FormDSLandscapeCommand::execute()
{
    std::shared_ptr<TerrainManager> terrain_manager = TerrainManager::instance();
    std::shared_ptr<TerrainBlock> terrain = terrain_manager->get_terrain_block();

    std::shared_ptr<GridGenerator> generator(new NewDSGenerator(_roughness, _delta, _heights));

    terrain->set_generator(generator);
    terrain->generate_grid(_height, _width);
}

SaveLandscapeToFile::SaveLandscapeToFile(std::string filename, EImageFileExtension ext)
{
    _filename = filename;
    _ext = ext;
}

void SaveLandscapeToFile::execute()
{
    std::shared_ptr<TerrainManager> terrain_manager = TerrainManager::instance();
    std::shared_ptr<TerrainBlock> terrain = terrain_manager->get_terrain_block();

    std::shared_ptr<GridSaver> saver(new FileGridSaver(_filename, _ext));
    terrain->save_grid(saver);
}

LoadLandscapeFromFile::LoadLandscapeFromFile(std::string filename)
{
    _filename = filename;
}

void LoadLandscapeFromFile::execute()
{
    std::shared_ptr<TerrainManager> terrain_manager = TerrainManager::instance();
    std::shared_ptr<TerrainBlock> terrain = terrain_manager->get_terrain_block();

    std::shared_ptr<FileGridLoader> loader(new FileGridLoader);
    std::shared_ptr<GridLoaderDirector> director(new FileGridLoaderDirector(loader, _filename));
    terrain->load_grid(director);
}

SetMaxLandscapeHeightCommand::SetMaxLandscapeHeightCommand(float height)
    : _height(height)
{

}

void SetMaxLandscapeHeightCommand::execute()
{
    std::shared_ptr<TerrainManager> terrain_manager = TerrainManager::instance();
    std::shared_ptr<TerrainBlock> terrain = terrain_manager->get_terrain_block();

    terrain->setMaxHeight(_height);
}

SetLandscapeWaterLevelCommand::SetLandscapeWaterLevelCommand(float waterLevel)
    : _waterLevel(waterLevel)
{

}

void SetLandscapeWaterLevelCommand::execute()
{
    std::shared_ptr<TerrainManager> terrain_manager = TerrainManager::instance();
    std::shared_ptr<TerrainBlock> terrain = terrain_manager->get_terrain_block();

    terrain->setWaterLevel(_waterLevel);
}

SetWaterStateCommand::SetWaterStateCommand(bool isRequired)
{
    _isRequired = isRequired;
}

void SetWaterStateCommand::execute()
{
    std::shared_ptr<TerrainManager> terrain_manager = TerrainManager::instance();
    std::shared_ptr<TerrainBlock> terrain = terrain_manager->get_terrain_block();

    terrain->setWaterRequired(_isRequired);
}

SetWaterRenderCommand::SetWaterRenderCommand(bool isEnable)
    : _isEnable(isEnable)
{

}

DeformLandscapeCommand::DeformLandscapeCommand(float value)
{
    _value = value;
}

void DeformLandscapeCommand::execute()
{
    std::shared_ptr<TerrainManager> terrain_manager = TerrainManager::instance();
    std::shared_ptr<TerrainBlock> terrain = terrain_manager->get_terrain_block();

    terrain->makeErrosion();
}

void SetWaterRenderCommand::execute()
{
    std::shared_ptr<TerrainManager> terrain_manager = TerrainManager::instance();
    std::shared_ptr<TerrainBlock> terrain = terrain_manager->get_terrain_block();

    terrain->setWaterRequired(_isEnable);
}

SetLandscapeMaskCommand::SetLandscapeMaskCommand()
{

}

SetLandscapeMaskCommand::SetLandscapeMaskCommand(size_t kernelRadius, size_t repeatCnt)
{
    _kernelRadius = kernelRadius;
    _repeatCnt = repeatCnt;
}


SetRandomLandscapeMaskCommand::SetRandomLandscapeMaskCommand()
    : SetLandscapeMaskCommand()
{
    
}

void SetRandomLandscapeMaskCommand::execute()
{
    std::shared_ptr<TerrainManager> terrain_manager = TerrainManager::instance();
    std::shared_ptr<TerrainBlock> terrain = terrain_manager->get_terrain_block();
    std::shared_ptr<ILandscapeMask> mask(new DefaultLandscapeMask());
    mask = std::shared_ptr<ILandscapeMask>(new SmoothMaskDecorator(mask, _kernelRadius, _repeatCnt));

    terrain->setLandscapeMask(mask);
}

SetTorusLandscapeMaskCommand::SetTorusLandscapeMaskCommand()
    : SetLandscapeMaskCommand()
{

}

void SetTorusLandscapeMaskCommand::execute()
{
    std::shared_ptr<TerrainManager> terrain_manager = TerrainManager::instance();
    std::shared_ptr<TerrainBlock> terrain = terrain_manager->get_terrain_block();
    std::shared_ptr<ILandscapeMask> mask(new DefaultLandscapeMask());
    mask = std::shared_ptr<ILandscapeMask>(new SmoothMaskDecorator(mask, _kernelRadius, _repeatCnt));
    mask = std::shared_ptr<ILandscapeMask>(new TorusMaskDecorator(mask));

    terrain->setLandscapeMask(mask);
}

SetHillLandscapeMaskCommand::SetHillLandscapeMaskCommand()
    : SetLandscapeMaskCommand()
{

}

void SetHillLandscapeMaskCommand::execute()
{
    std::shared_ptr<TerrainManager> terrain_manager = TerrainManager::instance();
    std::shared_ptr<TerrainBlock> terrain = terrain_manager->get_terrain_block();
    std::shared_ptr<ILandscapeMask> mask(new DefaultLandscapeMask());
    mask = std::shared_ptr<ILandscapeMask>(new SmoothMaskDecorator(mask, _kernelRadius, _repeatCnt));
    mask = std::shared_ptr<ILandscapeMask>(new HillMaskDecorator(mask));

    terrain->setLandscapeMask(mask);
}

SetupLandscapeGradientCommand::SetupLandscapeGradientCommand(std::shared_ptr<Gradient> gradient)
    : _gradient(gradient)
{

}

void SetupLandscapeGradientCommand::execute()
{
    std::shared_ptr<TerrainManager> terrain_manager = TerrainManager::instance();
    std::shared_ptr<TerrainBlock> terrain = terrain_manager->get_terrain_block();

    auto painter = std::make_shared<GradientPainter>();
    painter->setGradient(_gradient);

    terrain->setPainter(painter);
}
