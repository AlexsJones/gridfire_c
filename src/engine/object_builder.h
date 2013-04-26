/*
 * =====================================================================================
 *
 *       Filename:  object_builder.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  04/26/13 16:00:56
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */
#ifndef __OBJECT_BUILDER_H__
#define __OBJECT_BUILDER_H__
#include <SFML/Graphics.h>
#include <SFML/Window.h>
typedef struct game_object{
	sfSprite *sprite;
	sfVector2f position;
	int health;
	float rotation;
}game_object;

game_object *object_builder_create(char *texture_data,int x, int y, int health, float rotation);
#endif
