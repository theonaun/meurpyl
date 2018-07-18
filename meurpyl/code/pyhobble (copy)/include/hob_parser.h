/*

//////////////////////////////////////////////////////////////////////////////

GENERAL:
    HEADER_NAME:    hob_parser.h
    COMPANION_C:    hob_parser.c
    AUTHOR:         Theo Naunheim <theonaunheim@gmail.com>
    COPYRIGHT:      Theo Naunheim, 2018
    LICENSE:        MIT
    DESCRIPTION:    This file defines the hob_parser_t struct, the supporting
                    hob_setting_t struct, and the HOBParser() constructor. This
                    allows for simplified parsing files. It also contains the
                    P_BUFFER_SIZE constant.

//////////////////////////////////////////////////////////////////////////////

hob_settings_t

    ATTRIBUTES:     
        next:       Next hob_parser_t in settings chain.
        key:        The name of the setting (less than 100 char).
        type:       The type of the settings value.
        value:      The wrapped data (union) for the setting.

//////////////////////////////////////////////////////////////////////////////

hob_parser_t

    CONSTRUCTOR:
        HOBParser:   Builds the parser.

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


#ifndef HOB_PARSER_H
#define HOB_PARSER_H

#include <stdint.h>
#include <stdlib.h>

#define P_BUFFER_SIZE 1028


typedef struct hob_setting_t {

    struct hob_setting_t *next;
    char                 key[P_BUFFER_SIZE];
    char                 type[5];
    union value {
       char              char_[P_BUFFER_SIZE];
       long              long_;
    } value;

} hob_setting_t;


typedef struct hob_parser_t {

    // Attributes
    struct hob_parser_t *self;
    uint16_t             port;
    size_t               path_size;
    size_t               text_size;
    char                *path;
    char                *text;
    int                  newline_index[100];
    hob_setting_t      **settings_chain;

    // Methods
    void               (*destroy) (struct hob_parser_t *);
    void               (*_read)   (struct hob_parser_t *);
    void               (*_parse)  (struct hob_parser_t *);
    void               (*_get_nl) (struct hob_parser_t *);
    void               (*_map)    (struct hob_parser_t *, char *);

} hob_parser_t;


hob_parser_t * HOBParser(void);


#endif