#include <string>
#include "MyQueue.h"
#include "MyNodes.h"

MyQueue<std::string> myqueue;
int main(int argc, char** argv)
{
    MyNodes* mynodes = MyNodes::getInstance();

    mynodes->Show();
    return 0;


}
