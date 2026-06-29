# Get current dir name that is gonna be used as the current lib name
get_filename_component(DIR_NAME ${CMAKE_CURRENT_SOURCE_DIR} NAME)

set(LIB_NAME ${DIR_NAME})

# Création de la librairie
add_library(${LIB_NAME} STATIC)

# Flags de compilation
target_compile_options(${LIB_NAME} PRIVATE -Wall -Werror -Wextra)

# Ajout des includes de la librairie
target_include_directories(${LIB_NAME} PUBLIC ${HEADER_DIR})

# Fichiers sources de la librairie
target_sources(${LIB_NAME}
	PRIVATE
		fields.c
		file.c
		parser.c
		section.c
		section_unstream.c
		instance.c
)

# On link les librarie nécessaire à la compilation du projet
target_link_libraries(${LIB_NAME} PUBLIC m)
