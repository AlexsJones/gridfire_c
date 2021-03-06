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

#define ENGAGEMENT_RANGE 700
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

  switch(object->state)
  {
    case STATIONARY:
      if(distance < ENGAGEMENT_RANGE) { object->state = COMBAT; } 

      break;
    case MOVING:
      if(distance > WIDTHDRAWAL_RANGE) { object->state = STATIONARY; } 
      if(distance < ENGAGEMENT_RANGE) { object->state = COMBAT; }
      sfVector2f move_offset;
      sfSprite_setRotation(object->sprite,+res);
      move_offset.x = cos(sfSprite_getRotation(object->sprite) * 3.14159265 / 180) * object->maxspeed;
      move_offset.y = sin(sfSprite_getRotation(object->sprite) * 3.14159265 / 180) * object->maxspeed;
      sfSprite_move(object->sprite,move_offset);

      break;
    case COMBAT :
      if(distance > ENGAGEMENT_RANGE) { object->state = MOVING; break; }
      if(object->health < 50)
      {
        printf("Triggered evasion, health is %d\n",object->health);
        object->state = EVASION;
      }
      sfSprite_setRotation(object->sprite,+res);
      weapon_fire(object);
      break;
    case EVASION:
      /*-----------------------------------------------------------------------------
       *  Very basic implementation puts the ships into reverse
       *-----------------------------------------------------------------------------*/
      move_offset.x = cos(sfSprite_getRotation(object->sprite) * 3.14159265 / 180) * -5.0f;
      move_offset.y = sin(sfSprite_getRotation(object->sprite) * 3.14159265 / 180) * -5.0f ;
      sfSprite_move(object->sprite,move_offset);
      break;	

    case HEALTH_CONTAINER:

      if(distance < 150)
      {
        player->health += object->health;
        /*-----------------------------------------------------------------------------
         *  Destroy the health container and transfer health to the player
         *-----------------------------------------------------------------------------*/
        object->health = 0;
      }
      break;

  }	
}
