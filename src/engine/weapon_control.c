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
#include <jnxc_headers/jnxlog.h>
#include <SFML/Audio.h>
#include "../logic/audio_control.h"
#include <string.h>
#include <assert.h>
#include <jnxc_headers/jnxhash.h>
jnx_list *weapon_shot_list = NULL;
jnx_list *temp_draw = NULL;
#ifndef ALLOWINVUL
#define ALLOWINVUL
#endif
typedef struct weapon_shot
{
	sfSprite *sprite;
	int damage;
}weapon_shot;

extern jnx_hashmap *config;
/*-----------------------------------------------------------------------------
 *  Preloaded weapon sprites
 *-----------------------------------------------------------------------------*/
sfTexture *plasma_texture;
sfTexture *laser_texture;
sfSprite *weapon_create_sprite(game_object *parent)
{
	sfTexture *texture;
	switch(parent->weapon)
	{
		case PLASMA:
			texture = plasma_texture;
			break;
		case LASER:
			texture = laser_texture;
			break;
		default:
			texture = plasma_texture;
			break;

	}
	sfSprite *weapon = sfSprite_create();
	sfSprite_setTexture(weapon,texture,1);
	sfSprite_setPosition(weapon,sfSprite_getPosition(parent->sprite));
	sfSprite_setRotation(weapon,sfSprite_getRotation(parent->sprite));
	return weapon;
}
void weapon_setup()
{
	plasma_texture = sfTexture_createFromFile("res/plasma.png",NULL);
	laser_texture = sfTexture_createFromFile("res/laser.png",NULL);
}
void weapon_fire(game_object *parent/*  more to come i.e weapon type, speed etc... */)
{
	if(weapon_shot_list == NULL)
	{
		weapon_shot_list = jnx_list_init();
	}
	weapon_shot *weapon_shot = malloc(sizeof(weapon_shot));
	sfSprite *sprite = weapon_create_sprite(parent);
	assert(sprite);
	weapon_shot->damage = parent->weapon_damage;
	weapon_shot->sprite = sprite;	
	/*-----------------------------------------------------------------------------
	 *  Setting the initial start position infront of the parent sprite so it doesnt confuse later
	 *-----------------------------------------------------------------------------*/
	sfVector2f move_offset;
	move_offset.x = cos(sfSprite_getRotation(weapon_shot->sprite) * 3.14159265 / 180) * (45.0f + parent->velocity);
	move_offset.y = sin(sfSprite_getRotation(weapon_shot->sprite) * 3.14159265 / 180) * (45.0f  + parent->velocity);
	sfSprite_move(weapon_shot->sprite,move_offset);
	jnx_list_add(weapon_shot_list,weapon_shot);	

	if(strcmp(parent->object_type,"player") == 0)
	{
		play_sound(sound_laser2);
	}else
	{
		play_sound(sound_laser);
	}
}
void weapon_check_collision(weapon_shot *current, jnx_list **draw_queue)
{
	jnx_node *dqueue_head = (*draw_queue)->head;
	sfVector2f current_weapon_pos = sfSprite_getPosition(current->sprite);
	while(dqueue_head)
	{
		game_object *obj = dqueue_head->_data;	
		square *game_object_size = game_object_get_bounds(obj);		
		if(geometry_contains(game_object_size,sfSprite_getPosition(current->sprite)))
		{
#ifdef ALLOWINVUL
			if(strcmp(obj->object_type,"player") == 0 && strcmp(jnx_hash_get(config,"PLAYERINVUL"),"ON") == 0)
			{

			}else{
#endif
				obj->health = obj->health - current->damage;
#ifdef ALLOWINVUL
			}
#endif
			//destroy the ship if health is 0
		}	
		free(game_object_size);
		dqueue_head = dqueue_head->next_node;
	}
}
int weapon_check_bounds(weapon_shot *current, jnx_list **temp_list,square *view_bounds)
{
	if(geometry_contains(view_bounds, sfSprite_getPosition(current->sprite)))
	{
		jnx_list_add((*temp_list),current);
		return 0;
	}
	else
	{
		sfSprite_destroy(current->sprite);
		free(current);
		return 1;
	}
}
void weapon_draw(sfRenderWindow *window,sfView *view, jnx_list **draw_queue)
{
	if(weapon_shot_list == NULL)
	{
		weapon_shot_list = jnx_list_init();
	}
	jnx_node *head = weapon_shot_list->head;
	jnx_list *temp = jnx_list_init();
	sfVector2f view_pos = sfView_getCenter(view);
	sfVector2f view_size = sfView_getSize(view);
	square *view_bounds = malloc(sizeof(square));
	view_bounds->top = view_pos.y - (view_size.y /2);
	view_bounds->bottom = view_pos.y + (view_size.y /2);
	view_bounds->left = view_pos.x - (view_size.x /2);
	view_bounds->right = view_pos.x + (view_size.x /2);	
	while(head)
	{	
		weapon_shot *current = (weapon_shot*)head->_data;
		sfVector2f move_offset;
		move_offset.x = cos(sfSprite_getRotation(current->sprite) * 3.14159265 / 180) * 40.0f;
		move_offset.y = sin(sfSprite_getRotation(current->sprite) * 3.14159265 / 180) * 40.0f ;
		sfSprite_move(current->sprite,move_offset);
		/*-----------------------------------------------------------------------------
		 *  Check to see whether the current shot collides with anything drawn
		 *-----------------------------------------------------------------------------*/
		weapon_check_collision(current,draw_queue);
		/*-----------------------------------------------------------------------------
		 *  Check to see whether the current shot goes out of map bounds
		 *-----------------------------------------------------------------------------*/
		if(weapon_check_bounds(current,&temp,view_bounds) == 0)
		{
			sfRenderWindow_drawSprite(window,current->sprite,NULL);
		}	
		head = head->next_node;
	}
	free(view_bounds);
	weapon_shot_list = temp;	
}
