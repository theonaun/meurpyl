/*

//////////////////////////////////////////////////////////////////////////////
Generally
//////////////////////////////////////////////////////////////////////////////

    HEADER_NAME:    hob_setting.h
    COMPANION_C:    hob_setting.c
    AUTHOR:         Theo Naunheim <theonaunheim@gmail.com>
    COPYRIGHT:      Theo Naunheim, 2018
    LICENSE:        MIT
    DESCRIPTION:    This file defines the hob_setting_t struct, and the 
                    hob_setting_new constructor. This is used as an element
                    of the parser. It also contains the
                    HOB_SETTING_BUFFER_SIZE constant.

//////////////////////////////////////////////////////////////////////////////
hob_settings_t
//////////////////////////////////////////////////////////////////////////////

    CONSTRUCTOR:
        hob_setting_new:        Builds setting.
        hob_setting_delete:     Destroys setting.

    MEMBERS:
        self:       Instance reference.
        next:       Next hob_setting_t in settings chain.
        key:        The name of the setting.
        type:       The type of the settings value.
        value:      The wrapped data (union) for the setting (long/str).

    ASSOCIATED:
        hob_setting_type_desc:  Describes type (CHAR_=0, LONG_=1).

*/

#ifndef HOB_SETTING_H
#define HOB_SETTING_H

#include <stdint.h>
#include <stdlib.h>

#define HOB_SETTING_BUFFER_SIZE 1028

enum hob_setting_type_desc {CHAR_, LONG_} hob_setting_type_desc;

typedef struct hob_setting_t {

    /* Members */ 
    struct hob_setting_t        *self;
    struct hob_setting_t        *next;
    char                        key  [HOB_SETTING_BUFFER_SIZE];
    enum hob_setting_type_desc  type;
    union                       {
                                    char char_[HOB_SETTING_BUFFER_SIZE];
                                    long long_;
                                } value;

} hob_setting_t;

/* Public functions */ 
hob_setting_t * hob_setting_new   (const char *);
void            hob_setting_delete(hob_setting_t *);

#endif