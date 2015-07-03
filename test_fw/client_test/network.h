#include <netinet/in.h>
#include <netdb.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h> /* memset */
#include <unistd.h> /* close */

#define MAXPENDING            5
#define BUFFSIZE              1447
#define SERVER_SOCKET         1
#define CLIENT_SOCKET         0

#define TRUE                  1
#define FALSE                 0
#define START                 11
#define NUM_TESTS             275
int make_socket ( uint16_t port, int type, const char * server_IP );
void close_socket (int socket_test);
