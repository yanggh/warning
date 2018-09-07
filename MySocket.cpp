#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <syslog.h>
#include <string.h>
#include <unistd.h>
#include "MySocket.h"

MySocket::MySocket(std::string ip, int port):_ip{ip}, _port{port}
{
    struct sockaddr_in sin;  

    if(((_sockfd = socket(AF_INET, SOCK_DGRAM, 0))< 0))
    {
            syslog(LOG_ERR, "create  socket error");
            return;
    } 

    memset(&sin, 0, sizeof(sin));  
    sin.sin_family=AF_INET;  
    sin.sin_port=htons(port);
    sin.sin_addr.s_addr = htonl(INADDR_ANY);

    if(bind(_sockfd, (struct sockaddr *)&sin, sizeof(struct sockaddr_in)) < 0)
    {
            syslog(LOG_ERR, "bind udp service error, ip = %s, port = %d, error = %s\n", _ip.c_str(), _port, strerror(errno));
            return;
    }
}

MySocket::~MySocket()
{
    if(_sockfd != -1)
    {
        close(_sockfd);
        _sockfd = -1;
    }
}
