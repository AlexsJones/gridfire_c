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
#include "../utils/geometry.h"
#include "../logic/cartographer.h"
#include "game_object.h"
#include <string.h>
void game_object_update_position(game_object *obj)
{

}
void game_object_update(game_object *obj, sfEvent event,float elapsed_time)
{

	if(strcmp("player",obj->object_type) == 0)
	{
	
		if(sfKeyboard_isKeyPressed(sfKeyW))
		{
			obj->velocity = obj->velocity + 0.6f * elapsed_time;
		}
		if(sfKeyboard_isKeyPressed(sfKeyA))
		{
			obj->rotation = obj->rotation - 1.0f * elapsed_time;
		}
		if(sfKeyboard_isKeyPressed(sfKeyD))
		{
			obj->rotation = obj->rotation + 1.0f * elapsed_time;
		}

			

			sfSprite_rotate(obj->sprite,obj->rotation);

			sfVector2f move_offset;
			move_offset.x = cos(sfSprite_getRotation(obj->sprite) * 3.14159265 / 180) * obj->velocity;
			move_offset.y = sin(sfSprite_getRotation(obj->sprite) * 3.14159265 / 180) * obj->velocity ;
			sfSprite_move(obj->sprite,move_offset);

		sfVector2f pos = sfSprite_getPosition(obj->sprite);
		square *bounds = cartographer_getbounds();

		if(geometry_contains(bounds,pos))
		{

		}else
		{

		}

		if(obj->velocity > 0.0f)
		{
			obj->velocity = obj->velocity - 0.1f * elapsed_time;
		}
		if(obj->velocity < 0.0f)
		{
			obj->velocity = obj->velocity + 0.1f * elapsed_time;
		}
		if(obj->rotation > 0.0f)
		{
			obj->rotation = obj->rotation - 0.1 * elapsed_time;
		}
		if(obj->rotation <  0.0f)
		{
			obj->rotation = obj->rotation + 0.1 * elapsed_time;
		}

		}

	else
	{
						/*-----------------------------------------------------------------------------
						 *  AI movement
						 *-----------------------------------------------------------------------------*/
	}
}
