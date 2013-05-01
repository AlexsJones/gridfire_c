/*
 * =====================================================================================
 *
 *       Filename:  cartographer.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  04/28/13 21:07:42
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */
#ifndef __CARTOGRAPHER_H__
#define __CARTOGRAPHER_H__
#include "../engine/game_object.h"
#include "../utils/geometry.h"
#include <jnxc_headers/jnxlist.h>



void cartographer_setbounds(int top, int bottom, int left, int right);
square *cartographer_getbounds(void);
void cartographer_add(game_object *obj);
jnx_list *cartographer_get_at(sfVector2f position);
#endif
