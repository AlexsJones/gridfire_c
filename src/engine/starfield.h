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
void starfield_create(square *bounds,int density);
void starfield_draw(sfRenderWindow *window);
#endif
