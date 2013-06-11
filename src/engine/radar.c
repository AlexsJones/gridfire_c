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

sfRectangleShape *radar_background;

void radar_setup(void)
{
	radar_background = sfRectangleShape_create();
	sfVector2f radar_size;
	radar_size.x = 250;
	radar_size.y = 250;
	sfRectangleShape_setOutlineColor(radar_background,sfColor_fromRGB(255,245,235));
	sfRectangleShape_setFillColor(radar_background,sfColor_fromRGB(255,235,235));
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
