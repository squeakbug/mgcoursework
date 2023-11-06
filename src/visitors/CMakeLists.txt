set( MODULE_NAME visitors )

set( CPP_FILES
    shadow_generator.cpp
    drawvisitor.cpp 
    visitor.cpp 
)

add_library( ${MODULE_NAME} STATIC ${CPP_FILES} )