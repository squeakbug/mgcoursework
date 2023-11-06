set( MODULE_NAME painter )

set ( CPP_FILES
    gradient.cpp

    base_painter.cpp
    default_painter.cpp
    gradient_painter.cpp
)

add_library( ${MODULE_NAME} STATIC ${CPP_FILES} )