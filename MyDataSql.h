#ifndef _MyDataSql_H
#define _MyDataSql_H
#include <mysql.h>
#include <string>
class MyDataSql{
public:
    MyDataSql(std::string mysqlip, std::string username, std::string password, std::string database)
    {
        mysql_init(&mysql);
        mysql_real_connect(&mysql, mysqlip.c_str(), username.c_str(), password.c_str(), database.c_str(), 0, NULL, 0);
    } 

    ~MyDataSql()
    {
        mysql_free_result(my_res);
        mysql_close(&mysql);
    }

    virtual void DataHandle(MYSQL_ROW row) = 0;

    void GetSqlRes(const std::string sql);
private:
    MYSQL     mysql;
    MYSQL_RES *my_res;
    MYSQL_ROW row;
};
#endif
