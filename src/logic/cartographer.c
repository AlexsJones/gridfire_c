/*
 * =====================================================================================
 *
 *       Filename:  cartographer.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  04/28/13 21:10:33
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */
#include <stdlib.h>
#include "cartographer.h"
#include <string.h>
#include <stdio.h>
#include <jnxc_headers/jnxlist.h>
#include <jnxc_headers/jnxlog.h>
square *bounds_map = NULL;

jnx_list *object_list;
void cartographer_add(game_object *obj)
{
	if(object_list == NULL) { object_list = jnx_list_init(); }
	/*-----------------------------------------------------------------------------
	 *  Temporary solution whilst I create an algorithm for search 
	 *-----------------------------------------------------------------------------*/
	jnx_list_add(object_list,obj);
}
jnx_list *cartographer_get_at(sfVector2f position)
{

	/*-----------------------------------------------------------------------------
	 *  Again a temporary solution to return the entire list
	 *-----------------------------------------------------------------------------*/

	/*-----------------------------------------------------------------------------
	 *  Note, that you probably don't want to return the original list ever as any manipulation outside of this functionality could cause error
	 *-----------------------------------------------------------------------------*/
	return object_list;
}
void cartographer_setbounds(int top, int bottom, int left, int right)
{
	bounds_map = malloc(sizeof(square));
	bounds_map->top = top;
	bounds_map->bottom = bottom;
	bounds_map->left = left;
	bounds_map->right = right;
	jnx_log("Set new bounds map\n");
}
square *cartographer_getbounds(void)
{
	if(bounds_map == NULL) { jnx_log("Error getting bounds - no map set\n");return NULL; }
	return bounds_map;
}
