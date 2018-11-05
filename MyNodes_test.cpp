#include <string>
#include "MyNodes.h"

int main(int argc, char** argv)
{
    MyNodes* mynodes = MyNodes::getInstance();

    std::cout << mynodes << std::endl;
    return 0;


}
