#include <gtest/gtest.h>
#include <iostream>
#include <cmath>

#include "../../errors/math_exceptions.h"
#include "../../math/math.h"

static const float testEps = 1e-5;

TEST(TranslateTests, TranslateZeroDistance)
{
    mat4<> identity(1.f);
    vec3<> direction(0.f);

    mat4<> controlMatrix;
    controlMatrix[0][0] = 1.f;  controlMatrix[0][1] = 0.f;  controlMatrix[0][2] = 0.f;  controlMatrix[0][3] = 0.f;
    controlMatrix[1][0] = 0.f;  controlMatrix[1][1] = 1.f;  controlMatrix[1][2] = 0.f;  controlMatrix[1][3] = 0.f;
    controlMatrix[2][0] = 0.f;  controlMatrix[2][1] = 0.f;  controlMatrix[2][2] = 1.f;  controlMatrix[2][3] = 0.f;
    controlMatrix[3][0] = 0.f;  controlMatrix[3][1] = 0.f;  controlMatrix[3][2] = 0.f;  controlMatrix[3][3] = 1.f;

    identity = math<>::translate(identity, direction);

    for (size_t i = 0; i < 4; ++i)
        for (size_t j = 0; j < 4; j++)
            ASSERT_NEAR(identity[i][j], controlMatrix[i][j], testEps);
}

TEST(TranslateTests, PositiveTest)
{
    mat4<> identity(1.f);
    vec3<> direction = { 10.f, 20.f, 30.f };

    mat4<> controlMatrix;
    controlMatrix[0][0] = 1.f;  controlMatrix[0][1] = 0.f;  controlMatrix[0][2] = 0.f;  controlMatrix[0][3] = 0.f;
    controlMatrix[1][0] = 0.f;  controlMatrix[1][1] = 1.f;  controlMatrix[1][2] = 0.f;  controlMatrix[1][3] = 0.f;
    controlMatrix[2][0] = 0.f;  controlMatrix[2][1] = 0.f;  controlMatrix[2][2] = 1.f;  controlMatrix[2][3] = 0.f;
    controlMatrix[3][0] = 10.f;  controlMatrix[3][1] = 20.f;  controlMatrix[3][2] = 30.f;  controlMatrix[3][3] = 1.f;

    identity = math<>::translate(identity, direction);

    for (size_t i = 0; i < 4; i++)
        for (size_t j = 0; j < 4; j++)
            ASSERT_NEAR(identity[i][j], controlMatrix[i][j], testEps);
}

/* Не сделано */
TEST(RotateTests, RotateOnePlaneAngles)
{
    mat4<> identity(1.f);
    vec3<> direction(0.f);

    mat4<> controlMatrix;
    controlMatrix[0][0] = 1.f;  controlMatrix[0][1] = 0.f;  controlMatrix[0][2] = 0.f;  controlMatrix[0][3] = 0.f;
    controlMatrix[1][0] = 0.f;  controlMatrix[1][1] = 1.f;  controlMatrix[1][2] = 0.f;  controlMatrix[1][3] = 0.f;
    controlMatrix[2][0] = 0.f;  controlMatrix[2][1] = 0.f;  controlMatrix[2][2] = 1.f;  controlMatrix[2][3] = 0.f;
    controlMatrix[3][0] = 0.f;  controlMatrix[3][1] = 0.f;  controlMatrix[3][2] = 0.f;  controlMatrix[3][3] = 1.f;

    identity = math<>::translate(identity, direction);

    for (size_t i = 0; i < 4; ++i)
        for (size_t j = 0; j < 4; j++)
            ASSERT_FLOAT_EQ(identity[i][j], controlMatrix[i][j]);
}

/* Не сделано */
TEST(RotateTests, RotateRandomAxisAngle)
{
    mat4<> identity(1.f);
    vec3<> direction(0.f);

    mat4<> controlMatrix;
    controlMatrix[0][0] = 1.f;  controlMatrix[0][1] = 0.f;  controlMatrix[0][2] = 0.f;  controlMatrix[0][3] = 0.f;
    controlMatrix[1][0] = 0.f;  controlMatrix[1][1] = 1.f;  controlMatrix[1][2] = 0.f;  controlMatrix[1][3] = 0.f;
    controlMatrix[2][0] = 0.f;  controlMatrix[2][1] = 0.f;  controlMatrix[2][2] = 1.f;  controlMatrix[2][3] = 0.f;
    controlMatrix[3][0] = 0.f;  controlMatrix[3][1] = 0.f;  controlMatrix[3][2] = 0.f;  controlMatrix[3][3] = 1.f;

    identity = math<>::translate(identity, direction);

    for (size_t i = 0; i < 4; ++i)
        for (size_t j = 0; j < 4; j++)
            ASSERT_FLOAT_EQ(identity[i][j], controlMatrix[i][j]);
}

