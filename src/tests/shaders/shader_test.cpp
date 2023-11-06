#include <gtest/gtest.h>
#include <iostream>

#include "vertex_shader.h"
#include "vertex.h"

static const float testEps = 1e-5;

TEST(VertexShaderTest, DefaultTest)
{
    VertexShader shader;

    vec3<> clr = { 0.f, 0.f, 0.f };
    vec3<> pos = { 0, 0, 0.5f };
    vec3<> normal = { 0.f, 0.f, 1.f };
    Vertex vertex(clr, pos, normal);

    mat4<> modelMatrix(1.f);

    /* Матрица проекции для math<>:: perspective(radians(45.f), 1.6f, 0.1f, 100.f)*/
    mat4<> projMatrix;
    projMatrix[0][0] = 1.50888f;    projMatrix[0][1] = 0.f;         projMatrix[0][2] = 0.f;         projMatrix[0][3] = 0.f;
    projMatrix[1][0] = 0.f;         projMatrix[1][1] = 2.41421f;    projMatrix[1][2] = 0.f;         projMatrix[1][3] = 0.f;
    projMatrix[2][0] = 0.f;         projMatrix[2][1] = 0.f;         projMatrix[2][2] = -1.0002f;    projMatrix[2][3] = -1.f;
    projMatrix[3][0] = 0.f;         projMatrix[3][1] = 0.f;         projMatrix[3][2] = -0.20002;    projMatrix[3][3] = 0.f;

    /* Матрица вида камеры для math<>:: lookAt(dir: (0.f, 0.f, -1.f), pos: (-10.f, -10.f, 255.f), up: 0.f, 1.f, 0.f)) */
    mat4<> viewMatrix;
    viewMatrix[0][0] = 1.f;     viewMatrix[0][1] = 0.f;     viewMatrix[0][2] = 0.f;     viewMatrix[0][3] = 0.f;
    viewMatrix[1][0] = 0.f;     viewMatrix[1][1] = 1.f;     viewMatrix[1][2] = 0.f;     viewMatrix[1][3] = 0.f;
    viewMatrix[2][0] = 0.f;     viewMatrix[2][1] = 0.f;     viewMatrix[2][2] = 1.f;     viewMatrix[2][3] = 0.f;
    viewMatrix[3][0] = 10.f;    viewMatrix[3][1] = 10.f;    viewMatrix[3][2] = -255.f;  viewMatrix[3][3] = 1.f;

    Vertex output = shader.calculate(vertex, projMatrix, viewMatrix, modelMatrix);

    /* При переходе в глобальное пространство нормаль не поменялась */
    ASSERT_NEAR(output.normal.x, 0.f, testEps);
    ASSERT_NEAR(output.normal.y, 0.f, testEps);
    ASSERT_NEAR(output.normal.z, 1.f, testEps);

    ASSERT_NEAR(output.position.x, 0.059288f, testEps);
    ASSERT_NEAR(output.position.y, 0.094860f, testEps);
    ASSERT_NEAR(output.position.z, 0.999414f, testEps);
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}