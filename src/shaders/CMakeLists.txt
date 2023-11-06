set( MODULE_NAME shaders )

set( CPP_FILES
    fragment_shader.cpp
    vertex_shader.cpp

    fragment_shaders/gouraud_fragment_shader.cpp
    fragment_shaders/phong_fragment_shader.cpp
    fragment_shaders/simple_fragment_shader.cpp
)

add_library( ${MODULE_NAME} STATIC ${CPP_FILES} )