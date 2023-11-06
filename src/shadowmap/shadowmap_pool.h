#ifndef SHADOWMAP_POOL_H
#define SHADOWMAP_POOL_H

#include <unordered_map>
#include <cstddef>
#include <memory>

//TODO Заменить тип FrameBuffer на тип Texture
#include "frame_buffers/z_buffer.h"

#include "primitives/light_types/direct_light_source.h"

class ShadowGenerator;

/**
 *  Класс для хранения обычных теневых карт
 */
class ShadowmapPool
{
public:
    static std::shared_ptr<ShadowmapPool> instance();

    void addShadowmap(std::size_t sceneObjectId, std::shared_ptr<ZBuffer> shadowmap);
    void eraseShadowmap(std::size_t sceneObjectId);
    bool checkShadowmap(std::size_t sceneObjectId);
    const std::shared_ptr<ZBuffer> getShadowmap(std::size_t sceneObjectId) const;
    void clear();

    std::unordered_map<std::size_t, std::shared_ptr<ZBuffer>>::iterator begin();
    std::unordered_map<std::size_t, std::shared_ptr<ZBuffer>>::iterator end();

    void generateShadowmaps(Scene &scene);

    void setGenerator(std::shared_ptr<ShadowGenerator> generator);

private:
    ShadowmapPool() = default;
    ShadowmapPool(const ShadowmapPool &other) = delete;

private:
    std::unordered_map<std::size_t, std::shared_ptr<ZBuffer>> _shadowmaps;
    std::shared_ptr<ShadowGenerator> _generator;
};

#endif