/*
 * =====================================================================================
 *
 *       Filename:  config_parser.h
 *
 *    Description:  Parsing commands for game configuration
 *
 *        Version:  1.0
 *        Created:  04/26/13 07:41:30
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */
#ifndef __CONFIG_PARSER_H__
#define __CONFIG_PARSER_H__
#include <jnxc_headers/jnx_list.h>
#include "../engine/game_object.h"
jnx_list* config_parser_load_configuration(char *path);
#endif
