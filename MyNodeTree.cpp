#include <list>
#include <strings.h>
#include <algorithm>
//#include <utility>
//#include <algorithm>
#include "MyNodeTree.h"

static const int  DISCON = 0;
static const int  CONNECT = 1;
static const int  SYSSUB = 0;
static const int  IPSUB = 1;
static const int  PORTSUB = 2;

MyNodeTree::MyNodeTree(std::string mysqlip, std::string database, std::string username, std::string password, std::string sql):MyDataSql(mysqlip, username, password, database){
    mtx.lock();
    if(!vssys.empty())
    {
        vssys.clear();
    }
    mtx.unlock();

    GetSqlRes(sql);
}

void MyNodeTree::DataHandle(MYSQL_ROW row)
{
    uint8_t stop = 1;
    uint8_t ssys = atoi(row[SYSSUB]);
    std::string ip = std::string(row[IPSUB]);
    int     port = atoi(row[PORTSUB]);

    int     flag = CONNECT;
    int     timeout = _timeout;

    Node p(ssys, stop, ip, port, flag, timeout);

    mtx.lock();
    vssys.push_back(p);
    mtx.lock();
}

Node MyNodeTree::FindNode(Node node)
{
    Node dd;
    for(std::vector<Node>::iterator it = vssys.begin(); it != vssys.end(); it++)
    {
        if(*it == node)
        {
            dd = *it;
            break;
        }
    }

    return std::move(dd);
}
