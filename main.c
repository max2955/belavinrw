#include <stdlib.h>
#include <stdio.h>
#include <glib.h>
#include <sys/stat.h>
#include <glib/gstdio.h>
#include <unistd.h>

#include "netpdu.h"


int init_system()
{
	//comment
 //   g_thread_init(NULL);uuyytttt
	//
    return 0;
}

int main(int argc,char * argv[])
{

	if (argc<2)
	{
		g_print("number of arguments less than 3\n");
		exit(-1);
	}

	char mode_option = argv[1][0];
	char filename[1024];

	if (mode_option=='w' || mode_option=='r')
	{
		if (argc<2)
		{
			g_print("read and write require file name\n");
			exit(-1);
		}
	}


	g_print("mode_option=%c\n",mode_option);

    switch(mode_option)
    {
    case 's':
    	break;
    case 'r':
    	break;
    case 'w':
    	break;
    }


	gchar * data = g_strnfill(512, 'b') ;
	data[511]='c' ;
	guint8 pdubuf[1024] ;
	guint32 pdubuflen = 0;
    guint8 pduholder[1024] ;


	int n ;
	int connect_socket = 0  ;
	connect_to(8081, "127.0.0.1", &connect_socket) ;



	g_print("Send read\n") ;
    netpdu_read_t * rpdu = new_netpdu_read(pduholder,511,257) ;
    netpdu_to_buf((gpointer)rpdu, (gpointer)pdubuf,&pdubuflen) ;
	write(connect_socket,pdubuf,pdubuflen) ;
	n = read(connect_socket,pdubuf,1024) ;
	g_print("RECV: %s\n",dump_netpdu(pdubuf,n)) ;


	g_print("Send write\n") ;
	netpdu_write_t * wpdu = new_netpdu_write(pduholder,511,(guint8*)data,257) ;
    netpdu_to_buf((gpointer)wpdu, (gpointer)pdubuf,&pdubuflen) ;
	write(connect_socket,pdubuf,pdubuflen) ;
	n = read(connect_socket,pdubuf,1024) ;
	g_print("Recv: %s\n",dump_netpdu(pdubuf,n)) ;


	g_print("Send getsize\n") ;
	netpdu_getsize_t * gspdu = new_netpdu_getsize(pduholder,257) ;
    netpdu_to_buf((gpointer)gspdu, (gpointer)pdubuf,&pdubuflen) ;
	write(connect_socket,pdubuf,pdubuflen) ;
	n = read(connect_socket,pdubuf,1024) ;
	g_print("Recv: %s\n",dump_netpdu(pdubuf,n)) ;

	close(connect_socket) ;

    return 0;
}
