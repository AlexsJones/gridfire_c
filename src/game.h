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
int game_setup(void);
int game_load(char *configuration_path);
void game_run(void);
#endif
