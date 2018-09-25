#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "MyUdpSocket.h"
#include "MyQueue.h"
#include "MyDecomp.h"

MyUdpSocket::MyUdpSocket(std::string ip, int port):MySocket(ip, port)
{

}

void  MyUdpSocket::RecvUdp(MyQueue<std::string> *queue)
{
    char         message[1024];
    std::string  data;
    struct       sockaddr_in cin;
    socklen_t    cin_len;
    short        fnum;
    size_t       len = 1024;
    
    int  iLen = recvfrom(_sockfd,  message, len, 0, (struct sockaddr*)&cin, (socklen_t*)&cin_len);
    if(iLen > 0)
    {
       if((message[0] == 0xFF && message[1] == 0x7E) || (message[0] == 0x7E && message[1] == 0xFF))
        {
            fnum = *(short*)(message+2);
            sendto(_sockfd, (uint8_t*)&fnum, 2, 0, (struct sockaddr *)&cin, cin_len);

            data = decomp((uint8_t*)message, iLen);
            queue->push_data(data);
        }
        else if(message[0] == 0xFF)
        {
//              MyNodes::CheckClient(inet_ntoa(cin.sin_addr), ntohs(cin.sin_port));
//              char sstat[256];
//              bzero(sstat, 256);
//              snprintf(sstat, 256, KEEP_ALIVE_STR,  itor->son_sys, itor->stop, itor->ip, itor->port, itor->flag);
//              //TO DO
//              push_data(string(sstat));
        } 
    }
}

std::string  GetData(MyQueue<std::string> *queue)
{
    std::string  ss;
    queue->wait_and_pop(ss);
    return move(ss);
}
