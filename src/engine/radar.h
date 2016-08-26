/*
 * =====================================================================================
 *
 *       Filename:  radar.h
 *
 *    Description`
 *
 *        Version:  1.0
 *        Created:  06/10/13 08:16:51
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  AlexsJones (), alexsimonjones@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */
#ifndef __RADAR_H__
#define __RADAR_H__
#include <SFML/Graphics.h>
#include <jnxc_headers/jnx_list.h>
void radar_setup(void);
void radar_update(sfView *view,sfRenderWindow *main_window);
void radar_draw(sfRenderWindow *main_window,jnx_list *draw_queue);
#endif
