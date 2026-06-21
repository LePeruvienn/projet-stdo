#ifndef VERTEX_H
#define VERTEX_H

/**
 * \file vertex.h
 * \brief Fichier contenant les différent structure de vertex utilisable
 */

/**
 * \brief Type pour les vertex avec position et couleur,
 */
typedef struct vertex vertex;

/**
 * \brief Type pour les vertex avec position, couleur et normales.
 */
typedef struct vertex_nc vertex_nc;

struct vertex
{
	float x, y;
};

#endif // VERTEX_H