/* Не сделано */
TEST(RotateTests, NegativeTests)
{
    mat4<> identity(1.f);
    vec3<> direction(0.f);

    mat4<> controlMatrix;
    controlMatrix[0][0] = 1.f;  controlMatrix[0][1] = 0.f;  controlMatrix[0][2] = 0.f;  controlMatrix[0][3] = 0.f;
    controlMatrix[1][0] = 0.f;  controlMatrix[1][1] = 1.f;  controlMatrix[1][2] = 0.f;  controlMatrix[1][3] = 0.f;
    controlMatrix[2][0] = 0.f;  controlMatrix[2][1] = 0.f;  controlMatrix[2][2] = 1.f;  controlMatrix[2][3] = 0.f;
    controlMatrix[3][0] = 0.f;  controlMatrix[3][1] = 0.f;  controlMatrix[3][2] = 0.f;  controlMatrix[3][3] = 1.f;

    identity = math<>::translate(identity, direction);

    for (size_t i = 0; i < 4; ++i)
        for (size_t j = 0; j < 4; j++)
            ASSERT_FLOAT_EQ(identity[i][j], controlMatrix[i][j]);
}

/* Не сделано */
TEST(ScaleTests, PositiveTests)
{
    mat4<> identity(1.f);
    vec3<> direction = { 10.f, 20.f, 30.f };

    mat4<> controlMatrix;
    controlMatrix[0][0] = 1.f;  controlMatrix[0][1] = 0.f;  controlMatrix[0][2] = 0.f;  controlMatrix[0][3] = 0.f;
    controlMatrix[1][0] = 0.f;  controlMatrix[1][1] = 1.f;  controlMatrix[1][2] = 0.f;  controlMatrix[1][3] = 0.f;
    controlMatrix[2][0] = 0.f;  controlMatrix[2][1] = 0.f;  controlMatrix[2][2] = 1.f;  controlMatrix[2][3] = 0.f;
    controlMatrix[3][0] = 10.f;  controlMatrix[3][1] = 20.f;  controlMatrix[3][2] = 30.f;  controlMatrix[3][3] = 1.f;

    identity = math<>::translate(identity, direction);

    for (size_t i = 0; i < 4; i++)
        for (size_t j = 0; j < 4; j++)
            ASSERT_FLOAT_EQ(identity[i][j], controlMatrix[i][j]);
}

/* Не сделано */
TEST(ScaleTests, NegativeTests)
{
    mat4<> identity(1.f);
    vec3<> direction = { 10.f, 20.f, 30.f };

    mat4<> controlMatrix;
    controlMatrix[0][0] = 1.f;  controlMatrix[0][1] = 0.f;  controlMatrix[0][2] = 0.f;  controlMatrix[0][3] = 0.f;
    controlMatrix[1][0] = 0.f;  controlMatrix[1][1] = 1.f;  controlMatrix[1][2] = 0.f;  controlMatrix[1][3] = 0.f;
    controlMatrix[2][0] = 0.f;  controlMatrix[2][1] = 0.f;  controlMatrix[2][2] = 1.f;  controlMatrix[2][3] = 0.f;
    controlMatrix[3][0] = 10.f;  controlMatrix[3][1] = 20.f;  controlMatrix[3][2] = 30.f;  controlMatrix[3][3] = 1.f;

    identity = math<>::translate(identity, direction);

    for (size_t i = 0; i < 4; i++)
        for (size_t j = 0; j < 4; j++)
            ASSERT_NEAR(identity[i][j], controlMatrix[i][j], testEps);
}

