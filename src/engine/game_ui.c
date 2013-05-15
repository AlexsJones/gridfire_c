/*
 * =====================================================================================
 *
 *       Filename:  game_ui.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  05/14/13 07:42:19
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  AlexsJones (), alexsimonjones@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */
#include <stdlib.h>
#include "game_ui.h"
#include <unistd.h>
#include <jnxc_headers/jnxlog.h>
#include <stdio.h>
#include <string.h>
#define FONTPATH "res/8bit.ttf"
sfText *player_health_text = NULL;
sfFont *game_ui_font = NULL;

sfText *game_ui_text_builder(char *string, sfVector2f position, sfColor color,sfTextStyle style,float size)
{
	sfText *temp = sfText_create();
	if(game_ui_font == NULL)
	{
		game_ui_font = sfFont_createFromFile(FONTPATH);
		if(game_ui_font == NULL) { jnx_log("Critical error loading game font, exiting!\n"); exit(1); };
	}
	sfText_setFont(temp,game_ui_font);
	sfText_setString(temp,string);
	sfText_setColor(temp,color);
	sfText_setPosition(temp,position);
	sfText_setStyle(temp,style);
	sfText_setCharacterSize(temp,size);
	return temp;
}
int game_ui_setup(sfRenderWindow *main_window, sfView *main_view)
{
	
	/*-----------------------------------------------------------------------------
	 *  Player health text in top left
	 *-----------------------------------------------------------------------------*/
	sfVector2f pos = sfView_getCenter(main_view);
	sfVector2f view_size = sfView_getSize(main_view);
	sfVector2f newpos;
	newpos.x	= pos.x - (view_size.x /2);
	newpos.y = pos.y - (view_size.y /2);
	char stringbuf[1024];
	sprintf(stringbuf,"Health - %d",0);
	player_health_text = game_ui_text_builder(stringbuf, newpos, sfColor_fromRGB(255,255,0), sfTextRegular, 25);
	jnx_log("Created game ui\n");

	return 0;
}
void game_ui_update(sfRenderWindow *main_window, sfView *view, game_object *player)
{
	sfVector2f pos = sfView_getCenter(view);
	sfVector2f view_size = sfView_getSize(view);
	sfVector2f newpos;
	newpos.x	= pos.x - (view_size.x /2);
	newpos.y = pos.y - (view_size.y /2);
	sfText_setPosition(player_health_text,newpos);

	char stringbuf[1024];
	int health = player->health;
	if(health <= 0) { health = 0; }
	sprintf(stringbuf,"Health %d",health);
	sfText_setString(player_health_text,stringbuf);
}
void game_ui_draw(sfRenderWindow *main_window)
{
	sfRenderWindow_drawText(main_window,player_health_text,NULL);
}
