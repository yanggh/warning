#include <thread>
#include "Zmq.h"
#include "Queue.h"

#ifdef __UDPDEAL_
#include "UdpDeal.h"
#endif

#ifdef __SNMPDEAL_
#include "RecvSnmp.h"
#endif

#ifdef __ISCS__
#include "Iscs.h"
#endif

#include "Song.h"
using namespace std;

#define MAXFILE 65535
void dameno()
{
    pid_t pid;
    int i;
    pid = fork();     //创建一个进程用来做守护进程
    if(pid<0)
    {
        syslog(LOG_ERR, "dameno error fork \n");
        exit(1);
    }
    else if(pid>0)
    {
        exit(0);    //结束父进程
    }

    setsid();       //使子进程独立1.摆脱原会话控制 2.摆脱原进程组的控制 3.摆脱控制中端的控制
    chdir("/");     //改变当前工作目录，这也是为了摆脱父进程的影响
    umask(0);      //重设文件权限掩码
    for(i=0;i<MAXFILE;i++)
    {
        close(i);
    }
}

int main(int argc, char**argv)
{
    dameno();
#ifdef __SNMPDEAL_
    MySnmp    mysnmp;
#endif

    //给界面推送zmq处理
    thread  th1(ConsumerTask);

#ifdef __UDPDEAL_
    //Udp接收处理
    thread  th2(UdpDeal);
#endif

#ifdef __ISCS__
    //综合监控程勋
    thread  th3(ModBus_Deal);
#endif
    thread  th4(Song);

    th1.join();
#ifdef __UDPDEAL_
    th2.join();
#endif

#ifdef __ISCS__
    th3.join();
#endif
    
    th4.join();
    return 0;
}
