#include <gtest/gtest.h>

#include "../../terrain/grid.h"
#include "../../terrain/terrainblock.h"
#include "../../primitives/terrain_polygon_model.h"
#include "../../primitives/terrain_frame_model.h"
#include "../../terrain/generators/default_generator.h"
#include "../../terrain/generators/inclined_plane_generator.h"
#include "../../terrain/landscape_masks/default_landscape_mask.h"
#include "../../terrain/landscape_masks/smooth_mask_decorator.h"
#include "../../painter/default_painter.h"

class TerrainBlockTest : public ::testing::Test
{
protected:
    TerrainBlockTest()
        : defaultBlock(new TerrainBlock())
    {

    }

    virtual void SetUp()
    {
        defaultBlock->setLandscapeMask(std::shared_ptr<ILandscapeMask>(new DefaultLandscapeMask()));
        defaultBlock->set_generator(std::shared_ptr<GridGenerator>(new DefaultGenerator));
        defaultBlock->generate_grid(defaultSize,  defaultSize);
        defaultBlock->setPainter(std::shared_ptr<BasePainter>(new DefaultPainter()));
        defaultBlock->setMaxHeight(1.f);
    }

    virtual void TearDown()
    {

    }

    std::shared_ptr<TerrainBlock> defaultBlock;

public:
    static constexpr size_t defaultSize = 32;
};

/* Тест на правильность формирование сетки */
TEST_F(TerrainBlockTest, SimpleRibsFormingTest)
{
    const size_t testSize = 2;

    defaultBlock->set_generator(std::shared_ptr<GridGenerator>(new InclinedPlaneGenerator));
    defaultBlock->generate_grid(testSize,  testSize);
    std::shared_ptr<FrameModel> model = defaultBlock->to_frame_model();

    const std::shared_ptr<Details> details = model->get_details();
    std::vector<Rib> ribs = details->get_ribs();

    ASSERT_EQ(ribs.size(), 5);

    ASSERT_EQ(ribs[0].indx1, 0);    ASSERT_EQ(ribs[0].indx2, 1);
    ASSERT_EQ(ribs[1].indx1, 2);    ASSERT_EQ(ribs[1].indx2, 3);
    ASSERT_EQ(ribs[2].indx1, 0);    ASSERT_EQ(ribs[2].indx2, 2);
    ASSERT_EQ(ribs[3].indx1, 1);    ASSERT_EQ(ribs[3].indx2, 3);
    ASSERT_EQ(ribs[4].indx1, 2);    ASSERT_EQ(ribs[4].indx2, 1);
}

/* Тест на правильность формирование сетки */
TEST_F(TerrainBlockTest, ApprovedRibsFormingTest)
{
    const size_t testSize = 3;

    defaultBlock->set_generator(std::shared_ptr<GridGenerator>(new InclinedPlaneGenerator));
    defaultBlock->generate_grid(testSize,  testSize);
    std::shared_ptr<FrameModel> model = defaultBlock->to_frame_model();

    const std::shared_ptr<Details> details = model->get_details();
    std::vector<Rib> ribs = details->get_ribs();

    ASSERT_EQ(ribs.size(), 16);

    ASSERT_EQ(ribs[0].indx1, 0);    ASSERT_EQ(ribs[0].indx2, 1);    ASSERT_EQ(ribs[1].indx1, 1);    ASSERT_EQ(ribs[1].indx2, 2);
    ASSERT_EQ(ribs[2].indx1, 3);    ASSERT_EQ(ribs[2].indx2, 4);    ASSERT_EQ(ribs[3].indx1, 4);    ASSERT_EQ(ribs[3].indx2, 5);
    ASSERT_EQ(ribs[4].indx1, 6);    ASSERT_EQ(ribs[4].indx2, 7);    ASSERT_EQ(ribs[5].indx1, 7);    ASSERT_EQ(ribs[5].indx2, 8);

    ASSERT_EQ(ribs[6].indx1, 0);    ASSERT_EQ(ribs[6].indx2, 3);    ASSERT_EQ(ribs[7].indx1, 3);    ASSERT_EQ(ribs[7].indx2, 6);
    ASSERT_EQ(ribs[8].indx1, 1);    ASSERT_EQ(ribs[8].indx2, 4);    ASSERT_EQ(ribs[9].indx1, 4);    ASSERT_EQ(ribs[9].indx2, 7);
    ASSERT_EQ(ribs[10].indx1, 2);   ASSERT_EQ(ribs[10].indx2, 5);   ASSERT_EQ(ribs[11].indx1, 5);   ASSERT_EQ(ribs[11].indx2, 8);

    ASSERT_EQ(ribs[12].indx1, 3);   ASSERT_EQ(ribs[12].indx2, 1);   ASSERT_EQ(ribs[13].indx1, 6);   ASSERT_EQ(ribs[13].indx2, 4);
    ASSERT_EQ(ribs[14].indx1, 4);   ASSERT_EQ(ribs[14].indx2, 2);   ASSERT_EQ(ribs[15].indx1, 5);   ASSERT_EQ(ribs[15].indx2, 7);
}

