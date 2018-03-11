/*****************************************************************************

GENERAL:
    HEADER_NAME:    sn_logger.h
    COMPANION_C:    sn_logger.c
    AUTHOR:         Theo Naunheim <theonaunheim@gmail.com>
    COPYRIGHT:      Theo Naunheim, 2018
    LICENSE:        MIT
    DESCRIPTION:    This file defines the sn_logger_t struct and its
                    associated SNLogger() function. These facilities provide
                    for simplifiedlogging.

CONSTRUCTOR:
    SNLogger:   Builds logger.

ATTRIBUTES:
    self:       Instance reference.
    log_prefix: The log string to which the log message is appended.

METHODS:
    info:       Convenience function logging at info level to syslog. Used
                for general informational purposes.
    warn:       Convenience function logging at warning level to syslog. Used
                for true warnings and certain suspicious activities performed
                by the interpreter.
    destroy:    Cleans up the logger and frees its memory.

*/////////////////////////////////////////////////////////////////////////////


#ifndef SN_LOGGER_H
#define SN_LOGGER_H


#include <stdlib.h>

#include <sys/syslog.h>


typedef struct sn_logger_t {
    // Attributes
    struct sn_logger_t *self;
    char *log_prefix;
    // Methods
    void (*info)(struct sn_logger_t *, char *);
    void (*warn)(struct sn_logger_t *, char *);
    void (*destroy)(struct sn_logger_t *);
} sn_logger_t;

sn_logger_t * SNLogger(void);


#endif