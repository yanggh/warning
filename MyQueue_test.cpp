#include <thread>
#include <iostream>

#include "MyQueue.h"

static MyQueue myqueue;
void pth1()
{
    while(1)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds (1));    
        myqueue.push_data("aaaa");
    }
}

void pth2()
{
    std::string  ss;
    while(1)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds (1));    
        ss = myqueue.get_data();
        std::cout << "ss = " << ss << std::endl;
    }
}


int main(int argc, char**argv)
{
    std::thread th1(pth1);
    std::thread th2(pth2);
   
    th1.join();
    th2.join();

    return 0; 
}
