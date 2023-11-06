#include "managers/drawmanager.h"
#include "visitors/drawvisitor.h"
#include "terrain/terrainblock.h"
#include "scene/scene.h"

#include "shaders/fragment_shader.h"
#include "shaders/vertex_shader.h"

#ifdef EXPERIMENT
#include <chrono>
#include <fstream>
#include <iostream>
#include <string>

const size_t REPEAT_EXPERIMENT_CNT = 100;
const size_t DELETE_FIRST_COUNT = 10;       // Убрать первые замеры, чтобы сделать почище выборку
const std::string _logFileName_ = "logfile.txt";
#endif

const vec3<> defaultBackgroundColor = vec3<>(0.3, 0.3, 0.6);

DrawVisitor::DrawVisitor()
    : DrawVisitor(nullptr)
{

}

DrawVisitor::DrawVisitor(std::shared_ptr<DrawManager> manager)
    : _drawer(nullptr),
    _draw_manager(manager)
{

}

void DrawVisitor::visit(Scene &scene)
{
    _drawer->clearFrameBuffer();
    _drawer->clearZBuffer();

    for (auto &obj : scene)
    {
        if (obj->isEnabled())
            obj->accept(*this);
    }

    _drawer->swapBuffers();
}

void DrawVisitor::visit(FrameModel &model)
{
    std::shared_ptr<Details> details = model.get_details();
    std::vector<Vertex> vertecies = details->get_vertecies();
    std::vector<Rib> ribs = details->get_ribs();

    VertexShader shader;
    /* Выполнить проверку на менеджера */
    std::shared_ptr<DrawManager> manager = _draw_manager.lock();
    std::shared_ptr<Camera> camera = manager->get_cam();

    mat4<> projViewMatrix = camera->getProjMatrix() * camera->getViewMatrix();
    for (const auto &rib : ribs)
    {
        mat4<> modelMatrix(1.f);
        Vertex v1 = shader.calculate(vertecies[rib.indx1], projViewMatrix, modelMatrix);
        Vertex v2 = shader.calculate(vertecies[rib.indx2], projViewMatrix, modelMatrix);

        _drawer->drawLine(v1.position.x, v1.position.y, v2.position.x, v2.position.y);
    }
}

