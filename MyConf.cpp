#include <iostream>
#include <thread>
#include <unistd.h>
#include <string.h>
#include <syslog.h>
#include "MyConf.h"

#define  KEEPALIVE  "keepalive"
#define  LOGDIR     "log-dir"
#define  INNERIP    "inner-ip"
#define  UPDATEPORT "update-port"
#define  WEBPORT    "web-port"
#define  USERNAME   "username"
#define  PASSWORD   "password"
#define  DATABASE   "database"
#define  SOUTHIPM    "south-major-ip"
#define  SOUTHPORTM  "south-major-port"
#define  SOUTHIP    "south-min-ip"
#define  SOUTHPORT  "south-min-port"
#define  NORTHIP    "north-ip"
#define  NORTHPORT  "north-port"

ostream &operator<<(ostream &out, const MyConf *myconf)
{
    out <<  "keepalive = " << myconf->_keepalive << endl; 
    out <<  "dir = " << myconf->_dir << endl;
    out <<  "sip = " << myconf->_sip << endl;     
    out <<  "sport = " << myconf->_sport << endl;     
    out <<  "web_ip = " << myconf->_web_ip << endl;     
    out <<  "web_port = " << myconf->_web_port << endl;   
    out <<  "update_ip = " << myconf->_update_ip << endl;
    out <<  "update_port = " << myconf->_update_port << endl;
    out <<  "commit = " << myconf->_commit << endl;
    out <<  "trap_port = " << myconf->_trap_port << endl;  
    out <<  "username = " << myconf->_username << endl;
    out <<  "password = " << myconf->_password << endl;
    out <<  "mysql_ip = " << myconf->_mysql_ip << endl;
    out <<  "database = " << myconf->_database << endl;
    out <<  "modbus_major_ip = " << myconf->_modbus_major_ip << endl;
    out <<  "modbus_major_port = " << myconf->_modbus_major_port << endl;
    out <<  "modbus_min_ip = " << myconf->_modbus_min_ip << endl;
    out <<  "modbus_min_port = " << myconf->_modbus_min_port << endl;
    return out;
}

int MyConf::get_keepalive()
{
    return _keepalive;
}

int MyConf::set_keepalive(const int keepalive)
{
    _keepalive = keepalive;
    return _keepalive;
}

int MyConf::comp_keepalive(const int keepalive)
{
    return (_keepalive == keepalive ? 0 : -1);
}

string MyConf::get_sip()
{
    return _sip;
}

int MyConf::set_sip(const string ip)
{
    _sip = ip;
    return 0;
}

int MyConf::get_sport()
{
    return _sport;
}

int MyConf::set_sport(const int sport)
{
    _sport = sport;
    return 0;
}

int MyConf::comp_sport(const int sport)
{
    return (_sport == sport ? 0 : -1);
}

string MyConf::get_update_ip()
{
    return _update_ip;
}

int MyConf::set_update_ip(const string ip)
{
    _update_ip = ip;
    return 0;
}

int MyConf::comp_update_ip(const string ip)
{
    return  (_update_ip == ip ? 0 : -1);
}

int MyConf::get_update_port()
{
    return _update_port;
}

int MyConf::set_update_port(const int update_port)
{
    _update_port = update_port;
    return 0;
}

int MyConf::comp_update_port(const int update_port)
{
    return (_update_port == update_port ? 0 : -1);
}

string MyConf::get_web_ip()
{
    return _web_ip;
}

int MyConf::set_web_ip(const string ip)
{
    _web_ip = ip;
    return 0;
}

int MyConf::comp_web_ip(const string ip)
{
    return (ip == _web_ip ? 0 : -1);
}

int MyConf::get_web_port()
{
    return _web_port;
}

int MyConf::set_web_port(const int web_port)
{
    _web_port = web_port;
    return 0;
}

int MyConf::comp_web_port(const int web_port)
{
    return (_web_port == web_port ? 0 : -1);
}

string MyConf::get_dir()
{
    return _dir;
}

int MyConf::set_dir(const string dir)
{
    _dir = dir;
    return 0;
}

int MyConf::comp_dir(const string dir)
{
    return (_dir == dir ? 0 : -1);
}

string  MyConf::get_commit()
{
    return _commit;
}

int MyConf::set_commit(const string commit)
{
    _commit = commit;
    return 0;
}

int MyConf::comp_commit(const string commit)
{
    return (_commit == commit ? 0 : -1);
}

int  MyConf::get_trap_port()
{
    return _trap_port;
}

int MyConf::set_trap_port(const int trap_port)
{
    _trap_port = trap_port;
    return 0;
}

