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
        fclose(config_file);
    }
    return;
}

static void
sn_parser_parse(sn_parser_t *self) {

    return;
}