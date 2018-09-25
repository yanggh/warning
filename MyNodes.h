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
    static MyNodes* getInstance()
    {
        if(instance == NULL){
            Lock lock;
            if(instance == NULL)
            {
                std::string  mysqlip = "ip";
                std::string  database = "data";
                std::string  username = "username";
                std::string  password = "password";
                std::string  sql = "sql";

                instance = new MyNodes(mysqlip, username, password, database, sql);
            }
        }  
        return instance;
    }

    void   DataHandle(MYSQL_ROW row);
    void   ResetNodes(Node node);
    void   UpdateNodes();

private:
    static MyNodes* instance;
    MyNodes(std::string mysqlip, std::string username, std::string password, std::string database, std::string sql):MyDataSql(mysqlip, username, password, database)
    {
        GetSqlRes(sql);
    }

    std::vector<Node>   vssys;
    int                 _timeout;
};

MyNodes *MyNodes::instance = NULL;

#endif
