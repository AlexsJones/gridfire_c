/*
 * =====================================================================================
 *
 *       Filename:  game.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  04/25/13 17:22:29
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */
#include <stdlib.h>
#include "engine/object_builder.h"
#include "engine/game_object.h"
#include "logic/cartographer.h"
#include "game.h"
#include "utils/config_parser.h"
#include <jnxc_headers/jnxlog.h>
#include <jnxc_headers/jnxlist.h>
#include <string.h>
#include <stdio.h>
sfVideoMode videomode;
sfRenderWindow *main_window;
sfView *main_view;
sfColor clear_color;

/*-----------------------------------------------------------------------------
 *  Player handle for view and camera purposes
 *-----------------------------------------------------------------------------*/
game_object *player = NULL;
int game_setup()
{
	videomode = sfVideoMode_getDesktopMode();
	jnx_log("Video mode is %d %d\n",videomode.width,videomode.height);	
	main_window = sfRenderWindow_create(videomode,"Gridfire",sfDefaultStyle,NULL);
	sfRenderWindow_setFramerateLimit(main_window,30);
	main_view = sfView_create();
	sfVector2f view_size;
	view_size.x = videomode.width;
	view_size.y = videomode.height;
	sfView_setSize(main_view,view_size);
	clear_color = sfColor_fromRGB(0,0,0);
	jnx_log("Initial setup complete\n");	
	return 0;
}
int game_load(char *configuration_path)
{
	jnx_log("Starting game_load\n");	
	/*-----------------------------------------------------------------------------
	 *  Perform object loading
	 *-----------------------------------------------------------------------------*/
	jnx_list *configuration_list = config_parser_load_configuration(configuration_path);
	jnx_node *head = configuration_list->head;

	while(head)
	{
		data_object *obj = (data_object*)head->_data;
		/*-----------------------------------------------------------------------------
		 *  Here we transfer ownership from the configuration list to the draw queue
		 *  This also involves a conversion element to produce a sprite object
		 *-----------------------------------------------------------------------------*/
		game_object *game_obj = object_builder_create(obj->object_type,obj->texture_data_path,obj->x,obj->y,obj->health,obj->rotation);
		
		/*-----------------------------------------------------------------------------
		 *  Setup a pointer to player
		 *-----------------------------------------------------------------------------*/
		if(strcmp(game_obj->object_type,"player") == 0)
		{
			player = game_obj;
		}	
		cartographer_add(game_obj);
		head = head->next_node;
	}

	jnx_list_delete(configuration_list);
	head = NULL;

	if(player == NULL)
	{
		jnx_log("Could not find the player from the loaded configuration file!\n Cannot have a game without a player\n");
		return 1;
	}

	jnx_log("Done\n");
	return 0;
}
void game_run()
{
	jnx_log("Starting run loop\n");
	sfEvent current_event;
	while(sfRenderWindow_isOpen(main_window))
	{
		sfRenderWindow_pollEvent(main_window,&current_event);
		switch(current_event.key.code)
		{
			case sfKeyEscape:
				sfRenderWindow_close(main_window);
				break;
		}
		sfRenderWindow_clear(main_window,clear_color);	
		/*-----------------------------------------------------------------------------
		 *  Set the current view
		 *-----------------------------------------------------------------------------*/
		sfRenderWindow_setView(main_window,main_view);
		/*-----------------------------------------------------------------------------
		 *  Draw objects
		 *-----------------------------------------------------------------------------*/
		jnx_node *current_draw_pos = cartographer_get_at(player->position)->head; 
		while(current_draw_pos)
		{
			game_object *obj = (game_object*)current_draw_pos->_data;
			if(strcmp(obj->object_type,"player") == 0)
			{
				game_object_update(obj,current_event);				
				sfView_setCenter(main_view,sfSprite_getPosition(obj->sprite));
			}
			sfRenderWindow_drawSprite(main_window,obj->sprite,NULL);
			current_draw_pos = current_draw_pos->next_node;
		}
		/*-----------------------------------------------------------------------------
		 *  Display window
		 *-----------------------------------------------------------------------------*/
		sfRenderWindow_display(main_window);
	}
	sfRenderWindow_destroy(main_window);
}
