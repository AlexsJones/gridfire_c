/*
 * =====================================================================================
 *
 *       Filename:  scoreboard.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  05/24/13 12:32:26
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  AlexsJones (), alexsimonjones@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */
#ifndef __scoreboard_H__
#define __scoreboard_H__
#include "../engine/game_object.h"
void score_setup(int max_score);
void score_reset(void);
void score_add_destroyed_obj(game_object *obj);
int score_get_current(void);
int score_max_achieved(void);
#endif
