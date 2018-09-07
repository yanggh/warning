#ifndef _MyIscs_H
#define _MyIscs_H

#include "MyDataSql.h"

class MyIscs: public MyDataSql
{
public:
    MyIscs(std::string mysqlip, std::string database, std::string username, std::string password, std::string sql1, std::string sql2);
private:
    void  Iscs_Work();
    void  DataHandle(MYSQL_ROW row);

    int _sub;
    std::string _sql1;
    std::string _sql2;
};

#endif
