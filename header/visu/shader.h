#ifndef SHADER_H
#define SHADER_H

#include "visu/camera.h"
#include "visu/color.h"

#include "glad/glad.h"

#include <stddef.h>

/**
 * \file shader.h
 * \brief Structure représentant les programme GPU (shader) OpenGL.
 *
 * Structure représentant les programme GPU (shader) OpenGL
 * et ses varaibles uniform modifiable via le programme C.
 */

/**
* \brief Type représentant un programme GPU (shader)
*/
typedef struct shader* shader;

/**
 * \name Shaders globaux
 * \brief Liste des shaders chargés au démarrage du moteur de rendu
 * @{
 */
extern shader global_default_shader;
extern shader global_circle_shader;
/** @} */

/**
* \brief Créer les shader globaux
*/
void create_global_shaders();

/**
* \brief Libère la mémoire alloué par les shaders globaux
*/
void free_global_shaders();

/**
* \brief Compile le shader passer en praramêtre et renvoie son ID
*
* \param path chemin de fichier vers le shader glsl
* \param type type de shader à compiler (vertex ou fragment shader)
* \param out variable de retour pour l'ID du shader compiler
* \return statut de la compilation, 0 shader OK, autre erreur lors de la compilation
*/
int compile_shader(const char* path, GLuint type, GLuint* out);

/**
* \brief Assemble des shaders pour créer un programme GPU utilisable
*
* Prend une listes d'ID de shader déjà compiler, et les assemble pour créer un programme GPU utilisable.
*
* \param shaders listes des shaders à assembler
* \param size nombre de shader total à assembler
* \param out variable de retour pour l'ID du programme GPU
* \return statut de la compilation, 0 shader OK, autre erreur lors de la compilation
*/
int compile_shader_program(GLuint* shaders, unsigned int size, GLuint* out);

/**
* \brief Créer un shader à partir du code de son vertex et fragment.
* \param vert_shader_path chemin de fichier vers le vertex shader glsl
* \param frag_shader_path chemin de fichier vers le fragment shader glsl
* \return shader créée
*/
shader create_shader(const char* vert_shader_path, const char* frag_shader_path);

/**
* \brief Libère la mémoire alloué par le shader
* \param s shader à libérer
*/
void free_shader(shader s);

/**
* \brief Lie au GPU le shader s en paramêtre
* \param s shader à lier
*/
void bind_shader(shader s);

/**
* \brief Dé-Lie le shader actuelle lié
*/
void unbind_shader();

/**
* \brief Envoie les données de la caméra au shader passer en paramêtre
*
* Envoie les données de la caméra au shader passer en paramêtre
* via les variable uniforme du shader si celle si sont utilisées.
*
* \param s shader auquel envoyer les données
* \param c caméra données de la caméra
*/
void set_shader_camera(shader s, camera c);


/**
* \brief Envoie les données de position au shader passer en paramêtre
*
* Envoie les données de position au shader passer en paramêtre
* via les variable uniforme du shader si celle si sont utilisées.
*
* \param s shader auquel envoyer les données
* \param x position x
* \param y position y
* \param z position z
*/
void set_shader_model_pos(shader s, float x, float y);

/**
* \brief Envoie les données de scale au shader passer en paramêtre
*
* Envoie les données scale au shader passer en paramêtre
* via les variable uniforme du shader si celle si sont utilisées.
*
* \param s shader auquel envoyer les données
* \param sx scale x
* \param sy scale y
* \param sz scale z
*/
void set_shader_model_scale(shader s, float sx, float sy);

/**
* \brief Envoie les données de couleur au shader passer en paramêtre
*
* Envoie les données couleur au shader passer en paramêtre
* via les variable uniforme du shader si celle si sont utilisées.
*
* \param s shader auquel envoyer les données
* \param r valeur rouge entre 0 et 255
* \param g valeur vert entre 0 et 255
* \param b valeur bleu entre 0 et 255
*/
void set_shader_model_color(shader s, unsigned char r,
                                      unsigned char g,
                                      unsigned char b);

/**
* \brief Envoie les données de la texture à l'unit donner en paramêtre
*
* \param s shader auquel envoyer les données
* \param unit index de position du buffer GPU de la texture
*/
void set_shader_texture_unit(shader s, GLint unit);

void set_shader_circle_color(shader s, color c);
void set_shader_circle_radius(shader s, float r);
void set_shader_circle_border_color(shader s, color c);
void set_shader_circle_border_thinkness(shader s, float t);

#endif // SHADER_H
