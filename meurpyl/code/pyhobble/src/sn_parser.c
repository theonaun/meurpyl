#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sn_parser.h>


static const uint16_t  DEFAULT_PORT = 11235;
static const char     *CONFIG_PATH  = {"/etc/pyhobble.conf"};

static void   sn_parser_destroy (sn_parser_t *);
static void   sn_parser_read    (sn_parser_t *);
static void   sn_parser_parse   (sn_parser_t *);

sn_parser_t *
SNParser(void) {
    // Create and self reference
    sn_parser_t *parser = malloc(sizeof(sn_parser_t));
    memset(parser, 0, sizeof(sn_parser_t));
    parser->self = parser;
    // Fill out path and length.
    size_t config_path_size = strlen(CONFIG_PATH) + 1;
    parser->path_size = config_path_size;
    parser->path = malloc(parser->path_size);
    strcpy(parser->path, CONFIG_PATH);
    // Add methods
    parser->destroy = &sn_parser_destroy;
    parser->_read   = &sn_parser_read;
    parser->_parse  = &sn_parser_parse;
    // Read and parse.
    parser->_read(parser->self);
    parser->_parse(parser->self);
   // Check validity.
    if (parser < 0) {
        return NULL;
    }
    else {
        return parser;
    }
}

static void
sn_parser_destroy(sn_parser_t *self) {
    if (self) {
        // Zero everything out and then free.
        memset(self->path, 0, self->path_size);
        memset(self->text, 0, self->text_size);
        memset(self, 0, sizeof(*self));
        free(self->path);
        free(self->text);
        free(self);
        return;
    }
    else {
        return;
    }
}

static void
sn_parser_read(sn_parser_t *self) {
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
sn_parser_parse(sn_parser_t *self) {
    int newline_index[100];
    memset(newline_index, -1, sizeof(newline_index));
    newline_index[0] = 0;
    int line_count = 1;
    int i = 0;
    int text_size = self->text_size;
    for (i=1; i < text_size; i++) {
        if (self->text[i] == '\n') {
            if (line_count > 100) {
                perror("100+ line config file. Probably bad.");
            }
            newline_index[line_count] = i;
            line_count++;
        }
    }
    for (i=0; i<sizeof(newline_index); i++) {
        int start = 0;
        int end = 0;
        // -1 is sentinel.
        if (start == -1) {
            break;
        }
        // First item requires special rules.
        if (i == 0) {
            start = newline_index[0];
            end = newline_index[1] - 1;
        }
        else {
            start = newline_index[i] + 1;
            end = newline_index[i+1] - 1;
            if (end < 0) {
                end = self->text_size - 1;
            }
        }
        size_t length = end - start + 1;
        if (length > 1024) {
            perror("Bad config file.");
        }
        char string_buffer[length + 1];
        memset(string_buffer, '\0', length + 1);
        memcpy(string_buffer, &(self->text[start]), length);
        fprintf(stderr, string_buffer);
    }
    return;
}