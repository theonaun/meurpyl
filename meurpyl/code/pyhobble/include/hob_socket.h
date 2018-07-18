/*****************************************************************************

GENERAL:
    HEADER_NAME:    hob_socket.h
    COMPANION_C:    hob_socket.c
    AUTHOR:         Theo Naunheim <theonaunheim@gmail.com>
    COPYRIGHT:      Theo Naunheim, 2018
    LICENSE:        MIT
    DESCRIPTION:    This file defines the hob_socket_t struct and its
                    associated HOBSocket() function. This struct allows for
                    simplified network IPC.

CONSTRUCTOR:
    HOBSocket:   Builds the socket.

ATTRIBUTES:
    self:       Instance reference.

METHODS:
    method:     A

*/////////////////////////////////////////////////////////////////////////////


#ifndef HOB_SOCKET_H
#define HOB_SOCKET_H


#include <netinet/in.h>
#include <sys/socket.h>


typedef struct hob_socket_t {
    // Attributes
    struct hob_socket_t *self;
    int                fd_base;
    int                fd_comm;
    struct sockaddr_in server_address;
    struct sockaddr_in client_address;
    size_t             client_address_size;
    char               buffer[1024];
    // Methods
    void (*destroy)(struct hob_socket_t *);
} hob_socket_t;

hob_socket_t * HOBSocket(void);


#endif