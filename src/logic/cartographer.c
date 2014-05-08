/*
 * =====================================================================================
 *
 *       Filename:  cartographer.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  04/28/13 21:10:33
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */
#include <stdlib.h>
#include "cartographer.h"
#include <string.h>
#include <stdio.h>
#include <jnxc_headers/jnxlist.h>
#include <jnxc_headers/jnxlog.h>
#include "audio_control.h"
#include "../game.h"
#include "scoreboard.h"
square *bounds_map = NULL;
jnx_list *object_list;
void cartographer_clear(void)
{
	if(object_list == NULL) return;
	jnx_node *head = object_list->head;
	while(head)
	{
		game_object *currentobj = head->_data;
		free(currentobj->sprite);
		free(currentobj);
		head = head->next_node;
	}
	jnx_list_destroy(&object_list);
	object_list = NULL;
}
void cartographer_add(game_object *obj)
{
	if(object_list == NULL) { object_list = jnx_list_create(); }
	/*-----------------------------------------------------------------------------
	 *  Temporary solution whilst I create an algorithm for search 
	 *-----------------------------------------------------------------------------*/
	jnx_list_add(object_list,obj);
}
jnx_list *cartographer_get_at(sfView *view)
{
	/*-----------------------------------------------------------------------------
	 *  Again a temporary solution to return the entire list
	 *-----------------------------------------------------------------------------*/
	if(object_list == NULL)
	{
		return NULL;
	}
	sfVector2f position = sfView_getCenter(view);
	int view_max_size = sfView_getSize(view).x;
	jnx_node *head = object_list->head;
	jnx_node *head_reset = head;
	jnx_list *temp_list = jnx_list_create();	
	int count = 0;
	while(head)
	{
		game_object *obj = head->_data;
		sfVector2f obj_pos = sfSprite_getPosition(obj->sprite);
		if(obj_pos.x < position.x + view_max_size && obj_pos.x > position.x - view_max_size && obj_pos.y < position.y + view_max_size && obj_pos.y > position.y - view_max_size)
		{
			jnx_list_add(temp_list,obj);
			++count;
		}
		head = head->next_node;
	}
	head = head_reset;
	/*-----------------------------------------------------------------------------
	 *  Note, that you probably don't want to return the original list ever as any manipulation outside of this functionality could cause error
	 *-----------------------------------------------------------------------------*/
	return temp_list;
}
void cartographer_setbounds(int top, int bottom, int left, int right)
{
	bounds_map = malloc(sizeof(square));
	bounds_map->top = top;
	bounds_map->bottom = bottom;
	bounds_map->left = left;
	bounds_map->right = right;
	JNX_LOGC(JLOG_NORMAL,"Set new bounds map\n");
}
square *cartographer_getbounds(void)
{
	if(bounds_map == NULL) { JNX_LOGC(JLOG_NORMAL,"Error getting bounds - no map set\n");return NULL; }
	return bounds_map;
}
void cartographer_update()
{

	/*-----------------------------------------------------------------------------
	 *  Warning, may slow down game loop if there are alot of objects here
	 *-----------------------------------------------------------------------------*/
	jnx_node *head = object_list->head;
	jnx_list *new_draw = jnx_list_create();
	while(head)
	{
		game_object *current = head->_data;
		if(current->health > 0)
		{
			//still an active object
			jnx_list_add(new_draw,current);
		}
		else
		{
			if(strcmp(current->object_type,"player")  == 0)
			{
				/*-----------------------------------------------------------------------------
				 *  If the player has been killed we'll call a clean up function to end the game
				 *-----------------------------------------------------------------------------*/
				game_end();	
			}
			JNX_LOGC(JLOG_NORMAL,"Object %s at %g %g has been removed as health was %d\n", current->object_type,current->position.x, current->position.y, current->health);
			//remove the object
			play_sound(sound_lexplosion);

			/*-----------------------------------------------------------------------------
			 *  Add our soon to be lost object to the score board
			 *-----------------------------------------------------------------------------*/
			printf("adding object for destruction %s with health %d\n",current->object_type,current->health);
			//Possible bug here if the player starts in reach of enemy ships and they start blowing up before game time	
			score_add_destroyed_obj(current);
			sfSprite_destroy(current->sprite);
			free(current);
		}
		head = head->next_node;
	}
	object_list = new_draw;
}
