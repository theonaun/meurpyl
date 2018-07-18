#include <errno.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <hob_parser.h>


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
// TODO: No longer accurate.
hob_parser_destroy(hob_parser_t *self) {
    if (self) {
        // Zero everything out and then free.
        memset(self->path, 0, self->path_size);
        memset(self->text, 0, self->text_size);
        memset(self, 0, sizeof(*self));
        free(self->path);
        free(self->text);
        hob_setting_t *current_node;
        hob_setting_t *next_node;
        current_node = *(self->settings_chain); 
        next_node = current_node->next;
        // Free settings chain.
        while (next_node != NULL) {
            next_node = current_node->next;
            current_node;
        }
        // Final free.
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
            if (line_count > 100) {
                perror("100+ line config file. Probably bad.");
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
        if (length > P_BUFFER_SIZE - 1) {
            perror("Bad config file. Long line.");
        }
        char string_buffer[P_BUFFER_SIZE] = {0};
        memcpy(string_buffer, &(self->text[start]), length);
        self->_map(self, string_buffer);
    }
    return;
}

static void
hob_parser_map(hob_parser_t *self, char *string) {
    hob_setting_t  *node_ptr      = NULL;
    hob_setting_t **node_pptr     = NULL;
    hob_setting_t  *prev_node_ptr = NULL;

    // Point node_pptr at tail node, which is null.
    if (!(self->settings_chain)) {
        node_pptr     = malloc(sizeof(hob_setting_t *));
        node_ptr      = malloc(sizeof(hob_setting_t  ));
        *node_pptr    = node_ptr;
        prev_node_ptr = NULL;
    }
    else {
        node_ptr = *(self->settings_chain);
        while (node_ptr) {
            prev_node_ptr = node_ptr;
            node_ptr = node_ptr->next;
        }
    }

    // Get component strings from "key=value" string
    char *equal_index_ptr = strchr(string, '=');
    if (!equal_index_ptr) {
        return;
    }
    int equal_index = (int)(equal_index_ptr - string);
    string[equal_index] = '\0';
    char key_buffer[P_BUFFER_SIZE];
    char val_buffer[P_BUFFER_SIZE];
    memset(key_buffer, '\0', P_BUFFER_SIZE);
    memset(val_buffer, '\0', P_BUFFER_SIZE);
    strcpy(key_buffer, string);
    strcpy(val_buffer, string + equal_index + 1);

    // Attempt to convert to long.
    long numeric_rep = 0;
    char *string_rep;
    int prev_errno = errno;
    errno = 0;
    numeric_rep = strtol(val_buffer, &string_rep, 10);
    bool overflow = errno;
    bool parse_error = *string_rep != '\0';

    // If not a number, string, otherwise long. 
    if (overflow || parse_error) {
        node_ptr = malloc(sizeof(hob_setting_t));
        prev_node_ptr->next = node_ptr;
        memset(node_ptr, '\0', sizeof(hob_setting_t));
        strcpy(node_ptr->key, key_buffer);
        strcpy(node_ptr->type, "char");
        strcpy(node_ptr->value.char_, string_rep);
        node_ptr->value.long_ = 0;
    } else {
        node_ptr = malloc(sizeof(hob_setting_t));
        prev_node_ptr->next = node_ptr;
        memset(node_ptr, '\0', sizeof(hob_setting_t));
        strcpy(node_ptr->key, key_buffer);
        strcpy(node_ptr->type, "long");
        node_ptr->value.long_ = numeric_rep;
        memset(node_ptr->value.char_, '\0', P_BUFFER_SIZE);
   }
    return;
}