/*
 * =====================================================================================
 *
 *       Filename:  game_ui.h
 *
 *    Description:  :
 *
 *        Version:  1.0
 *        Created:  05/14/13 07:42:01
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  AlexsJones (), alexsimonjones@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */
#ifndef __GAME_UI_H__
#define __GAME_UI_H__
#include <SFML/Graphics.h>
#include <jnxc_headers/jnxlist.h>
#include "game_object.h"
#include "../logic/cartographer.h"
#include "../logic/scoreboard.h"
#include "radar.h"
int game_ui_setup(sfRenderWindow *main_window, sfView *main_view);
sfText *game_ui_text_builder(char *string, sfVector2f position, sfColor color,sfTextStyle style,float size);
void game_ui_update(sfRenderWindow *main_window, sfView *view,game_object *player,jnx_list *draw_queue);
void game_ui_draw(sfRenderWindow *main_window,jnx_list *draw_queue);
#endif
