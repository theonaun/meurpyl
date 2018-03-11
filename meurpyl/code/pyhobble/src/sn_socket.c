#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <sys/socket.h>

#include "sn_socket.h"


#include <stdio.h>


static void sn_socket_destroy(sn_socket_t *);

sn_socket_t *
SNSocket(void) {
    sn_socket_t *sock = malloc(sizeof(sn_socket_t));
    memset(sock, 0, sizeof(sn_socket_t));
    sock->self = sock;
    // Get socket.
    sock->fd_base = socket(AF_INET, SOCK_STREAM, 0);
    // Set socket optionss
    setsockopt(
        sock->fd_base,
        SOL_SOCKET,
        SO_REUSEADDR,
        &(sock->server_address),
        sizeof(sock->server_address)
    );
    // Set addr
    sock->server_address.sin_family = AF_INET;
    sock->server_address.sin_addr.s_addr = htonl(INADDR_ANY);
    sock->server_address.sin_port = htons(11235);
    sock->client_address_size = sizeof(sock->client_address);
    // Socket
    int bind_status = bind(
        sock->fd_comm, 
        (struct sockaddr *) &(sock->server_address), 
        sizeof (sock->server_address)
    );
    int listen_status = listen(sock->fd_comm, 2);
    sock->fd_comm = accept(
        sock->fd_base, 
        (struct sockaddr *) &(sock->client_address),
        &(sock->client_address_size)
    );
    // Add methods
    sock->destroy = &sn_socket_destroy;
    // Check validity.
    if (sock < 0) {
        return NULL;
    }
    else {
        return sock;
    }
}

static void
sn_socket_destroy(sn_socket_t *socket) {
    if (socket) {
        close(socket->fd_base);
        close(socket->fd_comm);
        memset(socket, 0, sizeof(*socket));
        free(socket);
        return 0;
    }
    else {
        return -1;
    }
}


