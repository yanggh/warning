#ifndef _MyNodeTree_H
#define _MyNodeTree_H
#include <vector>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <mutex>
#include "MyDataSql.h"
#include "MyNode.h"

class MyNodeTree: public MyDataSql
{
public:
    MyNodeTree(std::string mysqlip, std::string database, std::string username, std::string password, std::string sql);

    void   DataHandle(MYSQL_ROW row);
    Node   FindNode(Node node);

private:
    std::vector<Node>    vssys;
    std::vector<Node>::iterator  it;
    std::mutex            mtx;
    int                   _timeout;
};
#endif
