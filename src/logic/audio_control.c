/*
 * =====================================================================================
 *
 *       Filename:  audio_control.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  05/16/13 16:34:49
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  AlexsJones (), alexsimonjones@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */
#include <stdlib.h>
#include "audio_control.h"
#include <stdio.h>
#include <jnxc_headers/jnxlog.h>
#include <assert.h>
/*-----------------------------------------------------------------------------
 *  External ref to the configuration
 *-----------------------------------------------------------------------------*/
extern jnx_hashmap *config;
sfSound *audio_control_build_sound(char *path)
{
	sfSoundBuffer *buffer = sfSoundBuffer_createFromFile(path);
	sfSound *sound = sfSound_create();
	sfSound_setBuffer(sound,buffer);
	return sound;
}
void audio_control_setup(void)
{
	sound_lexplosion = audio_control_build_sound("res/lexplosion.flac");
	assert(sound_lexplosion);
	sound_laser = audio_control_build_sound("res/laser01.flac");
	assert(sound_laser);	
	sound_laser2 = audio_control_build_sound("res/laser02.flac");
	assert(sound_laser2);
	sound_laser3 = audio_control_build_sound("res/laser03.flac");
	assert(sound_laser3);
	title_music = sfMusic_createFromFile("res/shiny-ship.flac");
	assert(title_music);
	game_music = sfMusic_createFromFile("res/starpause.flac");
	assert(game_music);
}
void play_music(music_type m)
{
	if(strcmp(jnx_hash_get(config,"MUSIC"),"OFF") == 0)
	{
		jnx_log("Music has been disabled\n");
		return;
	}

	switch(m)
	{
		case TITLEMUSIC:
			sfMusic_play(title_music);
			break;
		case INGAMEMUSIC:
			sfMusic_stop(title_music);
			sfMusic_play(game_music);
			break;		
	}
}
void play_sound(sfSound *sound)
{
	if(strcmp(jnx_hash_get(config,"SOUND"),"OFF") == 0)
	{
		return;
	}
	sfSound_play(sound);
}
