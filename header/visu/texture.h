#ifndef TEXTURE_H
#define TEXTURE_H

#include "glad/glad.h"

/**
 * \file texture.h
 * \brief Structure représentant les données d'une texture charger dans le GPU
 *
 * Texture utiliser notamment pour chager les images de la skybox dans le GPU.
 */

/**
* \brief Type représentant une texture charger dans le GPU
*/
typedef struct texture* texture;

/**
 * \name Textures globales
 * \brief Liste des textures chargés au démarrage du moteur de rendu
 * @{
 */
// extern texture global_default_texture;
/** @} */

/**
* \brief Créer les textures globales
*/
void create_global_textures();

/**
* \brief Libère la mémoire des textures globales
*/
void free_global_textures();

/**
* \brief Créer une texture de type cube map avec les images données en paramêtre.
*
* \attention il faut donner exactement 6 chemin de fichier valide !
*
* \param faces_images_paths listes des chemin de fichier des images de la cube map
* \return texture dont la mémoire à été alloué
*/
texture create_texture(const char* path);

/**
* \brief Libère la mémoire de la texture en paramêtre
* \param t texture à libérer
*/
void free_texture(texture t);

/**
* \brief Lie au GPU la texture passer en paramêtre
*
* Lie la texture au GPU et l'active à l'index \a unit donné en paramêtre.
*
* \param t texture à lier
* \param unit index ou placer la texture
*/
void bind_texture(texture t, GLuint unit);

/**
* \brief Dé-lie la texture passer en paramêtre du GPU
* \param t texture à dé-lier
*/
void unbind_texture(texture t);


#endif // TEXTURE_H
