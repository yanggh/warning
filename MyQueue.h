#ifndef  _MyQueue_H
#define  _MyQueue_H
#include <queue>
#include <mutex>

class MyQueue{
public:
    MyQueue(){}
    ~MyQueue(){
        mtx.lock();
        while(!qdata.empty())
        {
            qdata.pop();
        }
        mtx.unlock();
    }
    
    void push_data(const std::string ss);
    std::string get_data();

private:
    std::queue<std::string>  qdata;
    std::mutex   mtx;
};
#endif
