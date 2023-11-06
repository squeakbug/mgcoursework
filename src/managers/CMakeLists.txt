set( MODULE_NAME managers )

set( CPP_FILES
    basemanager.cpp
    drawmanager.cpp
    scenemanager.cpp
    terrainmanager.cpp
)

add_library( ${MODULE_NAME} STATIC ${CPP_FILES} )