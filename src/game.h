/*
 * =====================================================================================
 *
 *       Filename:  game.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  04/25/13 17:21:11
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */
#ifndef __GAME_H__
#define __GAME_H__
#include <SFML/Graphics.h>
#include <SFML/Window.h>
#include <jnxc_headers/jnxhash.h>
int game_setup(jnx_hashmap *configptr);
void *game_load(void *args);
void game_run(void);
void game_end(void);


/*-----------------------------------------------------------------------------
 *  Globally accessible
 *-----------------------------------------------------------------------------*/
jnx_hashmap *config;
#endif
