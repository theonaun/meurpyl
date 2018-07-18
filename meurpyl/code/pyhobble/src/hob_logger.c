#include <stdlib.h>
#include <string.h>
#include <syslog.h>

#include "hob_logger.h"


static const char     *LOG_PREFIX = {"[pyhobble]: "};

static void hob_logger_info   (hob_logger_t *, char *);
static void hob_logger_warn   (hob_logger_t *, char *);
static void hob_logger_destroy(hob_logger_t *);

hob_logger_t *
HOBLogger(void) {
    hob_logger_t *logger = malloc(sizeof(hob_logger_t));
    memset(logger, 0, sizeof(hob_logger_t));
    logger->self = logger; 
    logger->log_prefix = malloc((strlen(LOG_PREFIX)) + 1);
    strcpy(logger->log_prefix, LOG_PREFIX);
    logger->info = &hob_logger_info;
    logger->warn = &hob_logger_warn;
    logger->destroy = &hob_logger_destroy;
    if (logger < 0) {
        return NULL;
    }
    else {
        return logger;
    }
}

static void 
hob_logger_info(hob_logger_t *self, char *message) {
    int len = strlen(self->log_prefix);
    int buffer_size = strlen(self->log_prefix) + strlen(message) + 1;
    char buffer[buffer_size];
    strcat(buffer, self->log_prefix);
    strcat(buffer, message);
    openlog("pyhobble", (LOG_CONS | LOG_PID), LOG_USER);
    syslog(LOG_INFO, buffer);
    closelog();
    return;
}

static void
hob_logger_warn(hob_logger_t *self, char *message) {
    int len = strlen(self->log_prefix);
    int buffer_size = strlen(self->log_prefix) + strlen(message) + 1;
    char buffer[buffer_size];
    strcat(buffer, self->log_prefix);
    strcat(buffer, message);
    openlog("pyhobble", (LOG_CONS | LOG_PID), LOG_USER);
    syslog(LOG_WARNING, buffer);
    closelog();
    return;
}

static void
hob_logger_destroy(hob_logger_t *self) {
    memset(self->log_prefix, 0, strlen(self->log_prefix));
    free(self->log_prefix);
    memset(self, 0, sizeof(self));
    free(self);
    return;
}