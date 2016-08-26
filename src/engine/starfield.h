/*
 * =====================================================================================
 *
 *       Filename:  starfield.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  05/01/13 11:40:33
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  AlexsJones (), alexsimonjones@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */
#ifndef __STARFIELD_H__
#define __STARFIELD_H__
#include <SFML/Graphics.h>
#include "../utils/geometry.h"
#include <jnxc_headers/jnx_list.h>
jnx_list *starfield_menu_create(sfView *view);
void starfield_create(square *bounds,int density);
void starfield_draw(sfView *view,sfRenderWindow *window,sfVector2f player_position);
#endif
