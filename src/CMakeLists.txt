# Ajout des sous dossiers qui représente des modules C
add_subdirectory(tsp)
add_subdirectory(visu)
add_subdirectory(core)

# On inclue les headers pour les sources
target_include_directories(${PROJECT_NAME} PUBLIC ${HEADER_DIR})

# Sources seulement présente dans l'exec
target_sources(${PROJECT_NAME}
	PRIVATE
		main.c 
)

# On link les librarie nécessaire à la compilation du projet
target_link_libraries(${PROJECT_NAME} PUBLIC tsp visu core)
