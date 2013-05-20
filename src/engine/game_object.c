/*
 * =====================================================================================
 *
 *       Filename:  game_object.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  04/27/13 20.73:02
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
#include <assert.h>
void game_object_update(game_object *obj, sfEvent event,sfView *view)
{
	if(strcmp("player",obj->object_type) == 0)
	{
		if(sfKeyboard_isKeyPressed(sfKeyW))
		{
			obj->velocity = obj->velocity + 0.7f;
		}
		if(sfKeyboard_isKeyPressed(sfKeyS))
		{
			obj->velocity = obj->velocity - 0.7f;
		}
		if(sfKeyboard_isKeyPressed(sfKeyA))
		{
			obj->rotation = obj->rotation - 0.4f;
		}
		if(sfKeyboard_isKeyPressed(sfKeyD))
		{
			obj->rotation = obj->rotation + 0.4f;
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
}
square* game_object_get_bounds(game_object *obj)
{
	assert(obj);
	square *box = malloc(sizeof(square));
	sfVector2f position = sfSprite_getPosition(obj->sprite);
	sfVector2u texture_size = sfTexture_getSize(sfSprite_getTexture(obj->sprite));
	
	box->left = position.x - texture_size.x ;
	box->right = position.x + texture_size.x;
	box->top = position.y - texture_size.y ;
	box->bottom = position.y + texture_size.y;
	return box;
}
sfRectangleShape *game_object_get_boundingRect(game_object *obj)
{

			sfVector2u texture_size = sfTexture_getSize(sfSprite_getTexture(obj->sprite));
			sfVector2f bounding_size;
			bounding_size.x = texture_size.x;
			bounding_size.y = texture_size.y;    
			sfRectangleShape *bounding_box = sfRectangleShape_create();
			sfVector2f bounding_position;
			bounding_position.x = sfSprite_getPosition(obj->sprite).x - (texture_size.x /2);
			bounding_position.y = sfSprite_getPosition(obj->sprite).y - (texture_size.y /2);
			sfRectangleShape_setPosition(bounding_box,bounding_position);
			               
			sfRectangleShape_setOutlineColor(bounding_box,sfColor_fromRGB(255,255,0));
			sfRectangleShape_setSize(bounding_box,bounding_size);

	return bounding_box;
}
