/*
 * =====================================================================================
 *
 *       Filename:  geometry.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  05/01/13 08:12:04
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  AlexsJones (), alexsimonjones@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */
#include <stdlib.h>
#include "geometry.h"
#include <math.h>

float geometry_distance(sfVector2f a,sfVector2f b)
{
	float k= sqrt((float)((a.x-b.x)*(a.x-b.x))+((a.y-b.y)*(a.y-b.y)));
	return k;
}
int geometry_contains(square *container,sfVector2f position)
{
	int x_flag = 0;
	int y_flag = 0;

	
	int posx = position.x;
	int posy = position.y;

	if(posx < container->right && posx > container->left)
	{
		x_flag = 1;
	}
	if(posy < container->bottom && posy > container->top)
	{
		y_flag = 1;
	}

	if(x_flag == 1 && y_flag == 1)
	{
		return 1;
	}

	return 0;
}
