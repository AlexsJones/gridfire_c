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
#include <jnxc_headers/jnx_log.h>
#include <jnxc_headers/jnx_file.h>
#include <jnxc_headers/jnx_hash.h>
#define GAMESETTINGS "conf/settings.conf"
#define GAMELOG "log/game.log"
#include <X11/Xlib.h>
jnx_hashmap *create_configuration()
{
	jnx_hashmap *map = jnx_file_read_kvp(GAMESETTINGS,1024,"=");
	const char **keys;

	int count = jnx_hash_get_keys_ts(map,&keys);	
	int x;
	for(x=0;x<count; ++x) {
		char *value = jnx_hash_get(map,keys[x]);
		JNX_LOG(NULL,"Map [Key: %s][Value: %s]\n",keys[x],value);
	}
	return map;
}
int main(int argc, char **argv)
{
	
	/*-----------------------------------------------------------------------------
	 *  Very important to note that XInitThreads is a linux implementation only
	 *-----------------------------------------------------------------------------*/
	XInitThreads();
	JNX_LOG(NULL,"Starting game setup\n");	

	jnx_hashmap *config = create_configuration();
	
	if(game_setup(config) == 0)
	{
		game_run();
	}
	else{
		return 1;
	}	
	return 0;
}
