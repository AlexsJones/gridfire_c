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
int game_ui_setup(sfRenderWindow *main_window, sfView *main_view);
void game_ui_update(sfRenderWindow *main_window, sfView *view,jnx_list **draw_queue);
void game_ui_draw(sfRenderWindow *main_window);
#endif
