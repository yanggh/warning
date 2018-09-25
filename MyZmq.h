#ifndef _MY_ZMQ_H
#define _MY_ZMQ_H
#include <string>
#include "MyQueue.h"
int  UpdateSig();
int ConsumerTask(MyQueue<std::string>& myqueue);
#endif
