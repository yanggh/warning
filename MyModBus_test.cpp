#include <chrono>
#include <thread>
#include <iostream>
#include <unistd.h>
#include "MyModBus.h"

static MyModBus mybus("192.168.43.217", 1502);

void pth2()
{
    int pos = 0;
    int ch = 0;

    while(1)
    {
        std::cout << "input pos, val:" << std::endl;
        std::cin >> pos >> ch;
        if(pos <= 0)
            pos = 1;
        else
            pos = pos - 1;
        if(ch == 1)
        {
                mybus.SetMapVal(pos, 1);
        }
        else
        {
              mybus.SetMapVal(pos, 0);
        }          
    }
}

int main(int argc, char** argv)
{
    std::thread th1(&MyModBus::ModSelect, mybus);
    std::thread th2(pth2);

    th1.join();
    th2.join(); 
    return 0;
}
