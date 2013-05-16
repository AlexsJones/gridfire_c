/*
 * =====================================================================================
 *
 *       Filename:  starfield.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  05/01/13 11:42:19
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
#include "starfield.h"
#include "../utils/geometry.h"
#include <jnxc_headers/jnxlist.h>


jnx_list *star_field_list = NULL;
jnx_list *menu_starfield = NULL;
jnx_list *starfield_menu_create(sfView *view)
{
	
	if(menu_starfield != NULL) { return menu_starfield; };
	menu_starfield = jnx_list_init();
	int density = 1000;
	sfVector2f vsize = sfView_getSize(view);
	srand(time(NULL));
	int count;
	sfTexture *texture = sfTexture_createFromFile("res/star.png",NULL);

	for(count = 0; count < density; ++count)
	{
		int x = rand() % (int)vsize.x;
		int y = rand() % (int)vsize.y;

		sfSprite *star = sfSprite_create();
		sfSprite_setTexture(star,texture,1);

		sfVector2f pos;
		pos.x = x;
		pos.y = y;

		sfVector2f scale;
		float current = 1;
		scale.x = current;
		scale.y = current;
		sfSprite_setScale(star,scale);
		sfSprite_setPosition(star,pos);
		jnx_list_add(menu_starfield,star);
	}
	return menu_starfield;
}
void starfield_create(square *bounds,int density)
{
	srand(time(NULL));
	if(star_field_list == NULL)
	{
		star_field_list = jnx_list_init();
	}
	int count;
	sfTexture *texture = sfTexture_createFromFile("res/star.png",NULL);

	for(count = 0; count < density; ++count)
	{
		int x = rand() % (bounds->left + bounds->right);
		int y = rand() % (bounds->top + bounds->bottom);

		sfSprite *star = sfSprite_create();
		sfSprite_setTexture(star,texture,1);

		sfVector2f pos;
		pos.x = x;
		pos.y = y;

		sfVector2f scale;
		float current = 1;
		scale.x = current;
		scale.y = current;
		sfSprite_setScale(star,scale);
		sfSprite_setPosition(star,pos);
		jnx_list_add(star_field_list,star);
	}
}
void starfield_draw(sfRenderWindow *window,sfVector2f player_position)
{
	jnx_node *head = star_field_list->head;

	sfVector2f vsize = sfView_getSize(sfRenderWindow_getDefaultView(window));
	while(head)
	{
		sfSprite *current = (sfSprite*)head->_data;
		float x = sfSprite_getPosition(current).x;
		float y = sfSprite_getPosition(current).y;

		if(x > player_position.x - (vsize.x/2) && x < player_position.x + (vsize.x/2) && y > player_position.y - (vsize.y/2) && y < player_position.y +(vsize.y/2)){	

			sfRenderWindow_drawSprite(window,current,NULL);
		}

		head = head->next_node;
	}
}
