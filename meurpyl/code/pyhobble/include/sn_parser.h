/*

//////////////////////////////////////////////////////////////////////////////

GENERAL:
    HEADER_NAME:    sn_parser.h
    COMPANION_C:    sn_parser.c
    AUTHOR:         Theo Naunheim <theonaunheim@gmail.com>
    COPYRIGHT:      Theo Naunheim, 2018
    LICENSE:        MIT
    DESCRIPTION:    This file defines the sn_parser_t struct, the supporting
                    sn_setting_t struct, and the SNParser() constructor. This
                    allows for simplified parsing files.

//////////////////////////////////////////////////////////////////////////////

sn_settings_t

    ATTRIBUTES:     
        next:       Next sn_parser_t in settings chain.
        key:        The name of the setting (less than 100 char).
        type:       The type of the settings value.
        value:      The wrapped data (union) for the setting.

//////////////////////////////////////////////////////////////////////////////

sn_parser_t

    CONSTRUCTOR:
        SNParser:   Builds the parser.

    ATTRIBUTES:
        self:       Instance reference.
        port:       Port for socket pulled from configuration files.
        path_size:  Length of path. 
        text_size:  Length of text.
        path:       Path to config file.
        text:       Text of config file.

    METHODS:
        destroy     Cleans up logger and removes data. 
        read        Reads text file into struct.
        parse       Parses text and populates struct members.

//////////////////////////////////////////////////////////////////////////////

*/


#ifndef SN_PARSER_H
#define SN_PARSER_H

#include <stdint.h>
#include <stdlib.h>


typedef struct sn_setting_t {

    struct sn_setting_t *next;
    char                 key[100];
    char                 type[5];
    union value {
       char              c[100];
       int               i;
       long              l;
    } value;

} sn_setting_t;


typedef struct sn_parser_t {

    // Attributes
    struct sn_parser_t *self;
    uint16_t            port;
    size_t              path_size;
    size_t              text_size;
    char               *path;
    char               *text;
    sn_setting_t       *settings_chain;

    // Methods
    void               (*destroy) (struct sn_parser_t *);
    void               (*_read)   (struct sn_parser_t *);
    void               (*_parse)  (struct sn_parser_t *);

} sn_parser_t;


sn_parser_t * SNParser(void);


#endif