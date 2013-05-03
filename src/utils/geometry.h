/*
 * =====================================================================================
 *
 *       Filename:  geometry.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  05/01/13 07:43:34
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */
#ifndef __GEOMETRY_H__
#define __GEOMETRY_H__
#include <SFML/Graphics.h>
typedef struct square
{
	int top;
	int bottom;
	int left;
	int right;
}square;

/*-----------------------------------------------------------------------------
 *  Return 1 on positive, Return 0 on negative
 *-----------------------------------------------------------------------------*/
int geometry_contains(square *container,sfVector2f position);
float geometry_distance(sfVector2f v1,sfVector2f v2);

#endif
