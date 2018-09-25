#include "MyNodes.h"

MyNodes *MyNodes::instance = NULL;
int main(int argc, char** argv)
{
    MyNodes* mynodes = MyNodes::getInstance();

    mynodes->UpdateNodes();
    return 0;


}
