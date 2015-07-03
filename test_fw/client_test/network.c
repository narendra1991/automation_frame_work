#include "network.h"
int sent_bytes = 0;
int read_bytes = 0;
int socket_test = 0;
char buf_s[BUFFSIZE];
char buf_r[BUFFSIZE];
int make_socket ( uint16_t port, int type, const char * server_IP )
{
    int sock;
    struct sockaddr_in  server_address;

    /* Create the socket. */
    sock = socket ( PF_INET, SOCK_STREAM, IPPROTO_TCP );
    if (sock < 0) {
        perror ( "socket" );
        exit ( 1 );
    }

    /* Give the socket a name. */
    memset(&server_address, 0, sizeof(server_address));  
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons ( port );

    if ( type == SERVER_SOCKET ) {
        server_address.sin_addr.s_addr = htonl(INADDR_ANY);
        if ( bind ( sock, ( struct sockaddr * ) &server_address, sizeof ( server_address ) ) < 0 ) {
            perror ( "bind" );
            exit ( 1 );
        }

        if ( listen(sock, MAXPENDING) < 0 ) {
            printf("listen() failed");
        }
    } else if ( type == CLIENT_SOCKET ) {
        server_address.sin_addr.s_addr = inet_addr(server_IP);

        /* Establish the connection to the server */
        if (connect(sock, (struct sockaddr *) &server_address, sizeof(server_address)) < 0) {
            printf("connect() failed\n");
        }
    }
    return sock;
}
void close_socket (int socket_test)
{
    close (socket_test);
}
