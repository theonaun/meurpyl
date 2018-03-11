/*  PyHobble v.3.8.0

    A utility for monitoring the execution of a Python interpreter, checking
    commands as they are run, and limiting specific commands based on
    a list of predefined criteria. It accomplishes these goals by using:

        1. A modified Python interpreter run with user-level permissions that
           sends commands to a local server process and requests permission
           to perform certain operations; and,

        2. A server process run with elevated permissions that writes certain
           commands to log, checks imports for validity, and permits the
           interpreter to perform actions.

 */


#include <stdlib.h>
#include <stdio.h>


#include <sn_logger.h>
#include <sn_parser.h>
#include <sn_socket.h>


int main(int argc, char* argv[]) {
    // Create parser.
    sn_parser_t *parser = SNParser();
    return 1;
    // Create logger.
    sn_logger_t *logger = SNLogger();
    // Create socket
    sn_socket_t *sock = SNSocket();
    // Open SSL

    fprintf(stderr, "HERE!");
    while (1) {
        int read_status = read(
            sock->fd_comm, 
            sock->buffer, 
            sizeof(sock->buffer)
        );
        fprintf(stderr, sock->buffer);
        fprintf(stderr, "%i", read_status);
        if (sock->buffer[0] == 'e') {
            break;
        }
        sleep(1);
    }
    fprintf(stdout, "Fries are done!\n");
    sock->destroy(sock->self);
    return 0;
}
