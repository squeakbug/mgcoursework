set( MODULE_NAME terrain )

set( CPP_FILES
    grid_generator.cpp
    grid_loader_director.cpp
    grid_loader.cpp
    grid_saver.cpp
    grid.cpp
    ilandscape_mask.cpp
    terrainblock.cpp

    generators/dsgenerator.cpp
    generators/mdsgenerator.cpp
    generators/pngenerator.cpp
    generators/spngenerator.cpp
    generators/new_dsgenerator.cpp

    grid_loaders/file_grid_loader_director.cpp
    grid_loaders/file_grid_loader.cpp
    grid_loaders/stb_image.cpp

    grid_savers/file_grid_saver.cpp
    grid_savers/stb_image_write.cpp

    landscape_masks/default_landscape_mask.cpp
    landscape_masks/hill_mask_decorator.cpp
    landscape_masks/torus_mask_decorator.cpp
    landscape_masks/smooth_mask_decorator.cpp
)

add_library( ${MODULE_NAME} STATIC ${CPP_FILES} )