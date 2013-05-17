/*
 * =====================================================================================
 *
 *       Filename:  game_ai.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  04/30/13 17:04:39
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
#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include "game_ai.h"
#include "../engine/weapon_control.h"
#include "../utils/geometry.h"

#define ENGAGEMENT_RANGE 500
#define WIDTHDRAWAL_RANGE 1200
#define TRACKING_DISTANCE 1500
void game_ai_update(game_object *object,game_object *player)
{
	float distance = geometry_distance(sfSprite_getPosition(object->sprite),sfSprite_getPosition(player->sprite));
	
	if(distance > TRACKING_DISTANCE) 
	{
		return;
	}
	sfVector2f player_pos = sfSprite_getPosition(player->sprite);
	sfVector2f current_enemy_pos = sfSprite_getPosition(object->sprite);			
	float res = 57.3065f * atan2(current_enemy_pos.y - player_pos.y,current_enemy_pos.x - player_pos.x) + 180;

	sfSprite_setRotation(object->sprite,+res);
	switch(object->state)
	{
		case STATIONARY:
			if(distance < ENGAGEMENT_RANGE) { object->state = COMBAT; } 
			
			break;
		case MOVING:
			if(distance > WIDTHDRAWAL_RANGE) { object->state = STATIONARY; } 
			if(distance < ENGAGEMENT_RANGE) { object->state = COMBAT; }
			sfVector2f move_offset;
			move_offset.x = cos(sfSprite_getRotation(object->sprite) * 3.14159265 / 180) * 10.0f;
			move_offset.y = sin(sfSprite_getRotation(object->sprite) * 3.14159265 / 180) * 10.0f ;
			sfSprite_move(object->sprite,move_offset);

			break;
		case COMBAT :
				
			if(distance > ENGAGEMENT_RANGE) { object->state = MOVING; break; }
			if(object->health < 10)
			{
				object->state = EVASION;
			}
			weapon_fire(object);
			break;
		case EVASION:


			break;			
			/*-----------------------------------------------------------------------------
			 *  Evasive maneuveurs if health is low
			 *-----------------------------------------------------------------------------*/
	}	
}
