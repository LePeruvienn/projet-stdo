# CMake - Liaison de la libaririe STB pour le chargement d'image

add_library(stb_image INTERFACE)
target_include_directories(stb_image INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include)

