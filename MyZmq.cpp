#include <zmq.hpp>
#include <syslog.h>
#include <list>
#include "MyZmq.h"
#include "MyConf.h"
#include "MyUdpSocket.h"


using namespace std;

int  UpdateSig()
{
    MyConf* myconf = MyConf::getInstance();
    
    char   constr[256] = {0};
    int  port = myconf->get_update_port();
    snprintf(constr, 256, "tcp://*:%d", port);

    zmq::context_t context (1);
    zmq::socket_t  socket(context, ZMQ_REP);
	socket.bind(constr);
 
    while (true) 
    {
        // 等待客户端请求
        zmq::message_t request;
        socket.recv (&request);
 
        if(memcmp(request.data(), "update", 6) == 0)
        {
            //TODO
            //int  ret = init_client();
            //if(ret == -1)
            //{
            //    syslog(LOG_INFO, "update error.");
            //    continue;
            //}
        }
        else
        {
            syslog(LOG_ERR, "error: request.size() = %ld.", request.size());
        }

        // 应答World
        zmq::message_t reply (5);
        memcpy ((void *) reply.data (), "World", 5);
        socket.send (reply);
    }

    return 0;
}

int ConsumerTask(MyQueue<std::string>& myqueue)
{
    MyConf* myconf = MyConf::getInstance();

    string ip = myconf->get_web_ip();
    int  port = myconf->get_web_port();

    zmq::context_t context (1);
    zmq::socket_t  socket (context, ZMQ_REQ);

    char   constr[256] = {0};
    snprintf(constr, 256, "tcp://%s:%d", ip.data(), port);
    syslog(LOG_INFO, "constr ============ %s\n", constr);
    socket.connect (constr);
    
    std::string data;
    while(1)
    {
        data = GetData(myqueue);
        
        zmq::message_t req(strlen(data.c_str()));
        memset((void*)req.data(), 0, strlen(data.c_str()));
        memcpy((void*)req.data(), data.c_str(), strlen(data.c_str()));
        syslog(LOG_INFO, "req.data is %sa\n", data.c_str());
        if(socket.send(req) < 0)
        {
            syslog(LOG_ERR, "zmq send error!\n");
        }

        zmq::message_t reply;
        if(socket.recv (&reply) < 0)
        {
            syslog(LOG_ERR, "zmq recv error!\n");
        }
        syslog(LOG_INFO, "udp reply.data is %s\n", (char*)reply.data());
    }

    return 0;
}
