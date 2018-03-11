/*****************************************************************************

GENERAL:
    HEADER_NAME:    sn_parser.h
    COMPANION_C:    sn_parser.c
    AUTHOR:         Theo Naunheim <theonaunheim@gmail.com>
    COPYRIGHT:      Theo Naunheim, 2018
    LICENSE:        MIT
    DESCRIPTION:    This file defines the sn_parser_t struct and its
                    associated SNParser() function. This struct allows for
                    simplified parsing files.

CONSTRUCTOR:
    SNParser:       Builds the parser.

ATTRIBUTES:
    self:           Instance reference.
    port:           Port for socket pulled from configuration files.
    path_size:      Length of path. 
    text_size:      Length of text.
    path:           Path to config file.
    text:           Text of config file.

METHODS:
    destroy         Cleans up logger and removes data. 
    read            Reads text file into struct.
    parse           Parses text and populates struct members.

*/////////////////////////////////////////////////////////////////////////////


#ifndef SN_PARSER_H
#define SN_PARSER_H

#include <stdint.h>
#include <stdlib.h>


typedef struct sn_parser_t {

    // Attributes
    struct sn_parser_t *self;
    uint16_t            port;
    size_t              path_size;
    size_t              text_size;
    char               *path;
    char               *text;

    // Methods
    void               (*destroy) (struct sn_parser_t *);
    void               (*_read)   (struct sn_parser_t *);
    void               (*_parse)  (struct sn_parser_t *);

} sn_parser_t;

sn_parser_t * SNParser(void);


#endif