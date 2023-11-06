enable_testing()

project(math_testing)
set(TARGET ${PROJECT_NAME})

find_package(GTest)
include(GoogleTest)

add_executable(${TARGET} 
    math_test.cpp
)

target_link_libraries(${TARGET} 
    -Wl,--start-group

    base_objects
    frame_buffers
    graphics
    lightmap
    painter
    primitives
    scene
    shaders
    terrain

    X11
    glfw
    GL
    GLU
    GLEW
    GTest::GTest

    -Wl,--end-group
)

gtest_discover_tests(${TARGET})