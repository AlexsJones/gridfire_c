/*
 * =====================================================================================
 *
 *       Filename:  object_builder.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  04/26/13 16:00:56
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */
#ifndef __OBJECT_BUILDER_H__
#define __OBJECT_BUILDER_H__
#include <SFML/Graphics.h>
#include <SFML/Window.h>
#include "game_object.h"

game_object *object_builder_create(char *object_type, char *texture_data,int x, int y, int health, float rotation,float velocity,int damage);
#endif
