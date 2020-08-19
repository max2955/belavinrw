#include "network.h"
//#include "configuration.h"

#include <sys/socket.h>
//#include <netinet/in.h>
#include <arpa/inet.h>
#include <fcntl.h>


/*int fill_socket_addr_in(struct sockaddr_in * paddr,int port, char * ip)
{
    memset(paddr, 0, sizeof(struct sockaddr_in));
    paddr->sin_family = AF_INET;
	paddr->sin_port = htons(port);
	if(inet_pton(AF_INET, ip, &paddr->sin_addr)<=0)
    {
	    g_print("\n inet_pton error occured\n");
        return 1;
	}
	//
	return 0;
}*/

int start_listen(int port,int *listen_socket)
{
    //int listenfd = 0;
    struct sockaddr_in serv_addr;

    *listen_socket = socket(AF_INET, SOCK_STREAM, 0);
    memset(&serv_addr, 0, sizeof(serv_addr));

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(port);

    socket_non_block(listen_socket) ;

    bind(*listen_socket, (struct sockaddr*)&serv_addr, sizeof(serv_addr));
    listen(*listen_socket, 10);

    return 0 ;
}


int socket_non_block(int * socket)
{
	int flags = fcntl(* socket, F_GETFL) ;
	return fcntl(*socket, F_SETFL, flags | O_NONBLOCK) ;
}

int connect_to(int port,char *ip,int * connect_socket)
{
	*connect_socket = socket(AF_INET, SOCK_STREAM, 0);
	struct sockaddr_in serv_addr;
	memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(port);

    if(inet_pton(AF_INET, ip, &serv_addr.sin_addr)<=0)
    {
        g_print("\n inet_pton error occured\n");
        return 1;
    }
    if( connect(*connect_socket, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
       g_print("\n Error : Connect Failed \n");
       return 1;
    }
    return 0;
}
