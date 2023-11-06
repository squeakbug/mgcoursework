#ifndef TERRAINMANAGER_H
#define TERRAINMANAGER_H

#include "managers/basemanager.h"
#include "terrain/terrainblock.h"

class TerrainManager : public BaseManager
{
public:
    static std::shared_ptr<TerrainManager> instance();

    std::shared_ptr<TerrainBlock> get_terrain_block();

private:
    TerrainManager();
    TerrainManager(const TerrainManager &other) = delete;
    TerrainManager &operator=(const TerrainManager &other) = delete;

private:
    std::shared_ptr<TerrainBlock> terrain_block;
};

#endif // TERRAINMANAGER_H
