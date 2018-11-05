#include "CallBack.h"
#include <string>
#include <fstream>
#include <map>
using namespace std;

const  string  SSYS     = "1.3.6.1.4.1.3902.4101.1.3.1.12";
const  string  ATIME    = "1.3.6.1.4.1.3902.4101.1.3.1.3";
const  string  ACODE    = "1.3.6.1.4.1.3902.4101.1.3.1.11";
const  string  BUS      = "1.3.6.1.4.1.3902.4101.1.3.1.26";
const  string  SLOT     = "1.3.6.1.4.1.3902.4101.1.3.1.15";
const  string  WARNING  = "1.3.6.1.4.1.3902.4101.4.2.1.1";
const  string  HEART    = "1.3.6.1.4.1.3902.4101.4.1.2";
const  string  RECOVER1 = "1.3.6.1.4.1.3902.4101.1.4.1.2";
const  string  RECOVER2 = "1.3.6.1.4.1.3902.4101.1.4.1.3";
const  string  ZXIP     = "1.3.6.1.4.1.3902.4101.1.3.1.17";

const  string  IPBUS    = "/usr/local/warning/etc/ip_addr";
const  string  ZXCODE   = "/usr/local/warning/etc/zxcode";

const  string  SNMP_JSON_STR  = "{ type: \"65406\", fnum: \"0\", flen: \"26\", son_sys: \"%d\", stop: \"%d\", eng: \"%s\", node:\"%s\", bug: \"%d\", time: \"%s\", res1: \"0\", res2: \"0\", res3: \"0\", check: \"0\"}";

int map_zx_code(map<long,  int>& codemap)
{
    int   id = 0;
    long  code = 0;
    char  buff[256];

    ifstream infile(ZXCODE, ios::in);
    
    while(infile.good())
    {
        infile.getline(buff,256);
        sscanf(buff, "%ld, %d", &code, &id);
        codemap.insert(pair<long, int>(code, id));
    }

    infile.close();
    return 0;
}

int  map_ip_bus(map<string, int>& ipmap) 
{
    int   id = 0;
    char  ip[256];
    char  buff[256];

    ifstream infile(IPBUS, ios::in);
    while(infile.good())
    {
        infile.getline(buff,256);
        bzero(ip, 256);
        sscanf(buff, "%s, %d", ip, &id);
        ipmap.insert(pair<string, int>(ip, id));
    }

    infile.close();
    return 0;
}

void TrapCallBack( int reason, Snmp *snmp, Pdu &pdu, SnmpTarget &target, void *cd)
{
    Vb nextVb;
    int pdu_error;

    GenAddress addr;
    target.get_address(addr);
    UdpAddress from(addr);

    if (pdu.get_type() == sNMP_PDU_INFORM) 
    {
        nextVb.set_value("This is the response.");
        pdu.set_vb(nextVb, 0);
        snmp->response(pdu, target);
    }
}
