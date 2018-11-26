#include <string>
#include <fstream>
#include <map>
#include <syslog.h>
#include "Queue.h"
#include "Nodes.h"
#include "TrapCallBack.h"
#include "hwzx.h"
using namespace std;
using namespace Snmp_pp;

const  string  SNMP_JSON_STR  = "{ type: \"65406\", fnum: \"0\", flen: \"26\", son_sys: \"%d\", stop: \"%d\", eng: \"%s\", node:\"%s\", bug: \"%d\", time: \"%s\", res1: \"0\", res2: \"0\", res3: \"0\", check: \"0\"}";

extern MyQueue<std::string> myqueue;

void   TrapCallBack(int reason, Snmp_pp::Snmp *snmp, Snmp_pp::Pdu &pdu, Snmp_pp::SnmpTarget &target, void *cd)
{
    MyNodes* mynodes = MyNodes::getInstance();

    GenAddress addr;
    target.get_address(addr);
//    UdpAddress from(addr);

    char  heartip[1024];
    bzero(heartip, 1024);
    sscanf(addr.get_printable(), "%[^/]s%*s", heartip);
    printf("heartip = %s\n" ,addr.get_printable());//(char*)addr);
    //获取子系统连接状态
    mynodes->HeartBeat("127.0.0.1", 162);

    int pdu_error;
    pdu_error = pdu.get_error_status();
    if(pdu_error)
    {
        syslog(LOG_INFO, "Response contains error: %s\n",  snmp->error_msg(pdu_error));
        return;
    }

    int    son_sys = 1;
    int    bus = 1;
    string jk = "12";
    string cw = "112";
    int    code = 4099;
    string atime = "asdfasdfasdf";

    //中兴设备
    if(zxGetData(pdu, son_sys, bus, jk, cw, code, atime))
    {

    }
    //华为设备
    else if(hwGetData(pdu, son_sys, bus, jk, cw, code, atime))
    {

    }       

        
    char output[1024];
    memset(output, 0, 1024);
    snprintf(output, 1024, SNMP_JSON_STR.c_str(), son_sys, bus, jk.c_str(), cw.c_str(), code, atime.c_str());
    //TODO ENQUEUE
    myqueue.push_data(output);

    if (pdu.get_type() == sNMP_PDU_INFORM) 
    {
        Vb nextVb;
        nextVb.set_value("This is the response.");
        pdu.set_vb(nextVb, 0);
        snmp->response(pdu, target);
    }
}
