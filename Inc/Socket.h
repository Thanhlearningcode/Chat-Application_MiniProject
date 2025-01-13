/**************************************************************************************************
 *  Header File: Socket.h
 *  -------------------------------------------------------------------------------------------------------------------
 *  \verbatim
 *  Author: Nguyen Van Thanh
 *  Created on: 1/09/2025
 *  Contact: https://thanhlearningcode.github.io/Myprofile/
 *  Description: This header file contains the declarations for the TCP socket functions that are used
 *  to create, bind, listen, accept, connect, send, receive, and close sockets in a simple server-client
 *  communication.
 *  \endverbatim
 **************************************************************************************************/

#ifndef SOCKET_H_
#define SOCKET_H_

#include <stdint.h>
#include <string.h>  // Để sử dụng strtok, strcmp, strcspn
#include <stdlib.h>  // Để sử dụng atoi, exit
#include <unistd.h>  // Để sử dụng close (trong môi trường Linux)
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>

// Function declarations for socket operations

/**
 * @brief Create a TCP socket
 * 
 * This function creates a socket using the TCP protocol.
 * 
 * @return The socket file descriptor, or -1 if the creation failed.
 */
int TCP_CreateSocket (void);

/**
 * @brief Bind the socket to a specific port
 * 
 * This function binds a socket to a specified port on the server.
 * 
 * @param sock_fd The socket file descriptor.
 * @param port The port number to bind to.
 * @return 0 on success, -1 on failure.
 */
int TCP_BindSocket  (int sock_fd, int port);

/**
 * @brief Start listening for incoming connections
 * 
 * This function puts the server socket in listening mode and waits for incoming connections.
 * 
 * @param sock_fd The socket file descriptor.
 * @return 0 on success, -1 on failure.
 */
int TCP_ListenForConnection (int sock_fd);

/**
 * @brief Accept a new client connection
 * 
 * This function accepts a new connection from a client and provides the client's IP address and port.
 * 
 * @param sock_fd The socket file descriptor.
 * @param port The port number of the connected client.
 * @param client_ip The IP address of the connected client.
 * @return The new socket file descriptor for the client connection, or -1 on failure.
 */
int TCP_AcceptConnection   (int sock_fd, int *port, char *client_ip);

/**
 * @brief Connect to a remote server
 * 
 * This function establishes a connection to a remote server using the provided IP and port.
 * 
 * @param sock_fd The socket file descriptor.
 * @param ip The IP address of the server.
 * @param port The port number of the server.
 * @return 0 on success, -1 on failure.
 */
int TCP_Connect           (int sock_fd, const char *ip, int port);

/**
 * @brief Send a message to a connected client or server
 * 
 * This function sends a message to a connected client or server.
 * 
 * @param sock_fd The socket file descriptor.
 * @param message The message to send.
 * @return The number of bytes sent, or -1 on failure.
 */
int TCP_SendMessage       (int sock_fd, const char *message);

/**
 * @brief Receive a message from a connected client or server
 * 
 * This function receives a message from a connected client or server.
 * 
 * @param sock_fd The socket file descriptor.
 * @param buffer The buffer to store the received message.
 * @param size The size of the buffer.
 * @return The number of bytes received, or -1 on failure.
 */
int TCP_ReceiveMessage    (int sock_fd, char *buffer, uint32_t size);

/**
 * @brief Close the socket connection
 * 
 * This function closes the socket connection.
 * 
 * @param sock_fd The socket file descriptor.
 * @return 0 on success, -1 on failure.
 */
int TCP_CloseConnection   (int sock_fd);

#endif /* SOCKET_H_ */
