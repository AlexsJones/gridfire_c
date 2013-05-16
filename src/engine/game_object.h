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
#include "../utils/geometry.h"
typedef enum { PLAYER,STATIONARY, MOVING, COMBAT } object_state;
typedef struct game_object{
	sfSprite *sprite;
	sfVector2f position;
	int health;
	float rotation;
	char *object_type;
	float velocity;
	int weapon_damage;
	object_state state;
}game_object;
void game_object_update(game_object *obj, sfEvent event,sfView *view);
square* game_object_get_bounds(game_object *obj);
sfRectangleShape *game_object_get_boundingRect(game_object *obj);
#endif
