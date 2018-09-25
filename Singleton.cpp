#include "Singleton.h"

Singleton *Singleton::_instance = NULL;

Singleton* Singleton::getInstance() {
    //check 之前进行临界区加锁操作
    //双重检验加锁
    if(_instance == NULL ) {
        Lock lock;
        if( _instance == NULL) {
            _instance = new Singleton();
        }
    }
    return _instance;
}
