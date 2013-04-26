/*
 * =====================================================================================
 *
 *       Filename:  gridfire.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  04/25/13 17:20:03
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "game.h"
#include <jnxc_headers/jnxlog.h>
#define GAMECONFIGURATION "conf/game.conf"
#define GAMELOG "log/game.log"
int main(int argc, char **argv)
{
	jnx_log_setup(GAMELOG);
	jnx_log("Starting game setup\n");	
	if(game_setup() == 0 && game_load(GAMECONFIGURATION) == 0)
	{
		game_run();
	}
	else{
		return 1;
	}	
	return 0;
}
