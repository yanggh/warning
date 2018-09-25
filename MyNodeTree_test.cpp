#include "MyNodes.h"

int main(int argc, char** argv)
{
    MyNodes  mynodetree("ip", "database", "username", "password", "sql");

    Node  node(0, 0, "ip", 1234);


    Node  node1 = mynodetree.FindNode(node);
    return 0;
}
