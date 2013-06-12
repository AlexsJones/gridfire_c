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
extern jnx_hashmap *config;
sfRectangleShape *radar_background;


sfVector2f radar_position_translation(game_object *obj)
{
	//translate the object's ingame position to something in the radar
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
}
void radar_update(sfView *view,sfRenderWindow *main_window, jnx_list *list)
{
	sfVector2f view_center = sfView_getCenter(view);
	sfVector2f view_size = sfView_getSize(view);

	sfVector2f radar_background_pos;
	radar_background_pos.x = (view_center.x + (view_size.x /2)) - sfRectangleShape_getSize(radar_background).x;
	radar_background_pos.y = (view_center.y + (view_size.y /2)) - sfRectangleShape_getSize(radar_background).y;

	sfRectangleShape_setPosition(radar_background,radar_background_pos);	
}
void radar_draw(sfRenderWindow *main_window)
{
	sfRenderWindow_drawRectangleShape(main_window,radar_background,NULL);
}
