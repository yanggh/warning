#ifndef  _MyModBus_H
#define  _MyModBus_H
#include <string>
#include <modbus.h>

class MyModBus{
public:
    MyModBus(const std::string ip, const int port);
    ~MyModBus();
    void  ModSelect();

    void  SetMapVal(int pos, int val);
private:
    uint8_t query[MODBUS_TCP_MAX_ADU_LENGTH];
    int     server_socket;
    modbus_mapping_t *mb_mapping{nullptr};
    modbus_t *ctx{nullptr};
};
#endif
