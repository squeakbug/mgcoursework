set( MODULE_NAME commands )

set( CPP_FILES
    basecommand.cpp
    camera_command.cpp
    drawcommand.cpp
    landscape_commands.cpp
    light_sources_commands.cpp
    scene_commands.cpp
)

add_library( ${MODULE_NAME} STATIC ${CPP_FILES} )

qt5_use_modules( ${MODULE_NAME} Widgets )