#ifndef READ_FILE_H
#define READ_FILE_H

#include <stddef.h>


/**
 * \file read_file.h
 * \brief Fichier implémentant des fonction permettant de lire des fichier sur le système.
 */

/**
 * \brief Lit le fichier binaire en paramêtre
 * \param path chemin vers le fichier à lire
 * \param out_size varaible de sortie pour la taille du fichier lu
 * \return le buffer d'octet du fichier
 */
unsigned char* read_file_bin(const char* path, size_t* out_size);

/**
 * \brief Lit le fichier textuelle en paramêtre
 * \param path chemin vers le fichier à lire
 * \return le buffer d'octet du fichier
 */
char* read_file_txt(const char* path);

#endif // READ_FILE_H
