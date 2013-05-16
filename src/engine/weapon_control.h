/*
 * =====================================================================================
 *
 *       Filename:  weapon_control.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  05/01/13 17:13:12
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  AlexsJones (), alexsimonjones@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */
#ifndef __WEAPON_CONTROL_H__
#define __WEAPON_CONTROL_H__
#include "game_object.h"
#include <SFML/Graphics.h>
#include <jnxc_headers/jnxlist.h>
void weapon_setup();
void weapon_fire(game_object *parent/*  more to come i.e weapon type, speed etc... */);
void weapon_draw(sfRenderWindow *window,sfView *view, jnx_list **draw_queue);
#endif
