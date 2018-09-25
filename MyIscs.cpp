#include <unistd.h>
#include <thread>
#include "MyIscs.h"
#include "MyModBus.h"

static MyModBus  modbus("127.0.0.1", 1024);

MyIscs::MyIscs(std::string mysqlip, std::string database, std::string username, std::string password, std::string sql1, std::string sql2):MyDataSql(mysqlip, username, password, database)
{
    _sub = 0;
    _sql1 = sql1;
    _sql2 = sql2;
}

void MyIscs::DataHandle(MYSQL_ROW row)
{
    int val = atoi(row[1]) > 0 ? 1 : 0;
    modbus.SetMapVal(_sub, val);
    _sub++;
}

void  MyIscs::Iscs_Work()
{
    while(1)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds (5));
        GetSqlRes(_sql1);
        GetSqlRes(_sql2);
        _sub = 0;
    }
}