/*
TEST(OrthoTest, PositiveTests)
{
    float left = -1.f, right = 1.f, top = 1.f, bottom = -1.f, far = 10.f, near = 0.1f;

    mat4<> projMatrix = math<>::ortho(left, right, bottom, top, near, far);
    
    mat4<> controlMatrix;
    controlMatrix[0][0] = 1.f;  controlMatrix[0][1] = 0.f;  controlMatrix[0][2] = -0.f;         controlMatrix[0][3] = 0.f;
    controlMatrix[1][0] = 0.f;  controlMatrix[1][1] = 1.f;  controlMatrix[1][2] = -0.f;         controlMatrix[1][3] = 0.f;
    controlMatrix[2][0] = 0.f;  controlMatrix[2][1] = 0.f;  controlMatrix[2][2] = -0.20202f;    controlMatrix[2][3] = 0.f;
    controlMatrix[3][0] = 0.f;  controlMatrix[3][1] = 0.f;  controlMatrix[3][2] = -1.0202f;     controlMatrix[3][3] = 1.f;

    for (size_t i = 0; i < 4; i++)
        for (size_t j = 0; j < 4; j++)
            ASSERT_NEAR(projMatrix[i][j], controlMatrix[i][j], testEps);


    left = -10.f; right = 1.f; top = 10.f; bottom = -1.f; far = 1000.f; near = 0.1f;

    projMatrix = math<>::ortho(left, right, bottom, top, near, far);
    
    controlMatrix[0][0] = 0.181818f;    controlMatrix[0][1] = 0.f;          controlMatrix[0][2] = 0.f;         controlMatrix[0][3] = 0.f;
    controlMatrix[1][0] = 0.f;          controlMatrix[1][1] = 0.181818f;    controlMatrix[1][2] = 0.f;         controlMatrix[1][3] = 0.f;
    controlMatrix[2][0] = 0.f;          controlMatrix[2][1] = 0.f;          controlMatrix[2][2] = -0.0020002f;  controlMatrix[2][3] = 0.f;
    controlMatrix[3][0] = 0.818182f;    controlMatrix[3][1] = -0.818182f;    controlMatrix[3][2] = -1.0002f;     controlMatrix[3][3] = 1.f;

    for (size_t i = 0; i < 4; i++)
        for (size_t j = 0; j < 4; j++)
            ASSERT_NEAR(projMatrix[i][j], controlMatrix[i][j], testEps);


    left = -10.f; right = -1.f; top = -1.f; bottom = -10.f; far = 1.f; near = 0.1f;

    projMatrix = math<>::ortho(left, right, bottom, top, near, far);
    
    controlMatrix[0][0] = 0.222222f;    controlMatrix[0][1] = 0.f;          controlMatrix[0][2] = 0.f;         controlMatrix[0][3] = 0.f;
    controlMatrix[1][0] = 0.f;          controlMatrix[1][1] = 0.222222f;    controlMatrix[1][2] = 0.f;         controlMatrix[1][3] = 0.f;
    controlMatrix[2][0] = 0.f;          controlMatrix[2][1] = 0.f;          controlMatrix[2][2] = -2.222222f;  controlMatrix[2][3] = 0.f;
    controlMatrix[3][0] = 1.222222f;    controlMatrix[3][1] = 1.222222f;    controlMatrix[3][2] = -1.222222f;  controlMatrix[3][3] = 1.f;

    for (size_t i = 0; i < 4; i++)
        for (size_t j = 0; j < 4; j++)
            ASSERT_NEAR(projMatrix[i][j], controlMatrix[i][j], testEps);
}

TEST(OrthoTest, NegativeTests)
{
    float left = 1.f, right = -1.f, top = 1.f, bottom = -1.f, far = 10.f, near = 0.1f;

    mat4<> projMatrix = math<>::ortho(left, right, bottom, top, near, far);
    
    mat4<> controlMatrix;
    controlMatrix[0][0] = -1.f;  controlMatrix[0][1] = 0.f;  controlMatrix[0][2] = -0.f;         controlMatrix[0][3] = 0.f;
    controlMatrix[1][0] = 0.f;  controlMatrix[1][1] = 1.f;  controlMatrix[1][2] = -0.f;         controlMatrix[1][3] = 0.f;
    controlMatrix[2][0] = 0.f;  controlMatrix[2][1] = 0.f;  controlMatrix[2][2] = -0.20202f;    controlMatrix[2][3] = 0.f;
    controlMatrix[3][0] = 0.f;  controlMatrix[3][1] = 0.f;  controlMatrix[3][2] = -1.0202f;     controlMatrix[3][3] = 1.f;

    for (size_t i = 0; i < 4; i++)
        for (size_t j = 0; j < 4; j++)
            ASSERT_NEAR(projMatrix[i][j], controlMatrix[i][j], testEps);
}
*/

