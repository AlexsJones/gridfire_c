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
#include "logic/scoreboard.h"
#include <SFML/Audio.h>
#define GAMECONFIGURATION "conf/game.conf"
#include <pthread.h>
sfVideoMode videomode;
sfRenderWindow *main_window;
sfView *main_view;
sfColor clear_color;
sfClock *_clock;
int loading_flag = 0;
int loading_started = 0;
/*-----------------------------------------------------------------------------
 *  Game text
 *-----------------------------------------------------------------------------*/
sfText *next_level_text = NULL;
sfText *next_level_button_text = NULL;
sfText *game_over_text = NULL;
sfText *game_start_text = NULL;
sfText *game_author_text = NULL;
sfText *game_start_button_text = NULL;
sfText *game_loading_text = NULL;
sfText *game_finish_text = NULL;
int text_yellow = 1;
/*-----------------------------------------------------------------------------
 *  Player handle for view and camera purposes
 *-----------------------------------------------------------------------------*/
game_object *player = NULL;
typedef enum { GAMESTART,RUNNING,NEXT_LEVEL, GAMEOVER,LOADING,COMPLETE } game_state;
game_state current_game_state;
/*-----------------------------------------------------------------------------
 *  Keeping track of current level and game position
 *-----------------------------------------------------------------------------*/
int max_levels = 0;
int current_level = 0;

