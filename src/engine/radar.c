/*
 * =====================================================================================
 *
 *       Filename:  radar.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  06/10/13 08:16:59
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  AlexsJones (), alexsimonjones@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */
#include <stdlib.h>
#include "radar.h"
#include <jnxc_headers/jnxhash.h>
#include "game_object.h"
#include "../utils/geometry.h"
#include <stdio.h>
extern jnx_hashmap *config;
sfRectangleShape *radar_background;
sfTexture *radar_blip_texture;
sfTexture *radar_blip_texture_player;
sfSprite *radar_blip;

jnx_list *blip_list;

sfVector2f radar_position_translation(sfVector2f realworld_position)
{
	//translate the object's ingame position to something in the radar
	//radar bounds
	sfVector2f radar_size = sfRectangleShape_getSize(radar_background);
	sfVector2f radar_position = sfRectangleShape_getPosition(radar_background);
	square radar_bounds;
	radar_bounds.left = radar_position.x;
	radar_bounds.right = radar_position.x  + radar_size.x;
	radar_bounds.top = radar_position.y;
	radar_bounds.bottom = radar_position.y + radar_size.y;

	sfVector2f newposition;

	newposition.x = realworld_position.x / radar_size.x + radar_position.x;
	newposition.y = realworld_position.y / radar_size.y + radar_position.y;

	realworld_position = newposition;

	return realworld_position;
}
sfSprite *radar_blip_from_object(game_object *obj)
{
	sfSprite *objsprite = sfSprite_create();
	sfVector2u texture_origin;

	if(strcmp(obj->object_type,"player") == 0)
	{
		sfSprite_setTexture(objsprite,radar_blip_texture_player,1);
		texture_origin = sfTexture_getSize(radar_blip_texture_player);
	}else if(strcmp(obj->object_type,"enemy") == 0)
	{
		sfSprite_setTexture(objsprite,radar_blip_texture,1);
		texture_origin = sfTexture_getSize(radar_blip_texture);
	}
	float _x = (float)texture_origin.x;
	float _y = (float)texture_origin.y;
	sfVector2f new_org;
	new_org.x = _x /2 ;
	new_org.y = _y /2 ;
	sfSprite_setOrigin(objsprite,new_org);
	sfSprite_setPosition(objsprite,radar_position_translation(sfSprite_getPosition(obj->sprite)));
	return objsprite;
}
void radar_setup(void)
{
	/*-----------------------------------------------------------------------------
	 *  The radar will translate based on mapsize
	 *-----------------------------------------------------------------------------*/
	radar_background = sfRectangleShape_create();
	sfVector2f radar_size;
	radar_size.x = 250;
	radar_size.y = 250;
	sfRectangleShape_setOutlineThickness(radar_background,2);
	sfRectangleShape_setOutlineColor(radar_background,sfColor_fromRGB(50,50,50));
	sfRectangleShape_setFillColor(radar_background,sfColor_fromRGB(1,1,1));
	sfRectangleShape_setSize(radar_background,radar_size);
	radar_blip_texture= sfTexture_createFromFile("res/radar_blip.png",NULL);
	radar_blip_texture_player= sfTexture_createFromFile("res/radar_blip_player.png",NULL);
}
void radar_update(sfView *view,sfRenderWindow *main_window)
{
	sfVector2f view_center = sfView_getCenter(view);
	sfVector2f view_size = sfView_getSize(view);
	sfVector2f radar_background_pos;
	radar_background_pos.x = (view_center.x + (view_size.x /2)) - sfRectangleShape_getSize(radar_background).x;
	radar_background_pos.y = (view_center.y + (view_size.y /2)) - sfRectangleShape_getSize(radar_background).y;

	sfRectangleShape_setPosition(radar_background,radar_background_pos);	
}
void radar_draw(sfRenderWindow *main_window,jnx_list *draw_queue)
{
	sfRenderWindow_drawRectangleShape(main_window,radar_background,NULL);

	jnx_node *draw_queue_head = draw_queue->head;
	while(draw_queue_head)
	{
		game_object *current_obj = draw_queue_head->_data;
		sfSprite *obj_blip = radar_blip_from_object(current_obj);

		sfRenderWindow_drawSprite(main_window,obj_blip,NULL);
		sfSprite_destroy(obj_blip);
		draw_queue_head = draw_queue_head->next_node;
	}
}
