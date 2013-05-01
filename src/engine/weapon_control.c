/*
 * =====================================================================================
 *
 *       Filename:  weapon_control.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  05/01/13 17:14:17
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  AlexsJones (), alexsimonjones@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */
#include <stdlib.h>
#include <math.h>
#include "weapon_control.h"
#include <jnxc_headers/jnxlist.h>
jnx_list *weapon_shot_list = NULL;


sfSprite *weapon_create_sprite(game_object *parent)
{
	sfTexture *texture = sfTexture_createFromFile("res/plasma.png",NULL);

	sfSprite *weapon = sfSprite_create();
	sfSprite_setTexture(weapon,texture,1);
	sfSprite_setPosition(weapon,sfSprite_getPosition(parent->sprite));
	sfSprite_setRotation(weapon,sfSprite_getRotation(parent->sprite));

	return weapon;
}
void weapon_fire(game_object *parent/*  more to come i.e weapon type, speed etc... */)
{
	if(weapon_shot_list == NULL)
	{
		weapon_shot_list = jnx_list_init();
	}
	sfSprite *weapon_shot = weapon_create_sprite(parent);
	jnx_list_add(weapon_shot_list,weapon_shot);	
}
void weapon_draw(sfRenderWindow *window)
{
	if(weapon_shot_list == NULL)
	{
		weapon_shot_list = jnx_list_init();
	}
	jnx_node *head = weapon_shot_list->head;

	while(head)
	{	
		sfSprite *current = (sfSprite*)head->_data;

		sfVector2f move_offset;
		move_offset.x = cos(sfSprite_getRotation(current) * 3.14159265 / 180) * 10.0f;
		move_offset.y = sin(sfSprite_getRotation(current) * 3.14159265 / 180) * 10.0f ;
		sfSprite_move(current,move_offset);
		sfRenderWindow_drawSprite(window,current,NULL);
		head = head->next_node;
	}

	/*-----------------------------------------------------------------------------
	 *  Create second list based on objects outside of the cartographer bounds and delete
	 *-----------------------------------------------------------------------------*/
}
