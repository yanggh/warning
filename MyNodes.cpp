#include <list>
#include <strings.h>
#include <algorithm>
#include "MyNodes.h"

static const int  DISCON = 0;
static const int  CONNECT = 1;
static const int  SYSSUB = 0;
static const int  IPSUB = 1;
static const int  PORTSUB = 2;

MyNodes* MyNodes::getInstance()
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

MyNodes::~MyNodes()
{
    if(instance != NULL)
        delete instance;
}

MyNodes::MyNodes(std::string mysqlip, std::string username, std::string password, std::string database, std::string sql):MyDataSql(mysqlip, username, password, database)
{
    GetSqlRes(sql);
}

void MyNodes::DataHandle(MYSQL_ROW row)
{
    uint8_t stop = 1;
    uint8_t ssys = atoi(row[SYSSUB]);
    std::string ip = std::string(row[IPSUB]);
    int     port = atoi(row[PORTSUB]);

    int     flag = CONNECT;
    int     timeout = _timeout;

    Node p(ssys, stop, ip, port, flag, timeout);

    vssys.push_back(p);
}

void MyNodes::UpdateNodes()
{
    for(std::vector<Node>::iterator it = vssys.begin(); it != vssys.end(); it++)
    {
        it->SubNode();
    }
}

void MyNodes::ResetNodes(Node node)
{
    for(std::vector<Node>::iterator it = vssys.begin(); it != vssys.end(); it++)
    {
        if(*it == node)
        {
            it->ResetNode(_timeout); 
            break;
        }
    }
}
