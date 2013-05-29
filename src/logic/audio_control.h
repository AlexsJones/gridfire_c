/*
 * =====================================================================================
 *
 *       Filename:  audio_control.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  05/16/13 16:33:42
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  AlexsJones (), alexsimonjones@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */
#ifndef __AUDIO_CONTROL_H__
#define __AUDIO_CONTROL_H__
#include <SFML/Audio.h>
#include <jnxc_headers/jnxhash.h>
typedef enum { TITLEMUSIC, INGAMEMUSIC }music_type;
void play_music(music_type m);
void play_sound(sfSound *sound);
void audio_control_setup(void);
/*-----------------------------------------------------------------------------
 *  weapon sounds
 *-----------------------------------------------------------------------------*/
sfSound *sound_laser;
sfSound *sound_laser2;
sfSound *sound_laser3;
sfSound *sound_laser4;
sfSound *sound_phaser;
sfSound *sound_lexplosion;

/*-----------------------------------------------------------------------------
 *  Music 
 *-----------------------------------------------------------------------------*/
sfMusic *title_music;
sfMusic *game_music;

#endif
