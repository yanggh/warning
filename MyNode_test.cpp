#include "MyNode.h"

int main()
{
    Node a;
    Node b(10, 20, "192.168.1.11", 10, 0, 200);

    std::cout << a;
    std::cout << "----------------------" << std::endl;
    std::cout << b;
}
