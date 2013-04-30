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
typedef struct
{
	void **mapx;
	void **mapy;	
}stellarmap;

stellarmap *cartographer_seed(int map_size);
void cartographer_add(void);

#endif
