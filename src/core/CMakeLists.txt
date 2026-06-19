# Get current dir name that is gonna be used as the current lib name
get_filename_component(DIR_NAME ${CMAKE_CURRENT_SOURCE_DIR} NAME)

set(LIB_NAME ${DIR_NAME})

# Création de la librairie
add_library(${LIB_NAME} STATIC)

# Ajout des includes de la librairie
target_include_directories(${LIB_NAME} PUBLIC ${HEADER_DIR})

# On récupère tout les .c dans le dossier
file(GLOB CORE_FILES CONFIGURE_DEPENDS "*.c")

# On les ajoute comme fichier sources de la lib
target_sources(${LIB_NAME} PRIVATE ${CORE_FILES})
