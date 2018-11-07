#include <thread>
#include <cstring>
#include <iostream>
#include <vector>
#include "MySocket.h"
#include "MyNodes.h"
#include "MyQueue.h"
#include "MyRecvSnmp.h"
#include "MyUdpDeal.h"
const char* WAR_JSON_STR = "{ type: \"%d\", fnum: \"%d\", flen: \"%d\", son_sys: \"%d\", stop: \"%d\", eng: \"%d\", node:\"%d\", bug: \"%d\", time: \"%02d%02d-%02d-%02d %02d:%02d:%02d\", res1: \"%d\", res2: \"%d\", res3: \"%d\", check: \"%d\"}";

using namespace std;

extern  MyQueue<std::string> myqueue;

void RecvData(MySocket& socket)
{
    int    nRecvBuf=1024;
    char   message[nRecvBuf];

    struct sockaddr_in sin;
    int    sin_len = sizeof(sin);

    std::string data;
    int   sockfd = socket.get_sockfd();
    int   len = 0;

    while(1)
    {
        memset(message, 0, nRecvBuf);
        len = recvfrom(sockfd, message, nRecvBuf, 0, (struct sockaddr*)&sin, (socklen_t*)&sin_len);
        if(len > 0)
        {
            data.assign(message, len);
            socket.push_data(sin, data);
        }
    }
}

std::string  WDeComp(const std::string data, std::string& result)
{
    size_t  pos = 0;

    uint16_t  type;
    uint16_t  fnum;
    uint8_t   flen;
    uint8_t   son_sys;
    uint8_t   stop;
    uint8_t   eng;
    uint8_t   node;
    uint16_t  bug;
    uint8_t   tt[7];

    uint16_t  res1;
    uint16_t  res2;
    uint16_t  res3;
    uint16_t  check;

    memcpy(&type, data.data() + pos, 2);
    pos += 2;

    memcpy(&fnum, data.data() + pos, 2);
    pos += 2;

    memcpy(&flen, data.data() + pos, 1);
    pos += 1;

    memcpy(&son_sys, data.data() + pos, 1);
    pos += 1;

    memcpy(&stop, data.data() + pos, 1);
    pos += 1;

    /**********start*****************/
    memcpy(&eng, data.data() + pos, 1);
    pos += 1;

    memcpy(&node, data.data() + pos, 1);
    pos += 1;

    memcpy(&bug, data.data() + pos, 2);
    pos += 2;
    
    //**********end*****************//

    memcpy(tt, data.data() + pos, 7);
    pos += 7;

    memcpy(&res1, data.data() + pos, 2);
    pos += 2;

    memcpy(&res2, data.data() + pos, 2);
    pos += 2;

    memcpy(&res3, data.data() + pos, 2);
    pos += 2;

    memcpy(&check, data.data() + pos, 2);
    pos += 2;

    char  output[1024];
    memset(output, 0, 1024);
    if(snprintf(output, 1024, WAR_JSON_STR, ntohs(type), ntohs(fnum), flen, son_sys, stop, eng,  node,  ntohs(bug),  tt[0],  tt[1], tt[2], tt[3], tt[4], tt[5], tt[6], ntohs(res1), ntohs(res2), ntohs(res3), ntohs(check)) > 0)
    {
        result = output;
    }

    return result;
}

std::string  DDeComp(const std::string data, std::string& result)
{
    size_t  pos = 0;

    uint16_t  type;
    uint16_t  fnum;
    uint8_t   flen;
    uint8_t   son_sys;
    uint8_t   stop;

    uint8_t   eng;
    uint8_t   node;
    uint16_t  bug_type;

    uint8_t   tt[7];

    uint16_t  res1;
    uint16_t  res2;
    uint16_t  res3;
    uint16_t  check;


    memcpy(&type, data.data() + pos, 2);
    pos += 2;

    memcpy(&fnum, data.data() + pos, 2);
    pos += 2;

    memcpy(&flen, data.data() + pos, 1);
    pos += 1;

    memcpy(&son_sys, data.data() + pos, 1);
    pos += 1;

    memcpy(&stop, data.data() + pos, 1);
    pos += 1;

    /**********start*****************/
    memcpy(&eng, data.data() + pos, 1);
    pos += 1;

    memcpy(&node, data.data() + pos, 1);
    pos += 1;

    memcpy(&bug_type, data.data() + pos, 2);
    pos += 2;

    //**********end*****************//
    memcpy(tt, data.data() + pos, 7);
    pos += 7;

    memcpy(&res1, data.data() + pos, 2);
    pos += 2;

    memcpy(&res2, data.data() + pos, 2);
    pos += 2;

    memcpy(&res3, data.data() + pos, 2);
    pos += 2;

    memcpy(&check, data.data() + pos, 2);
    pos += 2;

    char      output[1024];
    memset(output, 0, 1024);
    if(snprintf(output, 1024, WAR_JSON_STR, ntohs(type), ntohs(fnum), flen, son_sys, stop, eng,  node,  ntohs(bug_type),  tt[0],  tt[1], tt[2], tt[3], tt[4], tt[5], tt[6], ntohs(res1), ntohs(res2), ntohs(res3), ntohs(check)) > 0)
    {
        result = output;
    }

    return result;
}

bool DealData(MySocket& socket)
{
    std::string data;
    std::string sdata;
    struct sockaddr_in sin;

    int      sockfd = socket.get_sockfd();

    std::string ip;
    std::string result;
    uint16_t    port;

    MyNodes* mynodes = MyNodes::getInstance();

    while(1)
    {
        result = "invalid";
        if(socket.get_data(sin, data))
        {
            if(((data[0] & 0xff) == 0xFF) && ((data[1] & 0xFF) == 0x7E))
            {
                std::cout << "告警数据/告警恢复:" << std::endl;
                sdata.assign(data, 0, 4);
                sendto(sockfd, sdata.data(), sdata.size(), 0, (struct sockaddr *)&sin, sizeof(sin));

                WDeComp(data, result);
            }
            else if((data[0] & 0xff) == 0xFF && (data[1] & 0xFF) == 0x4E)
            {
                std::cout << "采集数据:" << std::endl;         
                sdata.assign(data, 0, 4);
                sendto(sockfd, sdata.data(), sdata.size(), 0, (struct sockaddr *)&sin, sizeof(sin));

                DDeComp(data, result);
            }

            //TODO
            if(result != "invalid")
            {
                ip = inet_ntoa(sin.sin_addr);
                port = ntohs(sin.sin_port);
                myqueue.push_data(result);
                cout << "ip = " << ip << ", port = " << port << "myqueue.size() = " << myqueue.size()<< endl;
            }

            //心跳数据
            {
                mynodes->HeartBeat(ip, port);
            }
        }
        else
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }
    }
    return true;
}

