#ifndef _MyDataSql_H
#define _MyDataSql_H

#include <mysql.h>
#include <string>
#include <syslog.h>

class MyDataSql{
public:
    MyDataSql(std::string mysqlip, std::string username, std::string password, std::string database)
    {
        mysql_init(&mysql);
        if(!mysql_real_connect(&mysql, mysqlip.c_str(), username.c_str(), password.c_str(), database.c_str(), 0, NULL, 0))
        {
            syslog(LOG_INFO, "mysql_real_connect error, ip is %s, username is %s,  password is %s", mysqlip.c_str(), username.c_str(), password.c_str());
            flag = false;
        }
        else
        {
            flag = true;
        }
    } 

    virtual ~MyDataSql()
    {
        if(flag)
        {
            mysql_free_result(my_res);
        }
        mysql_close(&mysql);
    }

    virtual void  DataHandle(MYSQL_ROW row) = 0;

    void GetSqlRes(const std::string sql);
private:
    MYSQL     mysql;
    MYSQL_RES *my_res;
    MYSQL_ROW row;
    bool      flag;
};
#endif