TEST(PerspectiveTest, PositiveTests)
{
    float fov = 45.f, aspectRatio = 1.6f, far = 100.f, near = 0.1f;

    mat4<> projMatrix = math<>::perspective(math<>::radians(fov), aspectRatio, near, far);
    
    mat4<> controlMatrix;
    controlMatrix[0][0] = 1.50888f; controlMatrix[0][1] = 0.f;      controlMatrix[0][2] = -0.f;     controlMatrix[0][3] = 0.f;
    controlMatrix[1][0] = 0.f;      controlMatrix[1][1] = 2.41421f; controlMatrix[1][2] = -0.f;     controlMatrix[1][3] = 0.f;
    controlMatrix[2][0] = 0.f;      controlMatrix[2][1] = 0.f;      controlMatrix[2][2] = -1.002f;  controlMatrix[2][3] = -1.f;
    controlMatrix[3][0] = 0.f;      controlMatrix[3][1] = 0.f;      controlMatrix[3][2] = -0.2002f; controlMatrix[3][3] = 0.f;

    for (size_t i = 0; i < 4; i++)
        for (size_t j = 0; j < 4; j++)
            ASSERT_NEAR(projMatrix[i][j], controlMatrix[i][j], testEps);



    fov = 180.f; aspectRatio = 1.6f; far = 100.f; near = 0.1f;

    projMatrix = math<>::perspective(math<>::radians(fov), aspectRatio, near, far);

    controlMatrix[0][0] = 0.f;  controlMatrix[0][1] = 0.f;  controlMatrix[0][2] = -0.f;     controlMatrix[0][3] = 0.f;
    controlMatrix[1][0] = 0.f;  controlMatrix[1][1] = 0.f;  controlMatrix[1][2] = -0.f;     controlMatrix[1][3] = 0.f;
    controlMatrix[2][0] = 0.f;  controlMatrix[2][1] = 0.f;  controlMatrix[2][2] = -1.0020f; controlMatrix[2][3] = -1.f;
    controlMatrix[3][0] = 0.f;  controlMatrix[3][1] = 0.f;  controlMatrix[3][2] = -0.2002f; controlMatrix[3][3] = 0.f;

    for (size_t i = 0; i < 4; i++)
        for (size_t j = 0; j < 4; j++)
            ASSERT_NEAR(projMatrix[i][j], controlMatrix[i][j], testEps);


    fov = 30.f; aspectRatio = 2.f; far = 100.f; near = 0.1f;

    projMatrix = math<>::perspective(math<>::radians(fov), aspectRatio, near, far);

    controlMatrix[0][0] = 1.86603f; controlMatrix[0][1] = 0.f;      controlMatrix[0][2] = -0.f;     controlMatrix[0][3] = 0.f;
    controlMatrix[1][0] = 0.f;      controlMatrix[1][1] = 3.73205f; controlMatrix[1][2] = -0.f;     controlMatrix[1][3] = 0.f;
    controlMatrix[2][0] = 0.f;      controlMatrix[2][1] = 0.f;      controlMatrix[2][2] = -1.002f;  controlMatrix[2][3] = -1.f;
    controlMatrix[3][0] = 0.f;      controlMatrix[3][1] = 0.f;      controlMatrix[3][2] = -0.2002f; controlMatrix[3][3] = 0.f;

    for (size_t i = 0; i < 4; i++)
        for (size_t j = 0; j < 4; j++)
            ASSERT_NEAR(projMatrix[i][j], controlMatrix[i][j], testEps);
}

