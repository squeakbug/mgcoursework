set( MODULE_NAME primitives )

set( CPP_FILES
    camera.cpp
    clipping_space.cpp
    details.cpp
    ebo_setuper.cpp
    framemodel.cpp
    iterrain_object.cpp
    lightsource.cpp
    polygonmodel.cpp
    sceneobject.cpp
    terrain_frame_model.cpp
    terrain_polygon_model.cpp

    clipping_spaces/piramid_clipping_space.cpp
    clipping_spaces/rect_clipping_space.cpp

    ebo_setupers/from_grid_setuper.cpp

    light_types/direct_light_source.cpp
)

add_library( ${MODULE_NAME} STATIC ${CPP_FILES} )