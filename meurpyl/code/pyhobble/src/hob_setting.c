#include <errno.h>
#include <stdio.h>
#include <string.h>

#include "hob_setting.h"
#include "hob_utility.h"

static hob_setting_t * hob_setting_common_setup(const char *);
static hob_setting_t * hob_setting_from_long   (const char *, const long);
static hob_setting_t * hob_setting_from_char   (const char *, const char*);
static int             hob_setting_get_key     (const char *, const char *, char *);
static int             hob_setting_check_long  (const char *);

void 
hob_setting_delete(hob_setting_t *self) 
{
    hob_xfree(self);
    return;
}

hob_setting_t *
hob_setting_new(const char *line) 
{
    // Take length checked key=value string; return hob_setting_t *.
    // First check for huge inputs.
    int max_line_length = (HOB_SETTING_BUFFER_SIZE * 2) + 1;
    int oversize = strlen(line) > max_line_length;
    if (oversize) {
        return NULL;
    }
    // Then check for if it doesn't have an equals.
    char *equal_index_ptr = strchr(line, '=');
    if (!equal_index_ptr) {
        return NULL;
    }
    // Get keys
    char key_buffer[HOB_SETTING_BUFFER_SIZE];
    memset(key_buffer, 0, sizeof(key_buffer));
    int bad_key = hob_setting_set_key(line, equal_index_ptr, key_buffer);
    if (bad_key) {
        return NULL;
    }
    // Get values.
    char value_buffer[HOB_SETTING_BUFFER_SIZE];
    memset(value_buffer, 0, sizeof(value_buffer));
    int bad_value = hob_setting_set_value(line, equal_index_ptr, value_buffer);
    if (bad_key || bad_value) {
        return NULL;
    }
    int long_coerce_error = hob_setting_check_long(value_buffer);
    if (long_coerce_error) {
        hob_setting_t *setting = hob_setting_from_char(key_buffer, value_buffer);
        return setting;
    } else {
        long numeric_rep = strtol(value_buffer, NULL, 10);
        hob_setting_t *setting = hob_setting_from_long(key_buffer, numeric_rep);
        return setting;
    }
}

static int 
hob_setting_get_key(const char *line, 
                    const char *equal_index_ptr, 
                    char       *key_buffer) {
    // Extract key from key=value string.
    int key_length    = (int)(equal_index_ptr - line);
    // First do checks.
    int key_empty     = key_length == 0;
    int key_too_large = key_length > HOB_SETTING_BUFFER_SIZE;
    if (key_too_large || key_empty) {
        return 1;
    }
    // Then copy key.
    char *key;
    strncpy(key_buffer, line, key_length);
    return 0;
}

static int 
hob_setting_get_value(const char *line, 
                      const char *equal_index_ptr, 
                      char       *key_buffer) {
    // Extract value from key=value string.
    char *value_string;
    strncpy(value_string, equal_index_ptr + 1, HOB_SETTING_BUFFER_SIZE);
    // First do checks.
    int key_empty     = strlen(value_string) == 0;
    if (key_empty) {
        return 1;
    }
    return 0;

    // Extract key from key=value string.
    int key_length    = (int)(equal_index_ptr - line);
    // First do checks.
    int key_empty     = key_length == 0;
    int key_too_large = key_length > HOB_SETTING_BUFFER_SIZE;
    if (key_too_large || key_empty) {
        return 1;
    }
    // Then copy key.
    char *key;
    strncpy(key_buffer, line, key_length);
    return 0;
}

static int 
hob_setting_check_long(const char *value) {
    // Return 1 if bad long, return 0 if good long. 
    long numeric_rep = 0;
    char post_number_data[HOB_SETTING_BUFFER_SIZE];
    int prev_errno = errno;
    int parse_error = 0;
    errno = 0;
    numeric_rep = strtol(value, NULL, 10);
    int overflow = errno;
    // Check for characters other than whitespce.
    for (int i=0; i<strlen(post_number_data); i++) {
        char *cursor = post_number_data + i;
        if (*cursor == '\0' || *cursor == '\t' || *cursor == ' ') {
            ;
        } else {
            parse_error = 1;
        }
    }
    if (overflow || parse_error) {
        return 1;
    } else {
        return 0;
    }
}

static hob_setting_t *
hob_setting_from_char(const char *key, const char *value) {
    // do char specific setup.
    enum hob_setting_type_desc;
    hob_setting_t *setting = hob_setting_common_setup(key);
    if (setting) {
        strcpy(setting->type, hob_setting_type_desc.CHAR_);
        strcpy(setting->value.char_, value);
        return setting;
    } else {
        return NULL;
    }
}

static hob_setting_t *
hob_setting_from_long(const char *key, const long value) {
    // Do long specific setup.
    hob_setting_t *setting = hob_setting_common_setup(key);
    if (setting) {
        strcpy(setting->type, "long");
        setting->value.long_ = value;
        return setting;
    } else {
        return NULL;
    }
}

static hob_setting_t *
hob_setting_common_setup(const char *key) {
    // Do setup common to long and char nodes.
    hob_setting_t *setting = hob_xmalloc(sizeof(hob_setting_t));
    if (setting) {
        // Zero and set common attributes.
        memset(setting, 0, sizeof(hob_setting_t));
        setting->self = setting;
        setting->next = NULL;
        // Return
        return setting;
    } else {
        return NULL;
    }
}

