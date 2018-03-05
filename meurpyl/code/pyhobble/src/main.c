/*  PyHobble v.3.4.2

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
#include <sn_socket.h>


int main(int argc, char* argv[]) {
    // Create logger.
    sn_logger_t *logger = SNLogger();

    // Open SSL

    sn_socket_t *socket = sn_socket_create();
    fprintf(stderr, "HERE!");
    while (1) {
        int read_status = read(
            socket->fd_comm, 
            socket->buffer, 
            sizeof(socket->buffer)
        );
        fprintf(stderr, socket->buffer);
        fprintf(stderr, "%i", read_status);
        if (socket->buffer[0] == 'e') {
            break;
        }
        sleep(1);
    }
    fprintf(stdout, "Fries are done!\n");
    sn_socket_destroy(socket);
    return 0;
    /* Only superusers should have the ability to run. 
    fprintf(stdout, "Damn!");
    uid_t euid = geteuid();
    if (euid != 0) {
        fprintf(stderr, "Error: insufficient permissions.\n");
        exit(EACCES);
    }
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    // Serialize messages?*/
}
