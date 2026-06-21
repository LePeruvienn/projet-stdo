#ifndef DEBUG_H
#define DEBUG_H

/**
 * \file debug.h
 * \brief Ficher fournissant des macro afin de détecter les érreurs OpenGL rapidement.
 *
 * Ce fichier des macros de debug qui permet de récupérer les érreurs OpenGL (si il y en as)
 * après l'appel d'une fonction.
 *
 * Si le define `DEBUG_ENABLED` est à `0`, alors la vérification ne se fera pas,
 * et la macro n'aura pas d'impact performance.
 */

#define DEBUG_ENABLED 1

#if DEBUG_ENABLED

	#include "utils/logger.h"
	#include "glad/glad.h"

	#include <stdlib.h>

	#define GL_CALL(func) \
		do \
		{ \
			func; \
			GLenum err;\
			while ((err = glGetError()) != GL_NO_ERROR) \
			{ \
				LOG_ERROR("OpenGL error after %x | %s", err, #func); \
			}\
		} \
		while(0)

#else

	#define GL_CALL(func) func

#endif

#endif // DEBUG_H
