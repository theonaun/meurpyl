/*****************************************************************************

GENERAL:
    HEADER_NAME:    hob_logger.h
    COMPANION_C:    hob_logger.c
    AUTHOR:         Theo Naunheim <theonaunheim@gmail.com>
    COPYRIGHT:      Theo Naunheim, 2018
    LICENSE:        MIT
    DESCRIPTION:    This file defines the hob_logger_t struct and its
                    associated HOBLogger() function. These facilities provide
                    for simplified logging.

CONSTRUCTOR:
    HOBLogger:   Builds logger.

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


#ifndef HOB_LOGGER_H
#define HOB_LOGGER_H


#include <stdlib.h>

#include <sys/syslog.h>


typedef struct hob_logger_t {
    // Attributes
    struct hob_logger_t *self;
    char *log_prefix;
    // Methods
    void (*info)(struct hob_logger_t *, char *);
    void (*warn)(struct hob_logger_t *, char *);
    void (*destroy)(struct hob_logger_t *);
} hob_logger_t;


hob_logger_t * HOBLogger(void);


#endif