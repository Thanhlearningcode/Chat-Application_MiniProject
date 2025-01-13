/**************************************************************************************************
 *  Header File: Socket.h
 *  -------------------------------------------------------------------------------------------------------------------
 *  Author: Nguyen Van Thanh
 *  Created on: 1/09/2025
 *  Contact: https://thanhlearningcode.github.io/Myprofile/
 *  Description: This header file contains declarations for functions that manage server-client
 *               communication, including socket creation, connection handling, message sending/receiving,
 *               and connection listing/removal.
 **************************************************************************************************/

#ifndef COMMUNICATION_H_
#define COMMUNICATION_H_

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include "Socket.h"

#define MAX_CLIENTS 10 /**< Maximum number of clients the server can handle */
#define BUFFER_SIZE 1024 /**< Size of the buffer used for message handling */

/**
 * @brief Structure to manage client connections.
 * 
 * This structure is used to store information about each client connected
 * to the server, including client ID, socket file descriptor, port number,
 * and IP address.
 */
typedef struct {
    uint32_t client_id; /**< Unique identifier for the client */
    int sock_fd; /**< Socket file descriptor for the client connection */
    int in_port; /**< Port number the client is connected to */
    char *in_addr; /**< IP address of the client */
} connect_manager_t;

/**
 * @brief Creates a server socket bound to a specific port.
 * 
 * This function creates a socket for the server to listen for incoming client
 * connections on the given port.
 * 
 * @param[in] port Port number to bind the server socket.
 * @return Socket file descriptor for the server, or -1 on failure.
 */
int Create_ServerSocket(int port);

/**
 * @brief Creates a client socket for connecting to a server.
 * 
 * This function creates a socket that the client can use to connect to a server
 * at the specified IP address and port.
 * 
 * @param[in] ip IP address of the server to connect to.
 * @param[in] port Port number of the server to connect to.
 * @return Socket file descriptor for the client, or -1 on failure.
 */
int Create_ClientSocket(const char *ip, int port);

/**
 * @brief Accepts a new client connection on the server.
 * 
 * This function accepts an incoming connection request from a client and
 * adds the client to the server's connection list.
 * 
 * @param[in] listen_fd Socket file descriptor for listening to incoming connections.
 */
void Accept_NewConnection(int listen_fd);

/**
 * @brief Handles communication with a connected client.
 * 
 * This function is responsible for receiving and processing messages from
 * a connected client and sending responses back if necessary.
 */
void Client_Handler(void);

/**
 * @brief Sends a message to a specific client.
 * 
 * This function sends a message to the client identified by the given client_id.
 * 
 * @param[in] message Message to send to the client.
 * @param[in] client_id Unique identifier of the client to send the message to.
 */
void Send_ToClient(char *message, uint32_t client_id);

/**
 * @brief Removes a client from the server's connection list.
 * 
 * This function removes the client identified by the given client_id from
 * the list of active connections.
 * 
 * @param[in] client_id Unique identifier of the client to be removed.
 */
void Remove_Client(uint32_t client_id);

/**
 * @brief Removes all clients from the server's connection list.
 * 
 * This function removes all clients from the list of active connections,
 * effectively disconnecting all clients.
 */
void Remove_AllClients(void);

/**
 * @brief Lists all active client connections.
 * 
 * This function outputs information about all the clients currently connected
 * to the server, including client IDs, socket file descriptors, and IP addresses.
 */
void List_AllConnections(void);

/**
 * @brief Retrieves the IP address of the server.
 * 
 * This function retrieves and returns the IP address of the server associated
 * with the given socket file descriptor.
 * 
 * @param[in] sock_fd Socket file descriptor for which to retrieve the server's IP.
 */
void Get_MyIp(int sock_fd);

#endif /* COMMUNICATION_H_ */
