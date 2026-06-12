#ifndef LOG_H
#define LOG_H

/**
 * \file logger.h
 * \brief Ficher fournissant des macro de \a log afin d'afficher des messages de déboggage dans la console.
 *
 * Ce fichier des macros de \a log afin de faciliter l'affichage de message de déboggage dans la console.
 *
 * Il ya plusiurs niveau de message :
 *  - \b INFO message à titre informatif
 *  - \b WARNING message signifant quelque chose d'anormal ou suspect
 *  - \b ERROR message indicant une érreur du programme, si `EXIT_ON_ERROR` est acitivé, alors le programme s'arrêtera.
 *
 * Cette outils est très utile notamment en programmation C afin de comprendre les érreurs plus facilement
 * en ayant des message d'érreur explicite plutot qu'un \a seg_fault ou \a core_dump.
 *
 * Si le define `LOG_ENABLED` est à 0 alors aucun message ne sera afficher.
 *
 * Si le define `EXIT_ON_ERROR` alors le programme ne se fermera pas automatiquement
 * après l'affichage d'un message d'érreur
 */

#ifndef LOG_ENABLED

	/**
	 * \brief Permet d'activer (`0`) ou désactiver (`1`)
	 * l'affichage des messages de déboggages.
	 */
	#define LOG_ENABLED 1
#endif

#ifndef EXIT_ON_ERROR
	/**
	 * \brief Permet d'activer (`0`) ou désactiver (`1`)
	 * la terminaison du programme après la détection d'une erreur.
	 */
	#define EXIT_ON_ERROR 1
#endif

#if LOG_ENABLED

	#include <stdio.h>

	#define LOG_HEADER(fd, header, fmt, ...) fprintf(fd, "[%s]: " fmt "\n", header, ##__VA_ARGS__)
	#define LOG_HEADER_FILE(fd, header, fmt, ...) fprintf(fd, "[%s] %s:%d: " fmt "\n", header, __FILE__, __LINE__, ##__VA_ARGS__)

	#define LOG(fmt, ...) printf(fmt "\n", ##__VA_ARGS__)
	#define LOG_WARNING(fmt, ...) LOG_HEADER(stdout, "WARNING", fmt, ##__VA_ARGS__)
	#define LOG_INFO(fmt, ...) LOG_HEADER(stdout, "INFO", fmt, ##__VA_ARGS__)

	#if !EXIT_ON_ERROR
		#define LOG_ERROR(fmt, ...) LOG_HEADER_FILE(stderr, "ERROR", fmt, ##__VA_ARGS__)
	#endif

#else

	#define LOG(fmt, ...)
	#define LOG_ERROR(fmt, ...)
	#define LOG_INFO(fmt, ...)

#endif

#define EXIT_PROGRAM(code) do { LOG("Program exited with code %d", code); exit(code); } while(0)
#define EXIT_ERROR(code, fmt, ...) do { LOG_ERROR(fmt, ##__VA_ARGS__); EXIT_PROGRAM(code); } while(0)

#if LOG_ENABLED && EXIT_ON_ERROR

	#include <stdlib.h>

	#define LOG_ERROR(fmt, ...)                                    \
		do { LOG_HEADER_FILE(stderr, "ERROR", fmt, ##__VA_ARGS__); \
			 LOG_INFO("Exit on error is active exiting ...");      \
			 EXIT_PROGRAM(EXIT_FAILURE);                           \
		} while(0)
#endif

#endif // LOG_H
