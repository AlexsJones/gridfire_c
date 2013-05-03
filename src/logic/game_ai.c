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
#include <stdio.h>
#include "game_ai.h"
#include "../utils/geometry.h"
void game_ai_update(game_object *object,game_object *player)
{
	float distance = geometry_distance(sfSprite_getPosition(object->sprite),sfSprite_getPosition(player->sprite));
	sfVector2f player_pos = sfSprite_getPosition(player->sprite);
	sfVector2f current_enemy_pos = sfSprite_getPosition(object->sprite);			
	float res = 57.3065f * atan2(current_enemy_pos.y - player_pos.y,current_enemy_pos.x - player_pos.x) + 180;

	switch(object->state)
	{
		case STATIONARY:
			if(distance < 1000) { object->state = COMBAT; } 

			break;
		case MOVING:
			if(distance < 1000) { object->state = COMBAT; } 


			break;
		case COMBAT :
				sfSprite_setRotation(object->sprite,+res);


			break;
	}	
}
