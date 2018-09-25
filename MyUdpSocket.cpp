#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <string>
#include <vector>
#include <mutex>
#include <thread>
#include "MyUdpSocket.h"
#include "MyQueue.h"
#include "MyDecomp.h"


using namespace std;

MyUdpSocket::MyUdpSocket(std::string ip, int port):MySocket(ip, port)
{

}

void  MyUdpSocket::RecvUdp(MyQueue<std::string>& queue, MyQueue<std::string>& keeping)
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
            queue.push_data(data);
        }
        else if(message[0] == 0xFF)
        {
            data.assign(message, iLen);
            keeping.push_data(data);
        } 
    }
}

std::string  GetData(MyQueue<std::string>& queue)
{
    std::string  ss;
    queue.wait_and_pop(ss);
    return move(ss);
}
