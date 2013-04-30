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

enum instruction_type { OBJECT_TYPE, TEXTURE_DATA, LOC_X, LOC_Y, HEALTH, ROTATION } instruction_type;
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
data_object* process_line(char *line)
{
	data_object *data = malloc(sizeof(data_object));
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
					data->texture_data_path = malloc(strlen(temp));
					strcpy(data->texture_data_path,temp);
					break;
				case LOC_X:
					data->x = atoi(temp);
					break;
				case LOC_Y:
					data->y = atoi(temp);
					break;
				case HEALTH:
					data->health = atoi(temp);
					break;
				case ROTATION:
					data->rotation = (float)atoi(temp);
			}
			++instruction_number;
			counter = 0;
		}else
		{
			++counter;
		}
		head_line++;
	}
	printf("Object created %s %d %d %d %g\n",data->texture_data_path,data->x,data->y,data->health,data->rotation);
	return data;
}
jnx_list* config_parser_load_configuration(char *path)
{
	jnx_log("config_parser_load_configuration working\n");
	jnx_list *config_list = jnx_list_init();
	/*-----------------------------------------------------------------------------
	 *  Read our configuration into a malloc'd array
	 *-----------------------------------------------------------------------------*/
	char *buffer = jnx_file_read(path);
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
	jnx_log("Loaded from configuration file\n");
	return config_list;
}
