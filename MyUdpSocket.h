#ifndef _MyUdpSocket_H
#define _MyUdpSocket_H
#include "MyQueue.h"
#include "MySocket.h"

class MyUdpSocket: public MySocket
{
public:
    MyUdpSocket(std::string ip, int port);
    
    void          RecvUdp();
    virtual void  Handle() = 0;
private:
    MyQueue queue;
};
#endif
