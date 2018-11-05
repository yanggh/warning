#include "MyDataSql.h"

void MyDataSql::GetSqlRes(const std::string sql)
{
    if(flag)
    {
        int ret =mysql_real_query(&mysql, sql.c_str(), sql.length());
        if(ret == 0)
        {
           my_res = mysql_store_result(&mysql);//返回查询的全部结果集
           while((row = mysql_fetch_row(my_res)) > 0)
           {
               DataHandle(row);
           }
        }
        else
        {
            syslog(LOG_ERR, "mysql_real_query error, sql is %s", sql.c_str());
        }
    }
    else
    {
        syslog(LOG_ERR, "flag is false\n");
    }
}