TEST(PerspectiveTest, NegativeTests)
{
    float fov = -180.f, aspectRatio = 1.6f, far = 100.f, near = 0.1f;

    mat4<> projMatrix = math<>::perspective(math<>::radians(fov), aspectRatio, near, far);
    
    mat4<> controlMatrix;
    controlMatrix[0][0] = 0.f; controlMatrix[0][1] = 0.f; controlMatrix[0][2] =  0.f;     controlMatrix[0][3] = 0.f;
    controlMatrix[1][0] = 0.f; controlMatrix[1][1] = 0.f; controlMatrix[1][2] =  0.f;     controlMatrix[1][3] = 0.f;
    controlMatrix[2][0] = 0.f; controlMatrix[2][1] = 0.f; controlMatrix[2][2] = -1.002f;  controlMatrix[2][3] = -1.f;
    controlMatrix[3][0] = 0.f; controlMatrix[3][1] = 0.f; controlMatrix[3][2] = -0.2002f; controlMatrix[3][3] = 0.f;

    for (size_t i = 0; i < 4; i++)
        for (size_t j = 0; j < 4; j++)
            ASSERT_NEAR(projMatrix[i][j], controlMatrix[i][j], testEps);


    fov = 30.f; aspectRatio = 0.f; far = 100.f; near = 0.1f;

    try
    {
        projMatrix = math<>::perspective(math<>::radians(fov), aspectRatio, near, far);
        FAIL() << "math<>::perspective with zero aspect ratio should throw an exception";
    }
    catch(MathException &ex)
    {
        
    }

    fov = 30.f; aspectRatio = 1.6f; far = 0.1f; near = 100.f;

    projMatrix = math<>::perspective(math<>::radians(fov), aspectRatio, near, far);

    controlMatrix[0][0] = 2.33253f; controlMatrix[0][1] = 0.f;      controlMatrix[0][2] = 0.f;      controlMatrix[0][3] = 0.f;
    controlMatrix[1][0] = 0.f;      controlMatrix[1][1] = 3.73205f; controlMatrix[1][2] = 0.f;      controlMatrix[1][3] = 0.f;
    controlMatrix[2][0] = 0.f;      controlMatrix[2][1] = 0.f;      controlMatrix[2][2] = 1.002f;   controlMatrix[2][3] = -1.f;
    controlMatrix[3][0] = 0.f;      controlMatrix[3][1] = 0.f;      controlMatrix[3][2] = 0.2002f;  controlMatrix[3][3] = 0.f;

    for (size_t i = 0; i < 4; i++)
        for (size_t j = 0; j < 4; j++)
            ASSERT_NEAR(projMatrix[i][j], controlMatrix[i][j], testEps);
}

TEST(DotVec4Test, DefaultTest)
{
    const size_t vectorsCnt = 4;

    vec4<> leftVectors[vectorsCnt] = 
    { 
        { 0.f, 0.f, 0.f, 0.f },
        { 10.f, 10.f, 10.f, 10.f },
        { -10.f, 20.f, -30.f, 40.f },
        { -10.f, 20.f, -30.f, 40.f }
    };

    vec4<> rightVectors[vectorsCnt] = 
    { 
        { 10.f, 20.f, 30.f, 40.f },
        { 0.f, 0.f, 0.f, 0.f },
        { -10.f, 20.f, -30.f, 40.f },
        { 10.f, -20.f, 30.f, -40.f }
    };

    float controlValues[vectorsCnt] =
    {
        0.f, 0.f, 3000.f, -3000.f
    };

    for (size_t i = 0; i < vectorsCnt; i++)
    {
        float res =  math<>::dot(leftVectors[i], rightVectors[i]);
        ASSERT_FLOAT_EQ(controlValues[i], res);
    }
    
}

TEST(DotVec3Test, DefaultTest)
{
    const size_t vectorsCnt = 4;

    vec3<> leftVectors[vectorsCnt] = 
    { 
        { 0.f, 0.f, 0.f },
        { 10.f, 10.f, 10.f },
        { -10.f, 20.f, -30.f },
        { -10.f, 20.f, -30.f }
    };

    vec3<> rightVectors[vectorsCnt] = 
    { 
        { 10.f, 20.f, 30.f },
        { 0.f, 0.f, 0.f },
        { -10.f, 20.f, -30.f },
        { 10.f, -20.f, 30.f }
    };

    float controlValues[vectorsCnt] =
    {
        0.f, 0.f, 1400.f, -1400.f
    };

    for (size_t i = 0; i < vectorsCnt; i++)
    {
        float res =  math<>::dot(leftVectors[i], rightVectors[i]);
        ASSERT_FLOAT_EQ(controlValues[i], res);
    }
    
}

