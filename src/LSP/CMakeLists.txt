# Get current dir name that is gonna be used as the current lib name
get_filename_component(DIR_NAME ${CMAKE_CURRENT_SOURCE_DIR} NAME)

set(LIB_NAME ${DIR_NAME})

# Création de la librairie
add_library(${LIB_NAME} STATIC)

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
)
