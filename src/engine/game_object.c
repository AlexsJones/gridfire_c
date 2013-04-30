/*
 * =====================================================================================
 *
 *       Filename:  game_object.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  04/27/13 20:33:02
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */
#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include "game_object.h"
void game_object_update(game_object *obj, sfEvent event)
{
	switch(event.key.code)
	{
		case sfKeyW:
			obj->velocity = obj->velocity + 0.1f;			
			break;
		case sfKeyS:
			obj->velocity = obj->velocity - 0.1f;			
			break;
		case sfKeyA:
			
			obj->rotation = obj->rotation - 0.1f;
			break;
		case sfKeyD:

			obj->rotation = obj->rotation + 0.1f;
			break;
	}
		sfSprite_rotate(obj->sprite,obj->rotation);
		sfVector2f move_offset;
		move_offset.x = cos(sfSprite_getRotation(obj->sprite) * 3.14159265 / 180) * obj->velocity;
		move_offset.y = sin(sfSprite_getRotation(obj->sprite) * 3.14159265 / 180) * obj->velocity;
	sfSprite_move(obj->sprite,move_offset);

}
