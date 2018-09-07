#include <string.h>
#include "MyNode.h"

Node::Node(uint8_t ssys, uint8_t stop, std::string ip, int port, int flag, int timeout)
{
    _ssys = ssys;
    _stop = stop;
    _ip = ip;
    _port = port;
    _flag = flag;
    _timeout = timeout;

    memset(&_sin, 0, sizeof(_sin));  
    _sin.sin_family=AF_INET;  
    _sin.sin_addr.s_addr=inet_addr(_ip.c_str());
    _sin.sin_port=htons(_port);
}

std::ostream &operator<<(std::ostream &out, Node node)
{
    out << "node._ssys = " << (int)node._ssys << std::endl;
    out << "node._stop = " << (int)node._stop << std::endl; 
    out << "node._ip = " << node._ip << std::endl;
    out << "node._port = " << node._port << std::endl;
    out << "node._flag = " << node._flag << std::endl;
    out << "node._timeout = " << node._timeout << std::endl;

    return out;
}

bool operator==(Node node1, Node node2)
{
    return (node1._ip == node2._ip);
}

Node& Node::operator=(Node node)
{
    this->_ssys = node._ssys;
    this->_stop = node._stop;
    this->_ip = node._ip;
    this->_port = node._port;
    this->_flag = node._flag;
    this->_timeout = node._timeout;

    memset(&(this->_sin), 0, sizeof(struct sockaddr_in));  
    this->_sin.sin_family=AF_INET;  
    this->_sin.sin_addr.s_addr=inet_addr(node._ip.c_str());
    this->_sin.sin_port=htons(node._port);

    return *this;
}

