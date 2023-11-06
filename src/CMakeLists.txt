cmake_minimum_required( VERSION 3.10.2 )

project( lgav )

###############################################################################

set( CMAKE_INCLUDE_CURRENT_DIR ON )
set( PROJECT_CXX_STANDARD 11 )

set( CMAKE_CXX_STANDARD ${PROJECT_CXX_STANDARD} )
set( CMAKE_CXX_STANDARD_REQUIRED ON )

###############################################################################

set( CMAKE_CXX_FLAGS "-Wall -O4 -no-pie -g3 -std=c++${PROJECT_CXX_STANDARD} -fopenmp" )

###############################################################################

include_directories( . )

###############################################################################

set( CMAKE_AUTOMOC ON )
set( CMAKE_AUTORCC ON )
set( CMAKE_AUTOUIC ON )

find_package( Qt5 COMPONENTS Core Gui Widgets REQUIRED )

###############################################################################

find_library( X11_LIBRARY X11 )
find_library( GLFW_LIBRARY glfw )
find_library( OPENG_LIBRARY GL )
find_library( GLU_LIBRARY GLU )
find_library( GLEW_LIBRARY GLEW )

###############################################################################

add_subdirectory( application )
add_subdirectory( base_objects )
add_subdirectory( commands )
add_subdirectory( frame_buffers )
add_subdirectory( graphics )
add_subdirectory( gui )
add_subdirectory( lightmap )
add_subdirectory( managers )
add_subdirectory( painter )
add_subdirectory( primitives )
add_subdirectory( scene )
add_subdirectory( shaders )
add_subdirectory( shadowmap )
add_subdirectory( terrain )
add_subdirectory( visitors )

# add_subdirectory(tests)

###############################################################################

set( CPP_FILES
    main.cpp
)

###############################################################################

add_executable( ${PROJECT_NAME} ${CPP_FILES} )

###############################################################################

#set( LIBS
#    ${QT_LIBRARIES},
#    ${X11_LIBRARY},
#    ${GLFW_LIBRARY},
#    ${OPENG_LIBRARY},
#    ${GLU_LIBRARY},
#    ${GLEW_LIBRARY}
#)

###############################################################################

target_link_libraries( ${PROJECT_NAME}

    -Wl,--start-group

    application
    base_objects
    commands
    frame_buffers
    graphics
    gui
    lightmap
    managers
    painter
    primitives
    scene
    shaders
    shadowmap
    terrain
    visitors

    X11
    glfw
    GL
    GLU
    GLEW

    -Wl,--end-group
)

###############################################################################

# LD_BIND_NOW=1 valgrind --tool=callgrind ./lgav 100000000 
