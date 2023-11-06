#include "managers/terrainmanager.h"

std::shared_ptr<TerrainManager> TerrainManager::instance()
{
    static std::shared_ptr<TerrainManager> tmp(new TerrainManager);

    return tmp;
}


std::shared_ptr<TerrainBlock> TerrainManager::get_terrain_block()
{
    if (terrain_block == nullptr)
        terrain_block = std::shared_ptr<TerrainBlock>(new TerrainBlock);

    return terrain_block;
}


TerrainManager::TerrainManager()
    : terrain_block(nullptr)
{

}
