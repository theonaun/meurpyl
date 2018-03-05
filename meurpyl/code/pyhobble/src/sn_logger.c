#include <stdlib.h>
#include <string.h>
#include <syslog.h>

#include "sn_logger.h"


static void sn_logger_info   (sn_logger_t *, char *);
static void sn_logger_warn   (sn_logger_t *, char *);
static void sn_logger_destroy(sn_logger_t *);

sn_logger_t *
SNLogger(void) {
    sn_logger_t *logger = malloc(sizeof(sn_logger_t));
    memset(logger, 0, sizeof(sn_logger_t));
    logger->self = logger; 
    char *temp_str = "[PySnitch]: ";
    char *new = malloc(strlen(temp_str) * sizeof(char));
    logger->log_prefix = malloc((strlen(temp_str) * sizeof(char)) + 1);
    strcpy(logger->log_prefix, temp_str);
    logger->info = &sn_logger_info;
    logger->warn = &sn_logger_warn;
    logger->destroy = &sn_logger_destroy;
    if (logger < 0) {
        return NULL;
    }
    else {
        return logger;
    }
}

static void 
sn_logger_info(sn_logger_t *self, char *message) {
    int len = strlen(self->log_prefix);
    int buffer_size = strlen(self->log_prefix) + strlen(message) + 1;
    char buffer[buffer_size];
    strcat(buffer, self->log_prefix);
    strcat(buffer, message);
    openlog("pysnitch", (LOG_CONS | LOG_PID), LOG_USER);
    syslog(LOG_INFO, buffer);
    closelog();
    return;
}

static void
sn_logger_warn(sn_logger_t *self, char *message) {
    int len = strlen(self->log_prefix);
    int buffer_size = strlen(self->log_prefix) + strlen(message) + 1;
    char buffer[buffer_size];
    strcat(buffer, self->log_prefix);
    strcat(buffer, message);
    openlog("pysnitch", (LOG_CONS | LOG_PID), LOG_USER);
    syslog(LOG_WARNING, buffer);
    closelog();
    return;
}

static void
sn_logger_destroy(sn_logger_t *self) {
    memset(self->log_prefix, 0, strlen(self->log_prefix));
    free(self->log_prefix);
    memset(self, 0, sizeof(self));
    free(self);
    return;
}