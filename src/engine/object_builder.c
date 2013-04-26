/*
 * =====================================================================================
 *
 *       Filename:  object_builder.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  04/26/13 16:05:32
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */
#include <stdlib.h>
#include "object_builder.h"

game_object *object_builder_create(char *texture_data,int x, int y, int health, float rotation)
{
	game_object *obj = malloc(sizeof(game_object));
	obj->sprite = sfSprite_create();
	sfVector2f _position;
	_position.x = x;
	_position.y = y;
	obj->position = _position;
	obj->rotation = rotation;
	obj->health = health;
	sfTexture *_texture = sfTexture_createFromFile(texture_data,NULL);
	sfSprite_setTexture(obj->sprite,_texture,1);
	sfSprite_setPosition(obj->sprite,obj->position);
	sfSprite_setRotation(obj->sprite,obj->rotation);

	sfVector2u texture_origin = sfTexture_getSize(_texture);
	float _x = (float)texture_origin.x;
	float _y = (float)texture_origin.y;
	sfVector2f new_org;
	new_org.x = _x /2 ;
	new_org.y = _y /2 ;
	sfSprite_setOrigin(obj->sprite,new_org);

	return obj;
}
