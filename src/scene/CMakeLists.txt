set( MODULE_NAME scene )

set( CPP_FILES
    scene_selector.cpp
    scene.cpp
)

add_library( ${MODULE_NAME} STATIC ${CPP_FILES} )