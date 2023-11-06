set( MODULE_NAME frame_buffers )

set( CPP_FILES
    frame_buffer.cpp
    z_buffer.cpp
)

add_library( ${MODULE_NAME} STATIC ${CPP_FILES} )