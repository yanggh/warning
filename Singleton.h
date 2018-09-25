#include <mutex>

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

class Singleton {
public:
    static Singleton* getInstance();
    //析构的时候释放资源~
    ~Singleton() {
        if(_instance != NULL)
            delete _instance;
    }
protected:
    Singleton();
private:
    static Singleton* _instance;
};

