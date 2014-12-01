/*
 * =====================================================================================
 *
 *       Filename:  config_parser.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  04/26/13 07:42:01
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */
#include <stdlib.h>
#include "config_parser.h"
#include <string.h>
#include <stdio.h>
#include <jnxc_headers/jnxlog.h>
#include <jnxc_headers/jnxfile.h>

enum instruction_type { OBJECT_TYPE, TEXTURE_DATA, LOC_X, LOC_Y,MAXSPEED, HEALTH, ROTATION,VELOCITY,WEAPON_DAMAGE,WEAPON_TYPE } instruction_type;
char *strip_newline(char *s)
{
	char *p2 = s;
	while(*s != '\0'){
		if(*s != '\t' && *s != '\n')
		{
			*p2++ = *s++;
		}else{
			++s;
		}
	}
	*p2='\0';
}
sfSprite *sprite_from_texture(char *path)
{
	sfSprite *objsprite = sfSprite_create();
	sfTexture *_texture = sfTexture_createFromFile(path,NULL);
	sfSprite_setTexture(objsprite,_texture,1);
	sfVector2u texture_origin = sfTexture_getSize(_texture);
	float _x = (float)texture_origin.x;
	float _y = (float)texture_origin.y;
	sfVector2f new_org;
	new_org.x = _x /2 ;
	new_org.y = _y /2 ;
	sfSprite_setOrigin(objsprite,new_org);

	return objsprite;
}
game_object* process_line(char *line)
{
	game_object *data = malloc(sizeof(game_object));


	char *head_line = line;
	int counter = 0;
	int instruction_number = 0;
	while(*head_line !='\0')
	{
		if(*head_line == '#') // This is a comment line so ignore
		{
			continue;
		}
		if(*head_line == ',' || *(head_line+1) == '\0')
		{
			char temp[counter];
			strncpy(temp,head_line - counter, counter);
			temp[counter] = '\0';
			switch(instruction_number)
			{
				case OBJECT_TYPE:
					data->object_type = malloc(strlen(temp));
					strcpy(data->object_type,temp);
					break;
				case TEXTURE_DATA:
					data->sprite = sprite_from_texture(temp);	
					break;
				case LOC_X:
					data->position.x = atoi(temp);
					break;
				case LOC_Y:
					data->position.y = atoi(temp);
					break;
				case MAXSPEED:
					data->maxspeed = atoi(temp);
					break;
				case HEALTH:
					data->health = atoi(temp);
					break;
				case ROTATION:
					data->rotation = (float)atoi(temp);
					break;
				case VELOCITY:
					data->velocity = (float)atoi(temp);
					break;
				case WEAPON_DAMAGE:
					data->weapon_damage = (int)atoi(temp);
					break;
				case WEAPON_TYPE:
					data->weapon = (int)atoi(temp);
					break;
			}
			++instruction_number;
			counter = 0;
		}else
		{
			++counter;
		}
		head_line++;
	}

	if(strcmp(data->object_type,"player") == 0)
	{
		data->state = PLAYER;
	}
	else if(strcmp(data->object_type,"health") == 0 )
	{
		data->state = HEALTH_CONTAINER;
	}
	else if(data->velocity = 0)
	{
		data->state = STATIONARY;
	}
	else
	{
		data->state = MOVING;
	}
	/*-----------------------------------------------------------------------------
	 *  Not forgetting to set sprite rotation and position
	 *-----------------------------------------------------------------------------*/
	sfSprite_setPosition(data->sprite,data->position);
	sfSprite_rotate(data->sprite,data->rotation);
	return data;
}
jnx_list* config_parser_load_configuration(char *path)
{
	JNX_LOG(NULL,"config_parser_load_configuration working\n");
	jnx_list *config_list = jnx_list_create();
	/*-----------------------------------------------------------------------------
	 *  Read our configuration into a malloc'd array
	 *-----------------------------------------------------------------------------*/
	char *buffer;
    size_t bytes_read = jnx_file_read(path,&buffer,"r");
	char *buffer_walk = buffer;	
	while(*buffer_walk != '\0')
	{
		/*-----------------------------------------------------------------------------
		 *  Looking into the file
		 *-----------------------------------------------------------------------------*/
		if(*buffer_walk == '{')
		{
			*buffer_walk++;
			int current_line_length = 0;
			/*-----------------------------------------------------------------------------
			 *  We've found the end of a line, we cna use the current-line-counter to tell us the length
			 *-----------------------------------------------------------------------------*/
			while(*buffer_walk != '}')
			{
				buffer_walk++;
				++current_line_length;
			}
			char temp[current_line_length];
			bzero(temp,current_line_length);
			strncpy(temp,buffer_walk - current_line_length, current_line_length +1);
			temp[current_line_length +1] = '\0';
			printf("Processing %s\n",temp);
			jnx_list_add(config_list,(void*)process_line(temp));
		}
		*buffer_walk++;
	}
	free(buffer);
	JNX_LOG(NULL,"Loaded from configuration file\n");
	return config_list;
}