/* Тест на правильное генерирования поверхности - плоскости */
TEST_F(TerrainBlockTest, StraigthPlaneNormalTest)
{
    defaultBlock->set_generator(std::shared_ptr<GridGenerator>(new InclinedPlaneGenerator(0.f, 0.f, 1.f, -1.f)));
    defaultBlock->generate_grid(defaultSize,  defaultSize);

    std::shared_ptr<PolygonModel> model = defaultBlock->to_polygon_model();
    for (auto vert : model->VBO)
    {
        ASSERT_FLOAT_EQ(vert->normal.x, 0.f);
        ASSERT_FLOAT_EQ(vert->normal.y, 0.f);
        ASSERT_FLOAT_EQ(vert->normal.z, 1.f);

        ASSERT_FLOAT_EQ(vert->position.z, 1.f);
    }
}

/* Тест на правильное генерирования поверхности - плоскости */
TEST_F(TerrainBlockTest, SmoothLandscapeMaskRadius1Test)
{
    defaultBlock->set_generator(std::shared_ptr<GridGenerator>(new InclinedPlaneGenerator(0.f, 0.f, 1.f, -1.f)));
    std::shared_ptr<ILandscapeMask> mask(new DefaultLandscapeMask());
    mask = std::shared_ptr<ILandscapeMask>(new SmoothMaskDecorator(mask, 1, 10));
    defaultBlock->setLandscapeMask(mask);
    defaultBlock->generate_grid(defaultSize,  defaultSize);

    std::shared_ptr<Grid> grid = defaultBlock->get_grid();
    for (size_t i = 0; i < grid->height(); ++i)
    {
        for (size_t j = 0; j < grid->height(); ++j)
        {
            ASSERT_FLOAT_EQ((*grid)[i][j], 1.f);
        }
    }
}

/* Тест на правильное генерирования поверхности - плоскости */
TEST_F(TerrainBlockTest, SmoothLandscapeMaskRadius2Test)
{
    defaultBlock->set_generator(std::shared_ptr<GridGenerator>(new InclinedPlaneGenerator(0.f, 0.f, 1.f, -1.f)));
    std::shared_ptr<ILandscapeMask> mask(new DefaultLandscapeMask());
    mask = std::shared_ptr<ILandscapeMask>(new SmoothMaskDecorator(mask, 2, 10));
    defaultBlock->setLandscapeMask(mask);
    defaultBlock->generate_grid(defaultSize,  defaultSize);

    std::shared_ptr<Grid> grid = defaultBlock->get_grid();
    for (size_t i = 0; i < grid->height(); ++i)
    {
        for (size_t j = 0; j < grid->height(); ++j)
        {
            ASSERT_FLOAT_EQ((*grid)[i][j], 1.f);
        }
    }
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
