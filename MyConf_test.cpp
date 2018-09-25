#include "MyConf.h"

const  string conffile{"/usr/local/warning/etc/database.conf"};
MyConf* MyConf::instance = new MyConf(conffile);

int main()
{
    MyConf* myconf = MyConf::getInstance();
    cout << myconf << endl;
    return 0;
}
