/*****************************************************************************

GENERAL:
    HEADER_NAME:    sn_socket.h
    COMPANION_C:    sn_socket.c
    AUTHOR:         Theo Naunheim <theonaunheim@gmail.com>
    COPYRIGHT:      Theo Naunheim, 2018
    LICENSE:        MIT
    DESCRIPTION:    This file defines the sn_socket_t struct and its
                    associated SNSocket() function. This struct allows for
                    simplified network IPC.

CONSTRUCTOR:
    SNSocket:   Builds the socket.

ATTRIBUTES:
    self:       Instance reference.

METHODS:
    method:     A

*/////////////////////////////////////////////////////////////////////////////


#ifndef SN_SOCKET_H
#define SN_SOCKET_H


#include <netinet/in.h>
#include <sys/socket.h>


typedef struct sn_socket_t {
    // Attributes
    struct sn_socket_t *self;
    int                fd_base;
    int                fd_comm;
    struct sockaddr_in server_address;
    struct sockaddr_in client_address;
    size_t             client_address_size;
    char               buffer[1024];
    // Methods
    void (*destroy)(struct sn_socket_t *);
} sn_socket_t;

sn_socket_t * SNSocket(void);


#endif