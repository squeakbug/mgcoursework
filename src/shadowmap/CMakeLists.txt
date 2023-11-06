set( MODULE_NAME shadowmap )

set( CPP_FILES
    shadowmap_pool.cpp
)

add_library( ${MODULE_NAME} STATIC ${CPP_FILES} )