#include <thread>
#include "MyIscs.h" 

int main(int argc, char** argv)
{
    MyIscs  myiscs("127.0.0.1", "mysql", "root", "password", "sql1", "sql2");

    std::thread  th1(&MyIscs::Iscs_Work, myiscs, "127.0.0.1", 8080, "12", 8080);
    //std::thread  th2(&MyModBus::ModSelect, modbus1);
    //std::thread  th3(&MyModBus::ModSelect, modbus2);

    th1.join();
    //th2.join();
    //th3.join();
    return 0;
}
