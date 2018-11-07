#include <thread>
#include <thread>
#include "MyConf.h"
#include "MyIscs.h" 

static  const std::string  iscs_1 = "SELECT subsys_.SUBSYSTEM_CODE, IFNULL(sub_.QTY,0) qty FROM TBL_RESMANAGE_SUBSYSTEMINFO subsys_ LEFT JOIN (SELECT b.SUBSYSTEM_CODE,COUNT(*) QTY FROM TBL_ALARM_ALARMINFO a LEFT JOIN TBL_RESMANAGE_SUBSYSTEMINFO b ON a.SUBSYSTEMID=b.SUBSYSTEMID WHERE a.ALARM_STATE=0 AND a.FAULTID!=\"\" AND a.FAULTUNITID!=\"\" AND a.SUBSYSTEMID!=\"\" AND a.STATIONID!=\"\"  GROUP BY a.SUBSYSTEMID  LIMIT  8) sub_ ON subsys_.SUBSYSTEM_CODE=sub_.SUBSYSTEM_CODE LIMIT 9;";
static const  std::string  iscs_2  =  "SELECT        station.STATION_NAME,   IFNULL(q.QTY,0) qty  FROM TBL_RESMANAGE_STATIONINFO station LEFT JOIN(SELECT IFNULL(count(*),0) QTY,alarm.STATIONID FROM TBL_ALARM_ALARMINFO  alarm, TBL_RESMANAGE_FAULTINFO  fault ,TBL_RESMANAGE_SUBSYSTEMINFO system  WHERE alarm.FAULTID=fault.FAULTID AND fault.FAULT_CODE=4226 AND alarm.SUBSYSTEMID=system.SUBSYSTEMID AND system.SUBSYSTEM_CODE=8 AND alarm.ALARM_STATE!=2 GROUP BY  STATIONID) q ON station.STATIONID=q.STATIONID WHERE STATION_ORDER_NO <> 97 AND STATION_ORDER_NO <> 98 AND STATION_ORDER_NO <> 99 ORDER BY station.STATION_ORDER_NO asc  LIMIT 34";

int main(int argc, char** argv)
{
    MyConf* myconf = MyConf::getInstance();

    std::string  major_ip = myconf->get_modbus_major_ip();
    std::string  min_ip = myconf->get_modbus_min_ip();
    
    int  major_port = myconf->get_modbus_major_port();
    int  min_port =   myconf->get_modbus_min_port();

    MyIscs  myiscs("sql1", "sql2");

    std::thread  th1(&MyIscs::Iscs_Work, myiscs, major_ip, major_port, min_ip, min_port);

    th1.join();
    return 0;
}
