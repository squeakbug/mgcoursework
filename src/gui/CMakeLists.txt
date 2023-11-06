set( MODULE_NAME gui )

set( CPP_FILES
color_selector.cpp
    color_edit_record.cpp
    direct_light_setup_widget.cpp
    light_manager_widget.cpp
    gradient_slider.cpp
    mainwindow.cpp
)

set( MOC_SRC_FILES
    color_selector.h
    color_edit_record.h
    direct_light_setup_widget.h
    light_manager_widget.h
    gradient_slider.h
    mainwindow.h
)

set( UIC_SRC_FILES
    direct_light_setup_widget.ui
    light_manager_widget.ui
    mainwindow.ui
)

add_library( ${MODULE_NAME} STATIC ${CPP_FILES} ${MOC_SRC_FILES} ${UIC_SRC_FILES} )

qt5_use_modules( ${MODULE_NAME} Widgets )