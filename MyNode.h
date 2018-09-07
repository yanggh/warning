#ifndef _MyNode_H
#define _MyNode_H
#include <string>
#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

typedef unsigned char uint8_t;
class Node
{
public:
    Node(uint8_t ssys = 0, uint8_t stop = 0, std::string ip={}, int port = 0, int flag = 0, int timeout = 10);

    friend bool operator==(Node node1, Node node2);
    friend std::ostream& operator<<(std::ostream &out, Node node);
    Node& operator=(Node node);

private:
    uint8_t  _ssys;
    uint8_t  _stop;
    std::string   _ip;
    int      _port;
    int      _flag;
    int      _timeout;
    struct   sockaddr_in  _sin;
};
#endif
