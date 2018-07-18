#include <errno.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <hob_parser.h>
#include <hob_setting.h>


static const uint16_t  DEFAULT_PORT = 11235;
static const char     *CONFIG_PATH  = {"/etc/pyhobble_server/pyhobble_server.conf"};

static void hob_parser_destroy (hob_parser_t *);
static void hob_parser_read    (hob_parser_t *);
static void hob_parser_parse   (hob_parser_t *);
static void hob_parser_map     (hob_parser_t *, char *);
static void hob_parser_get_nl  (hob_parser_t *);


hob_parser_t *
HOBParser(void) {
    // Create and self reference
    hob_parser_t *parser = malloc(sizeof(hob_parser_t));
    memset(parser, 0, sizeof(hob_parser_t));
    parser->self = parser;
    // Fill out path and length.
    size_t config_path_size = strlen(CONFIG_PATH) + 1;
    parser->path_size = config_path_size;
    parser->path = malloc(parser->path_size);
    strcpy(parser->path, CONFIG_PATH);
    // Add methods
    parser->destroy = &hob_parser_destroy;
    parser->_read   = &hob_parser_read;
    parser->_get_nl = &hob_parser_get_nl;
    parser->_parse  = &hob_parser_parse;
    parser->_map    = &hob_parser_map;
    parser->_read  (parser->self);
    parser->_get_nl(parser->self);
    parser->_parse (parser->self);
   // Check validity.
    if (parser < 0) {
        return NULL;
    }
    else {
        return parser;
    }
}

static void 
hob_parser_delete(hob_parser_t *self) {
    if (self) {
        // Zero everything out and then free.
        memset(self->path, 0, self->path_size);
        memset(self->text, 0, self->text_size);
        free(self->path);
        free(self->text);
        hob_setting_t *current_node = self->settings_chain;
        hob_setting_t *next_node    = current_node->next;
        // Free settings chain.
        do {
            next_node = current_node->next;
            current_node->destroy(current_node);
        } while (next_node != NULL);
        // Final free.
        memset(self, 0, sizeof(*self));
        free(self);
        return;
    }
    else {
        return;
    }
}

static void
hob_parser_read(hob_parser_t *self) {
    FILE *config_file;
    config_file = fopen(CONFIG_PATH, "r");
    if (!config_file) {
        self->port = DEFAULT_PORT;
        self->path_size = 0;
        self->text_size = 0;
        self->path      = 0;
        self->text      = 0;
    }
    else {
        fseek(config_file, 0, SEEK_END);
        long file_size = ftell(config_file);
        fseek(config_file, 0, SEEK_SET); 
        self->text = malloc(file_size + 1);
        fread(self->text, 1, file_size, config_file);
        self->text_size = strlen(self->text);
        fclose(config_file);
    }
    return;
}

static void 
hob_parser_get_nl(hob_parser_t *self) {
    memset(self->newline_index, -1, sizeof(self->newline_index));
    self->newline_index[0] = 0;
    int line_count = 1;
    int i = 0;
    int text_size = self->text_size;
    // Get indexes for all newlines.
    for (i=1; i < text_size; i++) {
        if (self->text[i] == '\n') {
            if (line_count > HOB_PARSER_MAX_SETTINGS) {
                perror("Too many lines in config. Probably bad.");
            }
            self->newline_index[line_count] = i;
            line_count++;
        }
    }
    return;
}

static void
hob_parser_parse(hob_parser_t *self) {
   // Go through newline indexes and pull strings.
    int i = 0;
    for (i=0; i<sizeof(self->newline_index); i++) {
        int start = 0;
        int end = 0;
        // First item requires special rules.
        if (i == 0) {
            start = self->newline_index[0];
            end = self->newline_index[1] - 1;
        }
        else {
            start = self->newline_index[i] + 1;
            end = self->newline_index[i+1] - 1;
            if (end < 0) {
                end = self->text_size - 1;
            }
        }
         // -1 is sentinel.
        if (self->newline_index[i] == -1) {
            break;
        }
        // Get size and pull string to buffer.
        size_t length = end - start + 1;
        if (length > HOB_PARSER_BUFFER_SIZE - 1) {
            perror("Bad config file. Long line.");
        }
        char string_buffer[HOB_PARSER_BUFFER_SIZE] = {0};
        memcpy(string_buffer, &(self->text[start]), length);
        self->_map(self, string_buffer);
    }
    return;
}

static void 
hob_parser_map(hob_parser_t *self, char *string) {
    hob_setting_t *setting = HobSetting(string);
    if (!setting) {
        perror("Error creating node.");
    }
    hob_setting_t *cursor_node = self->settings_chain;
    while (cursor_node->next) {
        cursor_node = cursor_node->next;
    }
    // Cursor_node->next is empty node.
    cursor_node->next = setting; 

}