#ifndef VERTEX_LAYOUT_H
#define VERTEX_LAYOUT_H

#include "glad/glad.h"

#include <stddef.h>

/**
 * \file vertex_layout.h
 * \brief Fichier contenant les structure de spécification de la disposition des attributs des vertex.
 *
 * Les \ref vertex_layout sont des données utilisé par le GPU afin qu'il puisse lire les données de vertex correctement.
 * Sans cela le GPU ne sera pas capable de comprendre les données qu'on lui envoie.
 *
 * Cette structure à pour but alors de permettre au programme de créer leurs propres attributs de vertex,
 * ou d'utiliser ceux déjà prédéfinis.
 *
 * Un \ref vertex_layout est toujours associé à une \ref mesh,
 * de cette façon lors du chargement des données de la mesh au GPU
 * nous envoyer aussi la façon de lire ces données.
 */

/**
 * \name Indices des attributs de vertex
 * \brief Disposition des index des attributs de vertex disponible
 * @{
 */
#define VERTEX_ATTR_POSITION   0
#define INSTANCE_ATTR_POSITION 1

#define INSTANCE_ATTR_LINE_P1  2
#define INSTANCE_ATTR_LINE_P2  3

#define INSTANCE_ATTR_CHAR_ID  4

/** @} */

#define MAX_VERTEX_ATTRIBUTE_AMOUNT 5

/**
 * \brief Type représentant un attribut de vertex
 */
typedef struct vertex_attr vertex_attr;

/**
 * \brief Type opaque représentant la disposition des attributs pour un vertex
 */
typedef struct vertex_layout* vertex_layout;

struct vertex_attr
{
	GLuint id;
	GLint size;
	GLenum type;
	GLboolean normalized;
	size_t offset;

	GLuint divisor;
};

/**
 * \brief Créer une dispotion de vertex personnaliser
 *
 * Permet de créer une dispotion de vertex pour personnaliser 
 * en donnant une listes d'attribut.
 *
 * \param attributes listes des attributs personnalisés
 * \param attribute_amount nombre d'attribut total
 * \param stride taille en octet de l'ensemble des attribut combiner
 * \return vertex_layout alloué en mémoire
 */
vertex_layout create_custom_layout(vertex_attr* attributes,
                                   unsigned int attribute_amount,
                                   GLsizei stride);

/**
 * \brief Créer une dispotion pour la structure \ref vertex
 * \return vertex_layout alloué en mémoire
 */
vertex_layout create_vertex_layout();

/**
 * \brief Créer une dispotion pour la structure \ref vertex_nc
 * \return vertex_layout alloué en mémoire
 */
vertex_layout create_vertex_nc_layout();

/**
 * \brief Libéère la mémoire du vertex_layout en paramêtre
 * \param layout vertex_layout à libérer
 */
void free_vertex_layout(vertex_layout layout);

/**
 * \brief Envoie les données de dispotion des vertex au GPU
 * \param layout données de dispotion à envoyer
 */
void setup_vao_attributes(vertex_layout layout);

#endif // VERTEX_LAYOUT_H
