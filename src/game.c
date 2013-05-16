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
#include "engine/starfield.h"
#include "logic/cartographer.h"
#include "game.h"
#include "engine/weapon_control.h"
#include "logic/game_ai.h"
#include "utils/config_parser.h"
#include <jnxc_headers/jnxlog.h>
#include <jnxc_headers/jnxlist.h>
#include <string.h>
#include <stdio.h>
#include "engine/game_ui.h"
#include "logic/audio_control.h"
#include <SFML/Audio.h>
#define GAMEBOUNDSSIZE 25000
#define STARFIELDDENSITY 100000
sfVideoMode videomode;
sfRenderWindow *main_window;
sfView *main_view;
sfColor clear_color;
sfClock *clock;

/*-----------------------------------------------------------------------------
 *  Game text
 *-----------------------------------------------------------------------------*/
sfText *game_over_text = NULL;
sfText *game_start_text = NULL;
sfText *game_start_button_text = NULL;
int text_yellow = 1;
/*-----------------------------------------------------------------------------
 *  Player handle for view and camera purposes
 *-----------------------------------------------------------------------------*/
game_object *player = NULL;
typedef enum { GAMESTART,RUNNING, GAMEOVER } game_state;
game_state current_game_state;
int game_setup()
{
	videomode = sfVideoMode_getDesktopMode();
	jnx_log("Video mode is %d %d\n",videomode.width,videomode.height);	
	main_window = sfRenderWindow_create(videomode,"Gridfire",sfDefaultStyle,NULL);
	sfRenderWindow_setFramerateLimit(main_window,60);
	main_view = sfView_create();
	sfVector2f view_size;
	view_size.x = videomode.width;
	view_size.y = videomode.height;
	sfView_setSize(main_view,view_size);
	clear_color = sfColor_fromRGB(0,0,0);
	jnx_log("Creating game clock\n");
	clock = sfClock_create();
	jnx_log("Creating bounding map\n");
	cartographer_setbounds(0,GAMEBOUNDSSIZE,0,GAMEBOUNDSSIZE);
	starfield_create(cartographer_getbounds(),STARFIELDDENSITY);
	jnx_log("Initial setup complete\n");	

	/*-----------------------------------------------------------------------------
	 *  Game text
	 *-----------------------------------------------------------------------------*/
	game_start_text = game_ui_text_builder("GRIDFIRE",sfView_getCenter(main_view),sfColor_fromRGB(255,0,0),sfTextRegular,40);
	game_over_text = game_ui_text_builder("GAME OVER",sfView_getCenter(main_view),sfColor_fromRGB(255,255,255),sfTextRegular,30);
	game_start_button_text = game_ui_text_builder("Start",sfView_getCenter(main_view),sfColor_fromRGB(255,0,0),sfTextRegular,15);
	/*-----------------------------------------------------------------------------
	 *  Set up ingame ui
	 *-----------------------------------------------------------------------------*/
	
	
	/*-----------------------------------------------------------------------------
	 *  Load ingame music
	 *-----------------------------------------------------------------------------*/
	audio_control_setup();
	play_music(TITLEMUSIC);
	if(game_ui_setup(main_window,main_view) != 0)
	{
		return 1;
	}

	/*-----------------------------------------------------------------------------
	 *  Set game state to running
	 *-----------------------------------------------------------------------------*/
	current_game_state = GAMESTART;
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
		game_object *game_obj = object_builder_create(obj->object_type,obj->texture_data_path,obj->x,obj->y,obj->health,obj->rotation,obj->velocity,obj->weapon_damage);


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
	while(configuration_list->head)
	{
		jnx_node *current_head = configuration_list->head;
		jnx_node *next_node = configuration_list->head->next_node;
		free(current_head);
		configuration_list->head = next_node;
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
	sfTime time;
	float current_time;
	while(sfRenderWindow_isOpen(main_window))
	{
		switch(current_game_state)
		{
			case RUNNING:
				time = sfClock_getElapsedTime(clock);
				current_time = sfTime_asSeconds(time);

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
				 *  Draw starfield
				 *-----------------------------------------------------------------------------*/
				starfield_draw(main_window,sfSprite_getPosition(player->sprite));	
				/*-----------------------------------------------------------------------------
				 *  Draw objects
				 *-----------------------------------------------------------------------------*/
				jnx_list *draw_queue = cartographer_get_at(sfView_getCenter(main_view));
				jnx_node *current_draw_pos = draw_queue->head; 
				/*-----------------------------------------------------------------------------
				 *  Draw weapon fire
				 *-----------------------------------------------------------------------------*/
				weapon_draw(main_window,main_view,&draw_queue);
				/*-----------------------------------------------------------------------------
				 *  Draw ingame ui
				 *-----------------------------------------------------------------------------*/
				game_ui_update(main_window,main_view,player);
				game_ui_draw(main_window);
				while(current_draw_pos)
				{
					game_object *obj = (game_object*)current_draw_pos->_data;
					if(strcmp(obj->object_type,"player") == 0)
					{
						game_object_update(obj,current_event,main_view);				
						sfView_setCenter(main_view,sfSprite_getPosition(obj->sprite));
					}
					else
					{
						/*-----------------------------------------------------------------------------
						 *  Update AI objects
						 *-----------------------------------------------------------------------------*/
						game_ai_update(obj,player);	
					}
#ifdef DEBUG
					sfRectangleShape *bounding = game_object_get_boundingRect(obj);
					sfRenderWindow_drawRectangleShape(main_window,bounding,NULL);
					sfRectangleShape_destroy(bounding);
#endif
					sfRenderWindow_drawSprite(main_window,obj->sprite,NULL);
					current_draw_pos = current_draw_pos->next_node;
				}
				/*-----------------------------------------------------------------------------
				 *  Display window
				 *-----------------------------------------------------------------------------*/
				sfRenderWindow_display(main_window);
				cartographer_update();
				break;

			case GAMEOVER:
				sfRenderWindow_clear(main_window,clear_color);	
				sfRenderWindow_pollEvent(main_window,&current_event);
				switch(current_event.key.code)
				{
					case sfKeyEscape:
						sfRenderWindow_close(main_window);
						break;
				}

				sfVector2f pos = sfView_getCenter(main_view);
				int text_offset = strlen(sfText_getString(game_over_text));
				text_offset = text_offset * sfText_getCharacterSize(game_over_text);
				sfVector2f newpos;
				newpos.x	= pos.x - (text_offset / 2);
				newpos.y = pos.y;
				sfText_setPosition(game_over_text,newpos);
				sfRenderWindow_drawText(main_window,game_over_text,NULL);
				sfRenderWindow_display(main_window);	
				break;

			case GAMESTART:
				sfRenderWindow_clear(main_window,clear_color);	
				sfRenderWindow_pollEvent(main_window,&current_event);
				switch(current_event.key.code)
				{
					case sfKeyEscape:
						sfRenderWindow_close(main_window);
						break;
					case sfKeySpace:
						play_music(INGAMEMUSIC);
						current_game_state = RUNNING;
						break;
				}
				sfVector2f pos_start = sfView_getCenter(main_view);
				int text_offset_start = strlen(sfText_getString(game_start_text));
				text_offset_start = text_offset_start * sfText_getCharacterSize(game_start_text);
				sfVector2f newpos_start;
				newpos_start.x	= pos_start.x + (text_offset_start /2 );
				newpos_start.y = pos_start.y - (text_offset_start /2);
				sfText_setPosition(game_start_text,newpos_start);

				sfVector2f button_start;
				button_start.x = newpos_start.x;
				button_start.y = newpos_start.y + 50;
				sfText_setPosition(game_start_button_text,button_start);

				switch(text_yellow)
				{
					case 0:
						sfText_setColor(game_start_button_text,sfColor_fromRGB(255,255,0));
						text_yellow = 1;
						break;
					case 1:
						sfText_setColor(game_start_button_text,sfColor_fromRGB(255,0,0));
						text_yellow = 0;
						break;
				}
	
				jnx_list *menu_starfield = starfield_menu_create(main_view);
				jnx_node *head = menu_starfield->head;
				while(menu_starfield->head)
				{
					sfSprite *sprite = menu_starfield->head->_data;
					sfVector2f pos = sfSprite_getPosition(sprite);
					pos.y = pos.y +1;
					if(pos.y > sfView_getSize(main_view).y)
					{
						pos.y = 0;
					}
					sfSprite_setPosition(sprite,pos);
					sfRenderWindow_drawSprite(main_window,sprite,NULL);
					menu_starfield->head = menu_starfield->head->next_node;
				}
				menu_starfield->head = head;
				sfRenderWindow_drawText(main_window,game_start_button_text,NULL);
				sfRenderWindow_drawText(main_window,game_start_text,NULL);
				sfRenderWindow_display(main_window);	
				break;
		}

	}
}
void game_end(void)
{
	current_game_state = GAMEOVER;
}
