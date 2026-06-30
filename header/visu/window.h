#ifndef WINDOW_H
#define WINDOW_H

#include "visu/camera.h"

#include <stdbool.h>

/**
 * \file window.h
 * \brief Abstraction de la gestion de la fenêtre et du contexte OpenGL.
 *
 * Ce fichier décrit une interface pour créer, manipuler et détruire
 * une fenêtre d'affichage. Il encapsule les appels à la bibliothèque
 * GLFW pour éviter d'exposer ces détails au reste du programme.
 */

/**
 * \brief Pointeur représentant la structure et l'état d'une fenêtre.
 */
typedef struct window_s* window;

typedef struct mouse_status mouse_status;

struct mouse_status
{
	float x, y;
	int left_click;
	int right_click;
};

/**
 * \brief Crée et initialise une nouvelle fenêtre d'affichage.
 *
 * Cette fonction crée la fenêtre avec les dimensions données et initialise 
 * le contexte OpenGL associé.
 *
 * \param width Largeur logique initiale de la fenêtre en pixels.
 * \param height Hauteur logique initiale de la fenêtre en pixels.
 * \param title Chaîne de caractères affichée comme titre de la fenêtre.
 * \return Un pointeur \a window vers la fenêtre créée, ou NULL en cas d'échec.
 */
window create_window(int width, int height, const char* title);

/**
 * \brief Détruit la fenêtre et libère la mémoire associée.
 *
 * Ferme proprement la fenêtre et détruit le contexte OpenGL pour 
 * éviter toute fuite de mémoire.
 *
 * \param w La fenêtre à détruire.
 */
void free_window(window w);

/**
 * \brief Vérifie si la fenêtre a reçu un signal de fermeture.
 *
 * Permet de savoir si l'utilisateur a cliqué sur la croix ou fait un 
 * raccourci pour fermer l'application.
 *
 * \param w La fenêtre à vérifier.
 * \return true si la fenêtre doit se fermer, false sinon.
 */
bool window_should_close(window w);

/**
 * \brief Met à jour l'affichage et traite les événements de la fenêtre.
 *
 * Cette fonction intervertit les buffers de rendu (swap buffers) et 
 * dépile les événements en attente (clavier, souris, redimensionnement).
 *
 * \param w La fenêtre à mettre à jour.
 */
void window_update_events(window w);

/**
 * \brief Met en pause le processus en attendant des événements.
 *
 * Utile pour limiter l'utilisation du processeur (limitation de FPS) 
 * lorsqu'aucune mise à jour n'est requise immédiatement.
 *
 * \param w La fenêtre concernée.
 * \param timeout Temps d'attente maximum en secondes.
 */
void window_wait_events(window w, double timeout);

/**
 * \brief Récupère la largeur logique de la fenêtre.
 *
 * \param w La fenêtre concernée.
 * \return La largeur en pixels logiques.
 */
int window_get_width(window w);

/**
 * \brief Récupère la hauteur logique de la fenêtre.
 *
 * \param w La fenêtre concernée.
 * \return La hauteur en pixels logiques.
 */
int window_get_height(window w);

/**
 * \brief Récupère le temps écoulé depuis l'initialisation de la fenêtre.
 *
 * \param w La fenêtre concernée.
 * \return Le temps en secondes (float).
 */
float window_get_time(window w);

/**
 * \brief Récupère le pointeur natif de la fenêtre sous-jacente.
 *
 * \attention Cette fonction casse l'abstraction et ne doit être utilisée 
 * que pour initialiser des bibliothèques externes.
 *
 * \param w La fenêtre concernée.
 * \return Un pointeur `void*` correspondant au handle natif (ex: `GLFWwindow*`).
 */
void* window_get_native_handle(window w);

/**
 * \brief Récupère la taille physique du framebuffer.
 *
 * Sur les écrans haute densité (2K, 4K...), la taille physique en pixels 
 * peut différer de la taille logique de la fenêtre. Cette fonction est requise 
 * pour mettre à jour correctement le glViewport.
 *
 * \param w La fenêtre concernée.
 * \param width Pointeur où stocker la largeur physique en pixels.
 * \param height Pointeur où stocker la hauteur physique en pixels.
 */
void window_get_framebuffer_size(window w, int* width, int* height);


void handle_window_input(window w, camera c);

void handle_window_resize(window w, camera c);

mouse_status window_get_mouse_status(window w);

bool window_get_key_pressed(window w, int key);

#endif // WINDOW_H