int game_setup(jnx_hashmap *configuration)
{
	assert(configuration);
	config = configuration;
	assert(config);
	videomode = sfVideoMode_getDesktopMode();
	JNX_LOG(NULL,"Video mode is %d %d\n",videomode.width,videomode.height);	
	main_window = sfRenderWindow_create(videomode,"Gridfire",sfDefaultStyle,NULL);
	int max_fps = atoi(jnx_hash_get(config,"MAXFPS"));
	assert(max_fps);
	sfRenderWindow_setFramerateLimit(main_window,max_fps);
	main_view = sfView_create();
	sfVector2f view_size;
	view_size.x = videomode.width;
	view_size.y = videomode.height;
	sfView_setSize(main_view,view_size);
	clear_color = sfColor_fromRGB(0,0,0);
	JNX_LOG(NULL,"Creating game _clock\n");
	_clock = sfClock_create();
	JNX_LOG(NULL,"Creating bounding map\n");
	int game_bound = atoi(jnx_hash_get(configuration,"GAMEBOUNDS"));
	cartographer_setbounds(0,game_bound,0,game_bound);

	int star_density = atoi(jnx_hash_get(configuration,"STARCOUNT"));
	starfield_create(cartographer_getbounds(),star_density);
	JNX_LOG(NULL,"Initial setup complete\n");	
	/*-----------------------------------------------------------------------------
	 *  Game text
	 *-----------------------------------------------------------------------------*/
	game_start_text = game_ui_text_builder("GRIDFIRE",sfView_getCenter(main_view),sfColor_fromRGB(255,0,0),sfTextRegular,40);
	game_over_text = game_ui_text_builder("GAME OVER",sfView_getCenter(main_view),sfColor_fromRGB(255,255,255),sfTextRegular,30);
	game_start_button_text = game_ui_text_builder("Start",sfView_getCenter(main_view),sfColor_fromRGB(255,0,0),sfTextRegular,15);
	game_author_text = game_ui_text_builder("By Alex Jones",sfView_getCenter(main_view),sfColor_fromRGB(255,0,0),sfTextRegular,15);
	next_level_text = game_ui_text_builder("Congratulations",sfView_getCenter(main_view),sfColor_fromRGB(255,255,255),sfTextRegular,45);
	next_level_button_text = game_ui_text_builder("Press enter for the next level",sfView_getCenter(main_view),sfColor_fromRGB(255,0,0),sfTextRegular,20);
	game_loading_text = game_ui_text_builder("LOADING",sfView_getCenter(main_view),sfColor_fromRGB(255,0,0),sfTextRegular,40);
	game_finish_text = game_ui_text_builder("GAME COMPLETE",sfView_getCenter(main_view),sfColor_fromRGB(255,0,0),sfTextRegular,40);
	assert(game_finish_text);
	assert(game_loading_text);
	assert(next_level_button_text);
	assert(game_start_text);
	assert(game_over_text);
	assert(game_start_button_text);
	assert(game_author_text);
	assert(next_level_text);	
	/*-----------------------------------------------------------------------------
	 *  Game level setup
	 *-----------------------------------------------------------------------------*/
	max_levels = atoi(jnx_hash_get(configuration,"MAXLEVELS"));
	assert(max_levels);
	//start on level one
	current_level = 1;	
	/*-----------------------------------------------------------------------------
	 *  Scoreboard setup
	 *-----------------------------------------------------------------------------*/
	score_setup(atoi(jnx_hash_get(configuration,"MAXSCORE")));
	/*-----------------------------------------------------------------------------
	 *  Load weapon textures
	 *-----------------------------------------------------------------------------*/
	weapon_setup();
	/*-----------------------------------------------------------------------------
	 *  Load ingame music
	 *-----------------------------------------------------------------------------*/
	audio_control_setup(configuration);
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
void *game_load(void *args)
{
	char *configuration_path = GAMECONFIGURATION;
	loading_flag = 0;
	JNX_LOG(NULL,"Starting game_load\n");	
	/*-----------------------------------------------------------------------------
	 *  Perform object loading
	 *-----------------------------------------------------------------------------*/
	jnx_list *configuration_list = config_parser_load_configuration(configuration_path);
	jnx_node *head = configuration_list->head;

	while(head)
	{
		game_object *obj = (game_object*)head->_data;
		/*-----------------------------------------------------------------------------
		 *  Setup a pointer to player
		 *-----------------------------------------------------------------------------*/
		if(strcmp(obj->object_type,"player") == 0)
		{
			player = obj;
		}	
		cartographer_add(obj);
		head = head->next_node;
	}
	jnx_list_destroy(&configuration_list);
	head = NULL;
	if(player == NULL)
	{
		JNX_LOG(NULL,"Could not find the player from the loaded configuration file!\n Cannot have a game without a player\n");
		exit(0);
	}
	/*-----------------------------------------------------------------------------
	 *  Start results
	 *-----------------------------------------------------------------------------*/

	JNX_LOG(NULL,"Done\n");
	loading_flag = 1;
}
void game_setup_next_level()
{
	if(current_level < max_levels)
	{
		current_level++;
	}
	/*-----------------------------------------------------------------------------
	 *  Purge existing game objects
	 *-----------------------------------------------------------------------------*/
	cartographer_clear();
	player = NULL;
	current_game_state = LOADING;
}
void game_run()
{
	JNX_LOG(NULL,"Starting run loop\n");
	sfEvent current_event;
	sfTime time;
	float current_time;
	while(sfRenderWindow_isOpen(main_window))
	{
		switch(current_game_state)
		{
			case COMPLETE:
				sfRenderWindow_clear(main_window,clear_color);	
				sfRenderWindow_pollEvent(main_window,&current_event);
				switch(current_event.key.code)
				{
					case sfKeyReturn:
						sfRenderWindow_close(main_window);
				}
				sfVector2f completepos = sfView_getCenter(main_view);
				int string_length = strlen(sfText_getString(game_finish_text));
				int complete_offset = sfText_getCharacterSize(game_finish_text) * string_length;
				completepos.x = completepos.x - (complete_offset / 2);
				sfText_setPosition(game_finish_text,completepos);

				sfRenderWindow_drawText(main_window,game_finish_text,NULL);
				sfRenderWindow_display(main_window);	
				break;
			case NEXT_LEVEL:
				sfRenderWindow_clear(main_window,clear_color);	
				sfRenderWindow_pollEvent(main_window,&current_event);
				switch(current_event.key.code)
				{
					case sfKeyEscape:
						sfRenderWindow_close(main_window);
						break;
					case sfKeyReturn:
						game_setup_next_level();
						break;
				}
				sfVector2f nlpos = sfView_getCenter(main_view);
				int nltext_offset = strlen(sfText_getString(next_level_text));
				nltext_offset = nltext_offset * sfText_getCharacterSize(next_level_text);
				sfVector2f nlnewpos;
				nlnewpos.x	= nlpos.x - (nltext_offset / 2);
				nlnewpos.y = nlpos.y;
				sfText_setPosition(next_level_text,nlnewpos);
				int nlbt_offset = strlen(sfText_getString(next_level_button_text));
				nlbt_offset = nlbt_offset * sfText_getCharacterSize(next_level_button_text);
				nlnewpos.x = nlpos.x - (nlbt_offset /2);
				nlnewpos.y = nlnewpos.y + 50;
				sfText_setPosition(next_level_button_text,nlnewpos);
				switch(text_yellow)
				{
					case 0:
						sfText_setColor(next_level_button_text,sfColor_fromRGB(255,255,0));
						text_yellow = 1;
						break;
					case 1:
						sfText_setColor(next_level_button_text,sfColor_fromRGB(255,0,0));
						text_yellow = 0;
						break;
				}
				sfRenderWindow_drawText(main_window,next_level_text,NULL);
				sfRenderWindow_drawText(main_window,next_level_button_text,NULL);
				sfRenderWindow_display(main_window);	
				break;
			case RUNNING:
				time = sfClock_getElapsedTime(_clock);
				current_time = sfTime_asSeconds(time);
				sfRenderWindow_pollEvent(main_window,&current_event);
				/*-----------------------------------------------------------------------------
				 *  Slowly zoom in as we start the level
				 *-----------------------------------------------------------------------------*/
			/*  	if(sfView_getSize(main_view).x > videomode.width)
				{
					sfView_zoom(main_view,0.99f);
				}
			*/
				switch(current_event.key.code)
				{
					case sfKeyEscape:
						sfRenderWindow_close(main_window);
						break;
				}
				if(score_max_achieved() == 1)
				{
					if(current_level < max_levels)
					{
						current_game_state = NEXT_LEVEL;
					}else if(current_level == max_levels)
					{
						current_game_state = COMPLETE;
					}
					score_reset();
				}				
				sfRenderWindow_clear(main_window,clear_color);	
				/*-----------------------------------------------------------------------------
				 *  Set the current view
				 *-----------------------------------------------------------------------------*/
				if(player != NULL){
					sfView_setCenter(main_view,sfSprite_getPosition(player->sprite));
					sfRenderWindow_setView(main_window,main_view);
				}
				/*-----------------------------------------------------------------------------
				 *  Draw starfield
				 *-----------------------------------------------------------------------------*/
				if(player != NULL){
					starfield_draw(main_view,main_window,sfSprite_getPosition(player->sprite));	
				}
				/*-----------------------------------------------------------------------------
				 *  Draw objects
				 *-----------------------------------------------------------------------------*/
				jnx_list *draw_queue = cartographer_get_at(main_view);
				if(draw_queue != NULL){
					jnx_node *current_draw_pos = draw_queue->head; 
					/*-----------------------------------------------------------------------------
					 *  Draw weapon fire
					 *-----------------------------------------------------------------------------*/
					weapon_draw(main_window,main_view,&draw_queue);
					while(current_draw_pos)
					{
						game_object *obj = (game_object*)current_draw_pos->_data;
						if(strcmp(obj->object_type,"player") == 0)
						{
							game_object_update(obj,current_event,main_view);				
						}
						else
						{
							/*-----------------------------------------------------------------------------
							 *  Update AI objects
							 *-----------------------------------------------------------------------------*/
							game_ai_update(obj,player);	
						}
#ifdef BOUNDING_BOX
						sfRectangleShape *bounding = game_object_get_boundingRect(obj);
						sfRenderWindow_drawRectangleShape(main_window,bounding,NULL);
						sfRectangleShape_destroy(bounding);
#endif
						sfRenderWindow_drawSprite(main_window,obj->sprite,NULL);
						current_draw_pos = current_draw_pos->next_node;
					}
					cartographer_update();
				}
				/*-----------------------------------------------------------------------------
				 *  Draw ingame ui
				 *-----------------------------------------------------------------------------*/
				game_ui_update(main_window,main_view,player,draw_queue);
				game_ui_draw(main_window,draw_queue);
				sfRenderWindow_display(main_window);
				jnx_list_destroy(&draw_queue);
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
				int game_bound = atoi(jnx_hash_get(config,"GAMEBOUNDS"));
				switch(current_event.key.code)
				{
					case sfKeyEscape:
						sfRenderWindow_close(main_window);
						break;
					case sfKeySpace:

						play_music(INGAMEMUSIC);
						current_game_state = LOADING;
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
				button_start.y = button_start.y + 50;
				sfText_setPosition(game_author_text,button_start);
				switch(text_yellow)
				{
					case 0:
						sfText_setColor(game_start_button_text,sfColor_fromRGB(255,255,0));
						sfText_setColor(game_start_text,sfColor_fromRGB(255,255,0));
						text_yellow = 1;
						break;
					case 1:
						sfText_setColor(game_start_button_text,sfColor_fromRGB(255,0,0));
						sfText_setColor(game_start_text,sfColor_fromRGB(255,0,0));
						text_yellow = 0;
						break;
				}
				jnx_list *menu_starfield = starfield_menu_create(main_view);
				jnx_node *head = menu_starfield->head;
				while(menu_starfield->head)
				{
					sfSprite *sprite = menu_starfield->head->_data;
					sfVector2f pos = sfSprite_getPosition(sprite);
					pos.y = pos.y +5;
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
				sfRenderWindow_drawText(main_window,game_author_text,NULL);
				sfRenderWindow_display(main_window);	
				break;
			case LOADING:
				sfRenderWindow_clear(main_window,clear_color);
				sfRenderWindow_setView(main_window,main_view);
				if(loading_started == 0)
				{
					//spawn thread
					pthread_t load_worker;
					pthread_create(&load_worker,NULL,game_load,NULL);
					loading_started = 1;
				}
				if(loading_flag == 1)
				{
					//break and start game
					loading_started = 0;
					loading_flag = 0;
					sfVector2f viewpos;
					viewpos.x = game_bound /2;
					viewpos.y = game_bound /2;
					sfView_setCenter(main_view,viewpos);
					sfVector2f size = sfView_getSize(main_view);
					size.x = size.x *2;
					size.y = size.y *2;
					/*-----------------------------------------------------------------------------
					 *  Set the zoom a bit further out so on level start we can zoom in
					 *-----------------------------------------------------------------------------*/
				//	sfView_setSize(main_view,size);
					current_game_state = RUNNING;
					printf("Loading done\n");	
					break;
				}
				sfVector2f loadingpos = sfView_getCenter(main_view); 
				int loading_offset = strlen(sfText_getString(game_loading_text));
				loading_offset = loading_offset * sfText_getCharacterSize(game_loading_text);
				loadingpos.x = loadingpos.x - (loading_offset /2);
				loadingpos.y = loadingpos.y - (loading_offset /2);
				switch(text_yellow)
				{
					case 0:
						sfText_setColor(game_loading_text,sfColor_fromRGB(255,255,0));
						text_yellow = 1;
						break;
					case 1:
						sfText_setColor(game_loading_text,sfColor_fromRGB(255,0,0));
						text_yellow = 0;
						break;
				}
				sfText_setPosition(game_loading_text,loadingpos);
				sfRenderWindow_drawText(main_window,game_loading_text,NULL);
				sfRenderWindow_display(main_window);
				break;
		}
	}
}
void game_end(void)
{
	current_game_state = GAMEOVER;
}
