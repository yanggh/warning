#include "MyConf.h"


int main()
{
    MyConf* myconf = MyConf::getInstance();
    cout << myconf << endl;
    return 0;
}
