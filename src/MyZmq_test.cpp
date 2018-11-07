#include <thread>
#include <string>
#include "MyZmq.h"
#include "MyQueue.h"
#include "MyConf.h"

using namespace std;

int main(int argc, char**argv)
{
    thread  th1(ConsumerTask);

    th1.join();
}
