#ifndef MESH_H
#define MESH_H

#include "vertex.h"
#include "vertex_layout.h"

/**
 * \file mesh.h
 * \brief Structure représentant les données d'un modèle 3D
 *
 * Le type `mesh` représente les données de \ref vertex alloué sur la RAM.
 * L'ensemble de ces vertex représente un modèle 3D.
 *
 * Chaque mesh peut avoir une structure de vertex différente (avec normal, sans normal).
 */

/**
* \brief Type représentant les données de vertex d'un modèle 3D.
*/
typedef struct mesh* mesh;

/**
* \brief Créer les données de vertex d'un carré
* \return mesh vertex du carré
*/
mesh create_quad();
mesh create_quad2();

/**
* \brief Créer les données de vertex d'un cercle
* \return mesh vertex du cercle
*/
mesh create_circle_fan(unsigned int segments);

/**
* \brief Créer les données de vertex pour un ensemble de lignes
* \param vertices différent points des lignes
* \param size nombre de point total
* \return mesh vertex des lignes
*/
mesh create_line(vertex* vertices, unsigned int size);

/**
* \brief libère la mémoire de la mesh passer en paramêtre
* \param m mesh à libérer
*/
void free_mesh(mesh m);

/**
* \brief charge les données de la mesh dans le GPU
* \param m mesh à charger
*/
void load_mesh_data(mesh m);

/**
* \brief Donne le nombre d'indice total de la mesh en paramêtre
* \param m mesh cible
*/
unsigned int get_mesh_indices_amount(mesh m);

/**
* \brief Récupère le \ref vertex_layout de la mesh en paramêtre
* \param m mesh cible
*/
vertex_layout get_mesh_vertex_layout(mesh m);

#endif // MESH_H