TEST(CrossTest, DefaultTest)
{
    const size_t vectorsCnt = 9;

    vec3<> leftVectors[vectorsCnt] = 
    { 
        { 1.f, 0.f, 0.f },
        { 0.f, 1.f, 0.f },
        { 0.f, 0.f, 1.f },

        { 1.f, 0.f, 0.f },
        { 0.f, 1.f, 0.f },
        { 0.f, 0.f, 1.f },

	    { 1.f, 0.f, 0.f },
        { 0.f, 1.f, 0.f },
        { 0.f, 0.f, 1.f }
    };

    vec3<> rightVectors[vectorsCnt] = 
    { 
        { 1.f, 0.f, 0.f },
        { 1.f, 0.f, 0.f },
        { 1.f, 0.f, 0.f },

	    { 0.f, 1.f, 0.f },
        { 0.f, 1.f, 0.f },
        { 0.f, 1.f, 0.f },

	    { 0.f, 0.f, 1.f },
        { 0.f, 0.f, 1.f },
        { 0.f, 0.f, 1.f }
    };

    vec3<> controlValues[vectorsCnt] =
    {
        { 0.f, 0.f, 0.f },
        { 0.f, 0.f, -1.f },
        { 0.f, 1.f, 0.f },

	    { 0.f, 0.f, 1.f },
        { 0.f, 0.f, 0.f },
        { -1.f, 0.f, 0.f },

	    { 0.f, -1.f, 0.f },
        { 1.f, 0.f, 0.f },
        { 0.f, 0.f, 0.f }
    };

    for (size_t i = 0; i < vectorsCnt; i++)
    {
        vec3<> res =  math<>::cross(leftVectors[i], rightVectors[i]);
        for (size_t j = 0; j < 3; ++j)
        {
                ASSERT_FLOAT_EQ(controlValues[i][j], res[j]);
        }
    }
}

TEST(LookAtTests, DefaultTest)
{
    vec3<> dir(0.f, 0.f, -1.f);
	vec3<> pos(0.f, 0.f, 0.f);
	vec3<> up(0.f, 1.f, 0.f);

    mat4<> controlMatrix;
    controlMatrix[0][0] = 1.f;  controlMatrix[0][1] = 0.f;  controlMatrix[0][2] = 0.f;  controlMatrix[0][3] = 0.f;
    controlMatrix[1][0] = 0.f;  controlMatrix[1][1] = 1.f;  controlMatrix[1][2] = 0.f;  controlMatrix[1][3] = 0.f;
    controlMatrix[2][0] = 0.f;  controlMatrix[2][1] = 0.f;  controlMatrix[2][2] = 1.f;  controlMatrix[2][3] = 0.f;
    controlMatrix[3][0] = 0.f;  controlMatrix[3][1] = 0.f;  controlMatrix[3][2] = 0.f;  controlMatrix[3][3] = 1.f;

    mat4<> viewMatrix = math<>::lookAt(pos, dir + pos, up);

    for (size_t i = 0; i < 4; i++)
        for (size_t j = 0; j < 4; j++)
            ASSERT_FLOAT_EQ(viewMatrix[i][j], controlMatrix[i][j]);
}

TEST(LookAtTests, RandomTest)
{
    vec3<double> dir(1.f, 1.f, 0.f);
	vec3<double> pos(10.f, 20.f, 30.f);
	vec3<double> up(-1.f, 1.f, 0.f);

    mat4<double> controlMatrix;
    controlMatrix[0][0] = 0.f;      controlMatrix[0][1] = -0.707107f;   controlMatrix[0][2] = -0.707107f;   controlMatrix[0][3] = 0.f;
    controlMatrix[1][0] = 0.f;      controlMatrix[1][1] = 0.707107f;    controlMatrix[1][2] = -0.707107f;   controlMatrix[1][3] = 0.f;
    controlMatrix[2][0] = 1.f;      controlMatrix[2][1] = 0.f;          controlMatrix[2][2] = 0.f;          controlMatrix[2][3] = 0.f;
    controlMatrix[3][0] = -30.f;    controlMatrix[3][1] = -7.07107f;    controlMatrix[3][2] = 21.2132f;     controlMatrix[3][3] = 1.f;

    mat4<double> viewMatrix = math<double>::lookAt(pos, pos + dir, up);

    for (size_t i = 0; i < 4; i++)
        for (size_t j = 0; j < 4; j++)
            ASSERT_NEAR(viewMatrix[i][j], controlMatrix[i][j], 0.0001);
}

TEST(reflectTests, DefaultTest)
{
    vec3<> lightDir = { 1.f, 1.f, 1.f };
    vec3<> normal = { 1.f, 0.f, 0.f };
    vec3<> output = math<>::reflect(lightDir, normal);

    vec3<> controlVector = { -1.f, 1.f, 1.f };

    ASSERT_NEAR(output.x, controlVector.x, math<>::eps);
    ASSERT_NEAR(output.y, controlVector.y, math<>::eps);
    ASSERT_NEAR(output.z, controlVector.z, math<>::eps);
}

