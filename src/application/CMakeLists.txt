set( MODULE_NAME application )

set( CPP_FILES
    application.cpp
)

add_library( ${MODULE_NAME} STATIC ${CPP_FILES} )