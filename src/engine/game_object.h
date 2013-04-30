/*
 * =====================================================================================
 *
 *       Filename:  game_object.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  04/27/13 19:57:32
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */
#ifndef __GAME_OBJECT_H__
#define __GAME_OBJECT_H__
#include <SFML/Graphics.h>
#include <SFML/Window.h>
typedef struct game_object{
	sfSprite *sprite;
	sfVector2f position;
	int health;
	float rotation;
	char *object_type;
	float velocity;
}game_object;
void game_object_update(game_object *obj, sfEvent event);
#endif
