#ifndef __CONF__H
#define __CONF__H
#include <string>
#include <iostream>
using namespace std;

const  string conffile =  "/usr/local/warning/etc/database.conf";

class MyConf{
public:
   static MyConf* getInstance()
    {
        return instance;        
    }

    friend ostream &operator<<(ostream &out, const MyConf *myconf)
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


    int get_keepalive();
    int set_keepalive(const int keepalive);
    int comp_keepalive(const int keepalive);
    
    string get_sip();
    int set_sip(const string ip);
    int get_sport();
    int set_sport(const int sport);
    int comp_sport(const int sport);
    
    string get_update_ip();
    int set_update_ip(const string ip);
    int comp_update_ip(const string ip);
    
    int get_update_port();
    int set_update_port(const int update_port);
    int comp_update_port(const int update_port);
    
    string get_web_ip();
    int set_web_ip(const string ip);
    int comp_web_ip(const string ip);
    
    int get_web_port();
    int set_web_port(const int web_port);
    int comp_web_port(const int web_port);
    
    string get_dir();
    int set_dir(const string dir);
    int comp_dir(const string dir);
    
    string get_commit();
    int  set_commit(const string commit);
    int  comp_commit(const string commit);
    
    int  get_trap_port();
    int  set_trap_port(const int trap_port);
    int  comp_trap_port(const int trap_port);
    
    int  set_username(const string username);
    int  set_password(const string password);
    int  set_mysql_ip(const string mysql_ip);
    int  set_database(const string database);
    
    string  get_username();
    string  get_password();
    string  get_mysql_ip();
    string  get_database();
    
    string  get_modbus_major_ip();
    int  set_modbus_major_ip(const string modbus_ip);
    int  get_modbus_major_port();
    int  set_modbus_major_port(const int modbus_port);
    
    string  get_modbus_min_ip();
    int  set_modbus_min_ip(const string modbus_ip);
    int  get_modbus_min_port();
    int  set_modbus_min_port(const int modbus_port);

private:
    static MyConf*  instance;
    MyConf(const string conffile);

    int    _keepalive;
    string  _dir;
    string  _sip;
    int     _sport;
    string  _web_ip;
    int     _web_port;
    string  _update_ip;
    int     _update_port;
    string  _commit;
    int     _trap_port;
    string  _username; 
    string  _password;
    string  _mysql_ip;
    string  _database;
    string  _modbus_major_ip;
    int     _modbus_major_port;
    string  _modbus_min_ip;
    int     _modbus_min_port;
};
#endif
