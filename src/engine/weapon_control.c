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
	char *parent_type;
	sfSprite *sprite;
	int damage;
	int max_velocity;
}weapon_shot;

extern jnx_hashmap *config;
/*-----------------------------------------------------------------------------
 *  Preloaded weapon sprites
 *-----------------------------------------------------------------------------*/
sfTexture *plasma_texture;
sfTexture *laser_texture;
sfTexture *laser2_texture;
sfTexture *dual_laser_texture;
sfTexture *turbolaser_texture;
void weapon_setup()
{
	plasma_texture = sfTexture_createFromFile("res/plasma.png",NULL);
	laser_texture = sfTexture_createFromFile("res/laser.png",NULL);
	laser2_texture = sfTexture_createFromFile("res/laser2.png",NULL);
	dual_laser_texture = sfTexture_createFromFile("res/dual_laser.png",NULL);
	turbolaser_texture = sfTexture_createFromFile("res/laser_turbo.png",NULL);
}
void weapon_fire(game_object *parent/*  more to come i.e weapon type, speed etc... */)
{
	if(weapon_shot_list == NULL)
	{
		weapon_shot_list = jnx_list_init();
	}
	weapon_shot *weapon_shot = malloc(sizeof(weapon_shot));
	sfTexture *texture;
	switch(parent->weapon)
	{
		case PLASMA:
			texture = plasma_texture;
			break;
		case LASER:
			texture = laser_texture;
			break;
		case DUALLASER:
			texture = dual_laser_texture;
			break;
		case LASER2:
			texture = laser2_texture;
			break;
		case TURBO_LASER:
			texture = turbolaser_texture;
			break;
		default:
			texture = plasma_texture;
			break;

	}
	sfSprite *weapon = sfSprite_create();
	sfSprite_setTexture(weapon,texture,1);
	sfSprite_setPosition(weapon,sfSprite_getPosition(parent->sprite));
	sfSprite_setRotation(weapon,sfSprite_getRotation(parent->sprite));
	sfVector2u texture_origin = sfTexture_getSize(texture);
	float _x = (float)texture_origin.x;
	float _y = (float)texture_origin.y;
	sfVector2f new_org;
	new_org.x = _x /2 ;
	new_org.y = _y /2 ;
	sfSprite_setOrigin(weapon,new_org);
	weapon_shot->damage = parent->weapon_damage;
	weapon_shot->sprite = weapon;	
	weapon_shot->max_velocity = parent->maxspeed;
	sfVector2f move_offset;
	sfVector2u size = sfTexture_getSize(sfSprite_getTexture(parent->sprite));
	move_offset.x = cos(sfSprite_getRotation(weapon_shot->sprite) * 3.14159265 / 180) * size.x;
	move_offset.y = sin(sfSprite_getRotation(weapon_shot->sprite) * 3.14159265 / 180) * size.x;	
	sfSprite_move(weapon_shot->sprite,move_offset);
	jnx_list_add(weapon_shot_list,weapon_shot);	

	/*-----------------------------------------------------------------------------
	 *  Set the parent type to help us work out if enemies will blow each other up!
	 *-----------------------------------------------------------------------------*/
	weapon_shot->parent_type = parent->object_type;
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
			if(strcmp(obj->object_type,"player") == 0 && strcmp(jnx_hash_get(config,"PLAYERINVUL"),"ON") == 0)
			{
			}else
			{
				if(strcmp(obj->object_type,current->parent_type) == 0)
				{
					// Objects of the same type don't want to be blowing each other up!
				}else{
				obj->health -=current->damage;	
			}	}
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
		move_offset.x = cos(sfSprite_getRotation(current->sprite) * 3.14159265 / 180) * current->max_velocity;
		move_offset.y = sin(sfSprite_getRotation(current->sprite) * 3.14159265 / 180) * current->max_velocity;
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
	jnx_list_delete(weapon_shot_list);
	weapon_shot_list = temp;
}
