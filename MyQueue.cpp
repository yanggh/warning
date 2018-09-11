#include <iostream>
#include <string>
#include <thread>
#include "MyQueue.h"

void  MyQueue::push_data(const std::string ss)
{
    mtx.lock();
    qdata.push(ss);
    mtx.unlock();
}

std::string MyQueue::get_data()
{
    std::string ss = std::string("error");

    mtx.lock();
    if(!qdata.empty())
    {
        ss = qdata.front();
        std::cout << "size = " << qdata.size() << ",ss = " << ss << std::endl;
        qdata.pop();
    }
    mtx.unlock();

    return ss;
}
