#ifndef _MyNodes_H
#define _MyNodes_H
#include <vector>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <mutex>
#include "MyDataSql.h"
#include "MyConf.h"
#include "MyNode.h"

const string MYSQL_ISCS_STR = "SELECT subsys_.SUBSYSTEM_CODE, IFNULL(sub_.QTY,0) qty FROM TBL_RESMANAGE_SUBSYSTEMINFO subsys_ LEFT JOIN (SELECT b.SUBSYSTEM_CODE,COUNT(*) QTY FROM TBL_ALARM_ALARMINFO a LEFT JOIN TBL_RESMANAGE_SUBSYSTEMINFO b ON a.SUBSYSTEMID=b.SUBSYSTEMID WHERE a.ALARM_STATE=0 AND a.FAULTID!=\"\" AND a.FAULTUNITID!=\"\" AND a.SUBSYSTEMID!=\"\" AND a.STATIONID!=\"\"  GROUP BY a.SUBSYSTEMID  LIMIT  8) sub_ ON subsys_.SUBSYSTEM_CODE=sub_.SUBSYSTEM_CODE LIMIT 9;";

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
                MyConf* myconf = MyConf::getInstance();
                std::string  mysqlip = myconf->get_mysql_ip();
                std::string  username = myconf->get_username();
                std::string  password = myconf->get_password();
                std::string  database = myconf->get_database();
    
                instance = new MyNodes(MYSQL_ISCS_STR);
            }
        }
        return instance;
    }

    ~MyNodes();

    void   DataHandle(MYSQL_ROW row);
    void   ResetNodes(const std::string& ip, const uint16_t& port);

    void   HeartBeat(const string& ip, const uint16_t& port);
    void   UpdateNodes(int sockfd);

    void   Show();
private:
    static MyNodes* instance;
    std::vector<Node>   nms;
    MyNodes(std::string sql);

    int                 _timeout;
};

//ostream &operator<<(ostream &out, MyNodes* mynodes);

#endif
