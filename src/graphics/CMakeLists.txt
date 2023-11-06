set( MODULE_NAME graphics )

set( CPP_FILES
    base_drawer.cpp
    graphicsfactory.cpp

    qt/qt_drawer.cpp
    qt/qt_factory.cpp

    glfw/glfw_drawer.cpp
    glfw/glfw_factory.cpp

    dynamic_qt/dynamic_qt_drawer.cpp
    dynamic_qt/dynamic_qt_factory.cpp
)

add_library( ${MODULE_NAME} STATIC ${CPP_FILES} )

qt5_use_modules( ${MODULE_NAME} Widgets )