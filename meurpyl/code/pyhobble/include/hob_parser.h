/*

//////////////////////////////////////////////////////////////////////////////

GENERAL:
    HEADER_NAME:    hob_parser.h
    COMPANION_C:    hob_parser.c
    AUTHOR:         Theo Naunheim <theonaunheim@gmail.com>
    COPYRIGHT:      Theo Naunheim, 2018
    LICENSE:        MIT
    DESCRIPTION:    This file defines the hob_parser_t struct, the supporting
                    hob_setting_t struct, and the hob_parser_new() constructor.
                    This allows for simplified parsing files. It also
                    contains the P_BUFFER_SIZE constant.

//////////////////////////////////////////////////////////////////////////////

hob_parser_t

    ATTRIBUTES:
        self:       Instance reference.
        port:       Port for socket pulled from configuration files.
        path_size:  Length of path. 
        text_size:  Length of text.
        path:       Path to config file.
        text:       Text of config file.

    PUBLIC FUNCTIONS:
        hob_parser_new:     Create parser.
        hob_parser_delete:  Delete parser.

//////////////////////////////////////////////////////////////////////////////

*/


#ifndef HOB_PARSER_H
#define HOB_PARSER_H


#include <stdint.h>
#include <stdlib.h>

#include "hob_setting.h"

#define HOB_PARSER_MAX_SETTINGS    100
#define HOB_PARSER_BUFFER_SIZE     1028

typedef struct hob_parser_t {

    // Attributes
    struct hob_parser_t *self;
    uint16_t             port;
    size_t               path_size;
    size_t               text_size;
    char                *path;
    char                *text;
    int                  newline_index[100];
    hob_setting_t       *settings_chain;

} hob_parser_t;


// Constructor and deconstructor
hob_parser_t * hob_parser_new   (void);
int            hob_parser_delete(hob_parser_t *);


#endif