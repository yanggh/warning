#include <string>
#include <thread>
#include "MyUdpSocket.h"

using namespace std;
int main(int argc, char** argv)
{
    MyQueue<std::string> queue;
    MyQueue<std::string> keeping;
    MyUdpSocket abc("127.0.0.1", 8080);

}
