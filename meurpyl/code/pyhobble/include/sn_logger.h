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