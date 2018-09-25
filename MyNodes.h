#ifndef _MyNodes_H
#define _MyNodes_H
#include <vector>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <mutex>
#include "MyDataSql.h"
#include "MyNode.h"

using namespace std;
class Lock
{
private:
    std::mutex mtx;
public:
    Lock()
    {
        mtx.lock();
    }

    ~Lock()
    {
        mtx.unlock();
    }
};

class MyNodes: public MyDataSql
{
public:
    static MyNodes* getInstance();
    ~MyNodes();

    void   DataHandle(MYSQL_ROW row);
    void   ResetNodes(Node node);
    void   UpdateNodes();

private:
    static MyNodes* instance;
    MyNodes(string mysqlip, string username, string password, string database, string sql);

    std::vector<Node>   vssys;
    int                 _timeout;
};


#endif
