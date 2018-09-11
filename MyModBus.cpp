#include <syslog.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>
#include <modbus.h>
#include "MyModBus.h"

const int      NB_CONNECTION = 5;
const uint16_t UT_INPUT_REGISTERS_ADDRESS = 0x01;
const uint16_t UT_INPUT_REGISTERS_NB = 100;

MyModBus::MyModBus(const std::string ip, const int port)
{
    ctx = modbus_new_tcp(ip.c_str(), port);
    if(ctx == NULL)
    {
        modbus_free(ctx);
        ctx = NULL;
        return;
    }

    mb_mapping = modbus_mapping_new_start_address( 
            0, 0,
            0, 0,
            0, 0,
            UT_INPUT_REGISTERS_ADDRESS, UT_INPUT_REGISTERS_NB);
    if (mb_mapping == NULL) 
    {
        syslog(LOG_ERR, "Failed to allocate the mapping: %s\n", modbus_strerror(errno));
        return;
    }

    for(int i = 0; i < UT_INPUT_REGISTERS_NB; i++)
    {
        mb_mapping->tab_input_registers[i] = 1;
    }

    modbus_set_slave(ctx, 2);
//    modbus_set_debug(ctx, TRUE);
    modbus_set_debug(ctx, FALSE);
    server_socket = modbus_tcp_listen(ctx, NB_CONNECTION);
    if (server_socket == -1) 
    {
        syslog(LOG_ERR, "Unable to listen TCP connection\n");
        modbus_free(ctx);
        ctx = NULL;
        return;
    }
}

MyModBus::~MyModBus()
{
    if (server_socket != -1) 
    {
        close(server_socket);
        server_socket = -1;
    }

    if(ctx != NULL)
    {
        modbus_free(ctx);
        ctx = NULL;
    }

    if(mb_mapping != NULL)
    {
        modbus_mapping_free(mb_mapping);
    }
}

void  MyModBus::ModSelect()
{
    fd_set refset;
    fd_set rdset;
    int    rc = -1;
    int    fdmax = -1;
    int    master_socket = -1;

        /* Clear the reference set of socket */
    FD_ZERO(&refset);
    /* Add the server socket */
    FD_SET(server_socket, &refset);

    /* Keep track of the max file descriptor */
    fdmax = server_socket;
    for (;;) 
    {
        rdset = refset;
        if (select(fdmax+1, &rdset, NULL, NULL, NULL) == -1) 
        {
            syslog(LOG_ERR, "Server select() failure.");
            return;
        }

        /* Run through the existing connections looking for data to be read */
        for (master_socket = 0; master_socket <= fdmax; master_socket++) 
        {
            if (!FD_ISSET(master_socket, &rdset)) 
            {
                continue;
            }

            if (master_socket == server_socket) 
            {
                /* A client is asking a new connection */
                socklen_t addrlen;
                struct sockaddr_in clientaddr;
                int newfd;

                /* Handle new connections */
                addrlen = sizeof(clientaddr);
                memset(&clientaddr, 0, sizeof(clientaddr));
                newfd = accept(server_socket, (struct sockaddr *)&clientaddr, &addrlen);
                if (newfd == -1) 
                {
                    syslog(LOG_ERR, "Server accept() error");
                }
                else 
                {
                    FD_SET(newfd, &refset);

                    if (newfd > fdmax) 
                    {
                        /* Keep track of the maximum */
                        fdmax = newfd;
                    }
                }
            } 
            else 
            {
                modbus_set_socket(ctx, master_socket);
                rc = modbus_receive(ctx, query);

                if (rc > 0) 
                {
                    while(mb_mapping == NULL)
                    {
                        syslog(LOG_INFO, "mb_mapping is NULL!\n");
                        sleep(1);
                    }

                    modbus_reply(ctx, query, rc, mb_mapping);
                }
                else if (rc == -1) 
                {
                    /* This example server in ended on connection closing or
                     * any errors. */
                    syslog(LOG_INFO, "(Connection closed on socket %d", master_socket);
                    close(master_socket);

                    /* Remove from reference set */
                    FD_CLR(master_socket, &refset);

                    if (master_socket == fdmax) 
                    {
                        fdmax--;
                    }
                }
            }
        }
    }

}

void  MyModBus::SetMapVal(int pos, int val)
{
    if(val > 0)
    mb_mapping->tab_input_registers[pos] = 1;
    else 
    mb_mapping->tab_input_registers[pos] = 0;
}