void DrawVisitor::visit(PolygonModel &model)
{
    std::vector<std::shared_ptr<Vertex>> VBO = model.getVBO();
    std::vector<std::size_t> EBO = model.getEBO();

    VertexShader vertexShader;
    //TODO проверка на существование менеджера
    std::shared_ptr<DrawManager> manager = _draw_manager.lock();
    std::shared_ptr<Camera> camera = manager->get_cam();

    std::shared_ptr<MaterialProperty> material = model.getMaterial();
    std::shared_ptr<FragmentShader> fragmentShader = model.getFragmentShader();
    fragmentShader->setMaterial(material);
    fragmentShader->setShadowmapPool(manager->getShadowmapPool());
    fragmentShader->setShadowmapUsing(manager->getShadowmapUsing());
    _drawer->setFragmentShader(fragmentShader);
    std::shared_ptr<LightmapPool> pool = manager->getLightmapPool();
    if (manager->getLightmapUsing())
    {
        std::size_t modelId = model.getId();
        if (pool->checkLightmap(modelId))
        {
            fragmentShader->setLightmap(pool->getLightmap(modelId));
            fragmentShader->setLightmapUsing(true);
        }
        else
        {
            //TODO throw exception
            fragmentShader->setLightmapUsing(false);
        }
    }
    else
    {
        fragmentShader->setLightmapUsing(false);
    }

    _drawer->clearZBuffer();

    mat4<> modelMatrix(1.f);
    mat4<> projViewModelMatrix = camera->getProjMatrix() * camera->getViewMatrix() * modelMatrix;
    const size_t VERTICES_IN_TRIANGLES = 3;
    size_t verticesCnt = EBO.size();
    mat4<> inverseMat = math<>::inverse(projViewModelMatrix);
    fragmentShader->setClipToGlobalMatrix(inverseMat);

    #ifdef EXPERIMENT
    char *_cleaning_tlb_buf_ = new char[1048576];
    std::vector<long double> _timings_;
    std::vector<long double> _fragment_shader_timings_;
    for (size_t _i_ = 0; _i_ < REPEAT_EXPERIMENT_CNT; ++_i_)
    {
        long double _fragment_shader_timing_ = 0.0;
        auto _p1_ = std::chrono::high_resolution_clock::now();
    #endif

    for (size_t i = 0; i < verticesCnt; i += VERTICES_IN_TRIANGLES)
    {
        Vertex v1 = vertexShader.calculate(*VBO[EBO[i]], projViewModelMatrix, modelMatrix);
        Vertex v2 = vertexShader.calculate(*VBO[EBO[i + 1]], projViewModelMatrix, modelMatrix);
        Vertex v3 = vertexShader.calculate(*VBO[EBO[i + 2]], projViewModelMatrix, modelMatrix);

        #ifdef EXPERIMENT
        long double _one_element_shading_time_ = 0.0;
        #endif

        _drawer->drawTriangle(v1, v2, v3
        #ifdef EXPERIMENT
        , &_one_element_shading_time_
        #endif
        );

        #ifdef EXPERIMENT
        _fragment_shader_timing_ += ((long double)_one_element_shading_time_) / 1000000;
        #endif
    }

    #ifdef EXPERIMENT
        auto _p2_ = std::chrono::high_resolution_clock::now();
        long double _timing_ = std::chrono::duration_cast<std::chrono::microseconds>(_p2_ - _p1_).count();
        _timings_.push_back(_timing_);
        _fragment_shader_timings_.push_back(_fragment_shader_timing_);

        // Очистка кэша страниц для иммитация нового вызова
        for (size_t _j_ = 0; _j_ < 256; ++_j_)
            char tmp = _cleaning_tlb_buf_[_j_*4*1024];
        _drawer->clearZBuffer();
    }
    #endif

    #ifdef EXPERIMENT
    delete [] _cleaning_tlb_buf_;
    std::ofstream _outputStream_(_logFileName_, std::ios_base::out);
    if (_outputStream_.is_open())
    {
        long double _totalTimeSum_ = 0.0;
        long double _totalShaderTime_ = 0.0;
        for (size_t _i_ = DELETE_FIRST_COUNT; _i_ < REPEAT_EXPERIMENT_CNT; ++_i_)
        {
            _outputStream_ << "Замер №" << _i_ + 1 << ": " << _timings_[_i_] << " мкс." << std::endl;
            _totalTimeSum_ += _timings_[_i_];
            _totalShaderTime_ += _fragment_shader_timings_[_i_];
        }
        long double _avgTime_ = _totalTimeSum_ / (REPEAT_EXPERIMENT_CNT - DELETE_FIRST_COUNT);
        long double _avgShaderTime_ = _totalShaderTime_ / (REPEAT_EXPERIMENT_CNT - DELETE_FIRST_COUNT);
        _outputStream_ << "======================================================" << std::endl;
        _outputStream_ << "Среднее время: " << _avgTime_ << " мкс." << std::endl;
        _outputStream_ << "Среднее время работы фрагментного шейдера: " << _avgShaderTime_ << "*10^6 тактов" << std::endl;
        long double _squeareSum_ = 0.0;
        long double _squeareFragmentSum_ = 0.0;
        for (size_t _i_ = DELETE_FIRST_COUNT; _i_ < REPEAT_EXPERIMENT_CNT; ++_i_)
        {
            long double _diff_ = _avgTime_ - _timings_[_i_];
            long double _fragmentDiff_ = _avgShaderTime_ - _fragment_shader_timings_[_i_];
            _squeareSum_ += _diff_*_diff_;
            _squeareFragmentSum_ += _fragmentDiff_;
        }
        _outputStream_ << "Среднеквадратичное отклонение: " << sqrt(_squeareSum_ / (REPEAT_EXPERIMENT_CNT - DELETE_FIRST_COUNT)) << std::endl;
        _outputStream_ << "Среднеквадратичное отклонение для фрагментного шейдера: " 
            << sqrt(_squeareFragmentSum_ / (REPEAT_EXPERIMENT_CNT - DELETE_FIRST_COUNT)) << std::endl;
        _outputStream_.close();
    }
    else
    {
        std::cout << "Couldn't open log file" << std::endl;
    }
    #endif
}

void DrawVisitor::visit(TerrainBlock &terrain)
{
    std::shared_ptr<Grid> grid = terrain.get_grid();

    _drawer->clearFrameBuffer();

    size_t w = (_drawer->getSceneWidth() - 1);
    size_t h = (_drawer->getSceneHeight() - 1);
    double dw = 2.f / w;
    double dh = 2.f / h;
    double kx = 2.f / (grid->width() - 1);
    double ky = 2.f / (grid->height() - 1);

    for (double h = -1.f; h < 1.f - math<>::eps; h += dh)
    {
        for (double w = -1.f; w < 1.f - math<>::eps; w += dw)
            _drawer->drawPoint(w, h, vec3<>((*grid)[double(h + 1.f)/ky][double(w + 1.f)/kx]));
    }

    _drawer->swapBuffers();
}

void DrawVisitor::visit(LightmapPool &lightmaps)
{
    auto curPosition = lightmaps.getCurPosition();

    if (curPosition == lightmaps.end())
        return;

    _drawer->clearFrameBuffer();
    std::shared_ptr<FrameBuffer> texture = curPosition->second;

    size_t w = (_drawer->getSceneWidth() - 1);
    size_t h = (_drawer->getSceneHeight() - 1);
    double dw = 2.f / w;
    double dh = 2.f / h;
    double kx = 2.f / (texture->width() - 1);
    double ky = 2.f / (texture->height() - 1);

    for (double h = -1.f; h < 1.f - math<>::eps; h += dh)
    {
        for (double w = -1.f; w < 1.f - math<>::eps; w += dw)
            _drawer->drawPoint(w, h, (*texture)[size_t(double(h + 1.f)/ky)][size_t(double(w + 1.f)/kx)]);
    }

    _drawer->swapBuffers();
}

void DrawVisitor::set_drawer(std::shared_ptr<BaseDrawer> drawer)
{
    _drawer = drawer;
}

void DrawVisitor::set_draw_manager(std::shared_ptr<DrawManager> manager)
{
    _draw_manager = manager;
}