int MyConf::comp_trap_port(const int trap_port)
{
    return (_trap_port == trap_port ? 0 : -1);
}

string  MyConf::get_username()
{
    return _username;
}

int  MyConf::set_username(const string username)
{
    _username = username;
    return 0;
}

string  MyConf::get_password()
{
    return _password;
}

int  MyConf::set_password(const string password)
{
    _password = password;
    return 0;
}

string MyConf::get_mysql_ip()
{
    return _mysql_ip;
}

int  MyConf::set_mysql_ip(const string mysql_ip)
{
    _mysql_ip = mysql_ip;
    return 0;
}

string  MyConf::get_database()
{
    return _database;
}

int  MyConf::set_database(const string database)
{
    _database = database;
    return 0;
}
/*****************************************/
string MyConf::get_modbus_major_ip()
{
    return _modbus_major_ip;
}

int  MyConf::set_modbus_major_ip(const string modbus_ip)
{
    _modbus_major_ip = modbus_ip;
    return 0;
}

int  MyConf::get_modbus_major_port()
{
    return _modbus_major_port;
}

int  MyConf::set_modbus_major_port(const int modbus_port)
{
    _modbus_major_port = modbus_port;
    return 0;
}

/**************************************/
string MyConf::get_modbus_min_ip()
{
    return _modbus_min_ip;
}

int  MyConf::set_modbus_min_ip(const string modbus_ip)
{
    _modbus_min_ip = modbus_ip;
    return 0;
}

int  MyConf::get_modbus_min_port()
{
    return _modbus_min_port;
}

int  MyConf::set_modbus_min_port(const int modbus_port)
{
    _modbus_min_port = modbus_port;
    return 0;
}

MyConf::MyConf(const string conffile)
{
    char  buf1[256];
    char  buf2[256];
    char  buff[256];

    FILE  *fp = fopen(conffile.c_str(),  "r");

    while(fgets(buff, 256, fp) != NULL)
    {
        bzero(buf1, 256);
        bzero(buf2, 256);
        sscanf(buff, "%s %s", buf1, buf2);

        if(memcmp(buf1, KEEPALIVE, strlen(KEEPALIVE)) == 0)
        {
            set_keepalive(atoi(buf2));        
        }
        else if(memcmp(buf1, LOGDIR, strlen(LOGDIR)) == 0)
        {
            set_dir(string(buf2)); 
        }
        else if(memcmp(buf1, NORTHIP, strlen(NORTHIP)) == 0)
        {
            set_sip(string(buf2)); 
        }
        else if(memcmp(buf1, NORTHPORT, strlen(NORTHPORT)) == 0)
        {
            set_sport(atoi(buf2)); 
        }
        else if(memcmp(buf1, INNERIP, strlen(INNERIP)) == 0)
        {
            set_update_ip(string(buf2)); 
            set_mysql_ip(string(buf2));
            set_web_ip(string(buf2)); 
        }
        else if(memcmp(buf1, UPDATEPORT, strlen(UPDATEPORT)) == 0)
        {
            set_update_port(atoi(buf2));
        }
        else if(memcmp(buf1, WEBPORT, strlen(WEBPORT)) == 0)
        {
            set_web_port(atoi(buf2));
        }
        else if(memcmp(buf1, USERNAME, strlen(USERNAME)) == 0)
        {
            set_username(string(buf2));        
        }
        else if(memcmp(buf1, PASSWORD, strlen(PASSWORD)) == 0)
        {
            set_password(string(buf2)); 
        }
        else if(memcmp(buf1, DATABASE, strlen(DATABASE)) == 0)
        {
            set_database(string(buf2));
        }
        else if(memcmp(buf1, SOUTHIPM, strlen(SOUTHIPM)) == 0)
        {
            set_modbus_major_ip(string(buf2));
        }
        else if(memcmp(buf1, SOUTHPORTM, strlen(SOUTHPORTM)) == 0)
        {
            set_modbus_major_port(atoi(buf2));
        }
        else if(memcmp(buf1, SOUTHIP, strlen(SOUTHIP)) == 0)
        {
            set_modbus_min_ip(string(buf2));
        }
        else if(memcmp(buf1, SOUTHPORT, strlen(SOUTHPORT)) == 0)
        {
            set_modbus_min_port(atoi(buf2));
        }
        else
        {
            syslog(LOG_INFO, "buf1 find %s, buf2 find %s", buf1, buf2);
        }

        bzero(buff, 256);  
    } 
    fclose(fp);
    fp = NULL;
}

