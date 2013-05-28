/*
 * =====================================================================================
 *
 *       Filename:  scoreboard.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  05/24/13 12:32:40
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  AlexsJones (), alexsimonjones@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */
#include <stdlib.h>
#include "scoreboard.h"
int score_count;
int score_max;
int score_max_achieved(void)
{
	if(score_count >= score_max)
		{
			return 1;
		}else
		{
			return 0;
		}
}
void score_reset(void)
{
	score_count = 0;
}
void score_setup(int max_score)
{
	score_count = 0;
	score_max = max_score;
}
void score_add_destroyed_obj(game_object *obj)
{
	score_count++;
}
int score_get_current(void)
{
	return score_count;
}

