set( MODULE_NAME lightmap )

set( CPP_FILES
    iprocedural_lightmapping.cpp
    lightmap_generator.cpp
    lightmap_pool.cpp
)

add_library( ${MODULE_NAME} STATIC ${CPP_FILES} )