# CMakeLists.txt pour la liaison des librairie nécessaire à la compilation

# Ajout des libarie présente en locale
add_subdirectory(glad)
add_subdirectory(stb)

# Recherche des paquets nécessaire à la compilation du projet
set(OpenGL_GL_PREFERENCE GLVND)
find_package(OpenGL REQUIRED)

find_package(glfw3 CONFIG QUIET)

if(NOT glfw3_FOUND)

	if(NOT EXISTS "${CMAKE_SOURCE_DIR}/libs/GLFW/CMakeLists.txt")
		message(FATAL_ERROR "GLFW submodule missing, run : git submodule update --init --recursive")
	endif()

	add_subdirectory(GLFW)
endif()

