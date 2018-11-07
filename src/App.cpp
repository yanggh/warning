#include <thread>
#include <cstring>
#include <iostream>
#include <vector>
#include "MyNodes.h"
#include "MyQueue.h"
#include "MySocket.h"
#include "MyRecvSnmp.h"
#include "MyUdpDeal.h"

MyQueue<std::string> myqueue;
int  main(int argc, char**argv)
{
    MySnmp    mysnmp;

    MySocket  socket1(argv[1], 9999);

    std::thread  th1(RecvData, std::ref(socket1));
    std::thread  th3(DealData, std::ref(socket1));

    th1.join();
    th3.join();

    
    return 0;
}


