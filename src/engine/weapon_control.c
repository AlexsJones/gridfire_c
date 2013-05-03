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
#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <math.h>
#include "weapon_control.h"
#include <jnxc_headers/jnxlist.h>
#include "../utils/geometry.h"
#include "../logic/cartographer.h"
jnx_list *weapon_shot_list = NULL;


typedef struct weapon_shot
{
	sfSprite *sprite;
	int damage;
}weapon_shot;


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
	
	weapon_shot *weapon_shot = malloc(sizeof(weapon_shot));
	sfSprite *sprite = weapon_create_sprite(parent);
	weapon_shot->damage = 10; // hardcoded for now
	weapon_shot->sprite = sprite;	
	jnx_list_add(weapon_shot_list,weapon_shot);	
}
void weapon_draw(sfRenderWindow *window)
{
	if(weapon_shot_list == NULL)
	{
		weapon_shot_list = jnx_list_init();
	}
	jnx_node *head = weapon_shot_list->head;
	jnx_list *temp = jnx_list_init();
	
	while(head)
	{	
		weapon_shot *current = (weapon_shot*)head->_data;

		sfVector2f move_offset;
		move_offset.x = cos(sfSprite_getRotation(current->sprite) * 3.14159265 / 180) * 100.0f;
		move_offset.y = sin(sfSprite_getRotation(current->sprite) * 3.14159265 / 180) * 100.0f ;
		sfSprite_move(current->sprite,move_offset);
		sfRenderWindow_drawSprite(window,current->sprite,NULL);
		

		if(geometry_contains(cartographer_getbounds(),sfSprite_getPosition(current->sprite)))
		{
			jnx_list_add(temp,current);
		}		
		else
		{
			sfSprite_destroy(current->sprite);
			free(current);
		}	
		head = head->next_node;
	}

	weapon_shot_list = temp;	
}
