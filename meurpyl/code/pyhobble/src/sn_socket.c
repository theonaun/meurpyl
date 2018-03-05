#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <sys/socket.h>

#include "sn_socket.h"


#include <stdio.h>


sn_socket_t *
sn_socket_create(void) {
    sn_socket_t *s = malloc(sizeof(sn_socket_t));
    s->self = s;
    // Get socket.
    s->fd = socket(AF_INET, SOCK_STREAM, 0);
    // Set socket optionss
    setsockopt(
        s->fd,
        SOL_SOCKET,
        SO_REUSEADDR,
        &(s->server_address),
        sizeof(s->server_address)
    );
    // Set addr
    s->server_address.sin_family = AF_INET;
    s->server_address.sin_addr.s_addr = htonl(INADDR_ANY);
    s->server_address.sin_port = htons(11235);
    s->client_address_size = sizeof(s->client_address);
    // Socket
    int bind_status = bind(
        s->fd, 
        (struct sockaddr *) &(s->server_address), 
        sizeof (s->server_address)
    );
    int listen_status = listen(s->fd, 2);
    s->fd_comm = accept(
        s->fd, 
        (struct sockaddr *) &(s->client_address),
        &(s->client_address_size)
    );
    return s;
}


int
sn_socket_destroy(sn_socket_t *s) {
    if (s) {
        close(s->fd);
        close(s->fd_comm);
        memset(s, 0, sizeof(*s));
        free(s);
        return 0;
    }
    else {
        return -1;
    }
}


