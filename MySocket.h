#ifndef _MySocket_H
#define _MySocket_H
#include <string>

class MySocket{
public:
    MySocket(std::string ip, int port);
    ~MySocket();

protected:
    int            _sockfd{-1};
private:
    std::string    _ip;
    int            _port;
  
};
#endif
