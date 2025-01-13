/**************************************************************************************************
 *  Author: Nguyen Van Thanh
 *  Created on: 1/09/2025
 *  Contact: https://thanhlearningcode.github.io/Myprofile/
 *  Description: This header file contains declarations for functions that manage server-client
 *  communication, including socket creation, connection handling, message sending/receiving,
 *  and connection listing/removal.
 **************************************************************************************************/

#ifndef COMMUNICATION_H_
#define COMMUNICATION_H_

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include "Socket.h"
#define MAX_CLIENTS 10
#define BUFFER_SIZE 1024

// Struct to manage client connections
typedef struct {
    uint32_t client_id;
    int sock_fd;
    int in_port;
    char *in_addr;
} connect_manager_t;

// Function declarations for server-client communication
int Create_ServerSocket(int port);
int Create_ClientSocket(const char *ip, int port);
void Accept_NewConnection(int listen_fd);
void Client_Handler(void);
void Send_ToClient(char *message, uint32_t client_id);
void Remove_Client(uint32_t client_id);
void Remove_AllClients(void);
void List_AllConnections(void);
void Get_MyIp(int sock_fd);


#endif /* COMMUNICATION_H_ */
