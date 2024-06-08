#ifndef __NETWORK__H
#define __NETWORK__H

#include <stdio.h>
#include <stdlib.h>	// exit
#include <sys/types.h>
#include <sys/socket.h>
//#include <linux/in.h>	// struct sockaddr_in	Problems with header files(头文件的问题)
#include <netinet/in.h>		// htons inet_aton
#include <arpa/inet.h>		// htons inet_aton
#include <string.h>	// memset
#include <unistd.h>

#define IPADDR "192.168.1.253"
#define PORT "4713"

int net_init(const char *ipaddr, const char *port);


#endif