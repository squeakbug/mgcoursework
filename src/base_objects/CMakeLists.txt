set( MODULE_NAME base_objects )

set( CPP_FILES
    material_property.cpp
    rectangle.cpp
    rib.cpp
    vertex.cpp
    water_vertex.cpp
)

add_library( ${MODULE_NAME} STATIC ${CPP_FILES} )