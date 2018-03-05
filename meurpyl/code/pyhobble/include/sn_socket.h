#ifndef SN_SOCKET_H
#define SN_SOCKET_H


#include <netinet/in.h>
#include <stdbool.h>
#include <sys/socket.h>


typedef struct sn_socket_t {
    struct sn_socket_t *self;
    int                fd;
    int                fd_comm;
    struct sockaddr_in server_address;
    struct sockaddr_in client_address;
    size_t             client_address_size;
    char               buffer[1024];
} sn_socket_t;

sn_socket_t * sn_socket_create(void);

int sn_socket_destroy(sn_socket_t *);


#endif