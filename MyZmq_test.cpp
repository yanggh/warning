#include <thread>
#include <string>
#include "MyZmq.h"
#include "MyQueue.h"
#include "MyConf.h"

using namespace std;

const  string conffile{"/usr/local/warning/etc/database.conf"};
MyConf* MyConf::instance = new MyConf(conffile);

int main(int argc, char**argv)
{
    MyQueue<std::string> myqueue;

    thread  th1(ConsumerTask, ref(myqueue));
    thread  th2(UpdateSig);

    th1.join();
    th2.join();
}
