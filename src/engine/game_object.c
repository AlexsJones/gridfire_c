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
#include "weapon_control.h"
#include "game_object.h"
#include <string.h>
void game_object_update(game_object *obj, sfEvent event,sfView *view)
{
	if(strcmp("player",obj->object_type) == 0)
	{
		if(sfKeyboard_isKeyPressed(sfKeyW))
		{
			obj->velocity = obj->velocity + 0.3f;
		}
		if(sfKeyboard_isKeyPressed(sfKeyS))
		{
			obj->velocity = obj->velocity - 0.3f;
		}
		if(sfKeyboard_isKeyPressed(sfKeyA))
		{
			obj->rotation = obj->rotation - 0.2f;
		}
		if(sfKeyboard_isKeyPressed(sfKeyD))
		{
			obj->rotation = obj->rotation + 0.2f;
		}
		if(sfKeyboard_isKeyPressed(sfKeyZ))
		{
			sfView_zoom(view,.9f);
		}
		if(sfKeyboard_isKeyPressed(sfKeyX))
		{
			sfView_zoom(view,1.1f);
		}
		if(sfKeyboard_isKeyPressed(sfKeyTab))
		{
			weapon_fire(obj);
		}
		sfSprite_rotate(obj->sprite,obj->rotation);
		sfVector2f move_offset;
		move_offset.x = cos(sfSprite_getRotation(obj->sprite) * 3.14159265 / 180) * obj->velocity;
		move_offset.y = sin(sfSprite_getRotation(obj->sprite) * 3.14159265 / 180) * obj->velocity ;
		sfSprite_move(obj->sprite,move_offset);

		sfVector2f pos = sfSprite_getPosition(obj->sprite);
		square *bounds = cartographer_getbounds();

		if(!geometry_contains(bounds,pos))
		{
			/*-----------------------------------------------------------------------------
			 *  Off the map!
			 *-----------------------------------------------------------------------------*/
		}
		if(obj->velocity > 0.0f)
		{
			obj->velocity = obj->velocity - 0.1f;
		}
		if(obj->velocity < 0.0f)
		{
			obj->velocity = obj->velocity + 0.1f;
		}
		if(obj->rotation > 0.0f)
		{
			obj->rotation = obj->rotation - 0.1;
		}
		if(obj->rotation < 0.0f)
		{
			obj->rotation = obj->rotation + 0.1;
		}


}
else
{
	/*-----------------------------------------------------------------------------
	 *  AI movement
	 *-----------------------------------------------------------------------------*/
}
}
