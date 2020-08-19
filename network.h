#ifndef BELAVIN_NETWORK
#define BELAVIN_NETWORK


//#include "configuration.h"

//int fill_socket_addr_in(struct sockaddr_in * paddr,int port, char * ip);

int start_listen(int port,int * listen_socket);

int connect_to(int port,char *ip,int * connectfd);

int socket_non_block(int * socket);


#endif // BELAVIN_NETWORK
