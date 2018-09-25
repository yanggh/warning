#ifndef _MyUdpSocket_H
#define _MyUdpSocket_H
#include "MyQueue.h"
#include "MySocket.h"

class MyUdpSocket: public MySocket
{
public:
    MyUdpSocket(std::string ip, int port);
    
    void  RecvUdp(MyQueue<std::string> *queue);
//    virtual void  Handle() = 0;
};
std::string  GetData(MyQueue<std::string> *queue);
#endif