TEST(reflectTests, PerpendiculatToPlaneTest)
{
    vec3<> lightDir = { 0.f, 0.f, 1.f };
    vec3<> normal = { 0.f, 0.f, -1.f };
    vec3<> output = math<>::reflect(lightDir, normal);

    vec3<> controlVector = { 0.f, 0.f, -1.f };

    ASSERT_NEAR(output.x, controlVector.x, math<>::eps);
    ASSERT_NEAR(output.y, controlVector.y, math<>::eps);
    ASSERT_NEAR(output.z, controlVector.z, math<>::eps);
}

TEST(reflectTests, RandomTest)
{
    vec3<> lightDir = { 2.5f, -2.5f, 10.f };
    vec3<> normal = { 0.5f, -0.5f, 0.25f };
    vec3<> output = math<>::reflect(lightDir, normal);

    vec3<> controlVector = { -2.5f, 2.5f, 7.5f };

    ASSERT_NEAR(output.x, controlVector.x, math<>::eps);
    ASSERT_NEAR(output.y, controlVector.y, math<>::eps);
    ASSERT_NEAR(output.z, controlVector.z, math<>::eps);
}

TEST(inverse3Tests, IdentityTest)
{
    mat3<> source(1.f);
    mat3<> output = math<>::inverse(source);

    mat3<> controlMat(1.f);

    for (size_t i = 0; i < 3; i++)
    {
        for (size_t j = 0; j < 3; j++)
            ASSERT_NEAR(output[i][j], controlMat[i][j], math<>::eps);
    }
    
}

TEST(inverse3Tests, RandomTest)
{
    mat3<> source;
    source[0][0] = 1.f;     source[0][1] = 2.f;     source[0][2] = 4.f;
	source[1][0] = 6.f;     source[1][1] = 4.f;     source[1][2] = 2.f;
	source[2][0] = 3.f;     source[2][1] = 2.f;     source[2][2] = 6.f;
    mat3<> output = math<>::inverse(source);

    mat3<> controlMat;
    controlMat[0][0] = -0.5f;   controlMat[0][1] = 0.1f;   controlMat[0][2] = 0.3f;
    controlMat[1][0] = 0.75f;   controlMat[1][1] = 0.15f;  controlMat[1][2] = -0.55f;
    controlMat[2][0] = 0.f;     controlMat[2][1] = -0.1f;  controlMat[2][2] = 0.2f;

    for (size_t i = 0; i < 3; i++)
    {
        for (size_t j = 0; j < 3; j++)
            ASSERT_NEAR(output[i][j], controlMat[i][j], math<>::eps);
    }
    
}

TEST(inverse4Tests, RandomTest)
{
    mat4<> source;
    source[0][0] = 1.f;     source[0][1] = 3.f;     source[0][2] = 2.f;     source[0][3] = 4.f;
	source[1][0] = 2.f;     source[1][1] = 3.f;     source[1][2] = 1.f;     source[1][3] = 1.f;
	source[2][0] = 4.f;     source[2][1] = 1.f;     source[2][2] = 2.f;     source[2][3] = 4.f;
    source[3][0] = 3.f;     source[3][1] = 5.f;     source[3][2] = 3.f;     source[3][3] = 2.f;
    mat4<> output = math<>::inverse(source);

    mat4<> controlMat;
    controlMat[0][0] = -0.2549f;    controlMat[0][1] = 0.31372f;     controlMat[0][2] = 0.21568f;     controlMat[0][3] = -0.07843f;
	controlMat[1][0] = 0.11764f;    controlMat[1][1] = 0.47058f;     controlMat[1][2] = -0.17647f;    controlMat[1][3] = -0.11764f;
	controlMat[2][0] = -0.13725f;   controlMat[2][1] = -1.21568f;    controlMat[2][2] = 0.03921f;     controlMat[2][3] = 0.80392f;
    controlMat[3][0] = 0.29411f;    controlMat[3][1] = 0.17647f;     controlMat[3][2] = 0.05882f;     controlMat[3][3] = -0.29411f;

    for (size_t i = 0; i < 4; i++)
    {
        for (size_t j = 0; j < 4; j++)
            ASSERT_NEAR(output[i][j], controlMat[i][j], 1e-3);
    }
    
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
