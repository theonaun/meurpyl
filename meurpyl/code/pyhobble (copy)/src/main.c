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
#include <unistd.h> // TODO: gives sleep and read.


#include <hob_logger.h>
#include <hob_parser.h>
#include <hob_socket.h>


int main(int argc, char* argv[]) {
    // Create parser.
    // TODO: clobbering settings_chain. 
    hob_parser_t *parser = HOBParser();
    // Create logger.
    hob_logger_t *logger = HOBLogger();
    // Create socket
    hob_socket_t *sock = HOBSocket();
    // Open SSL
    while (1) {
        int read_status = read(
            sock->fd_comm, 
            sock->buffer, 
            sizeof(sock->buffer)
        );
        fprintf(stderr, sock->buffer);
        fprintf(stderr, "%i", read_status);
        fprintf(stderr, "%s", parser->settings_chain->key);
        if (sock->buffer[0] == 'e') {
            break;
        }
        sleep(1);
    }
    fprintf(stdout, "Fries are done!\n");
    sock  ->destroy(sock  ->self);
    logger->destroy(logger->self);
    parser->destroy(parser->self);
    return 0;
}
