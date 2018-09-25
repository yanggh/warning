#include <string>
#include "MyUdpSocket.h"

int main(int argc, char** argv)
{
    MyQueue<std::string> queue;
    MyUdpSocket abc("127.0.0.1", 8080);

    abc.RecvUdp(&queue);
}
