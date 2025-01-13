/**************************************************************************************************
 *  Author: Nguyen Van Thanh
 *  Created on: 1/13/2025
 *  Contact: https://thanhlearningcode.github.io/Myprofile/
 *  Description: This file contains implementations of TCP socket functions such as creating, binding,
 *  listening, accepting, connecting, sending, receiving, and closing connections.
 **************************************************************************************************/

#include "Socket.h"


/**************************************************************************************************
 *  Tạo socket TCP
 **************************************************************************************************/
int TCP_CreateSocket(void) {
    int sock_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (sock_fd < 0) {
        perror("Error creating socket");
        return -1;
    }
    return sock_fd;
}

/**************************************************************************************************
 *  Bind socket TCP với một cổng
 **************************************************************************************************/
int TCP_BindSocket(int sock_fd, int port) {
    struct sockaddr_in server_addr;
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    if (bind(sock_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("Error binding socket");
        return -1;
    }
    return 0;
}

/**************************************************************************************************
 *  Lắng nghe kết nối đến từ client
 **************************************************************************************************/
int TCP_ListenForConnection(int sock_fd) {
    if (listen(sock_fd, 1) < 0) {
        perror("Error listening on socket");
        return -1;
    }
    return 0;
}

/**************************************************************************************************
 *  Chấp nhận kết nối từ client
 **************************************************************************************************/
int TCP_AcceptConnection(int sock_fd, int *port, char *client_ip) {
    struct sockaddr_in client_addr;
    socklen_t client_len = sizeof(client_addr);
    int client_sockfd = accept(sock_fd, (struct sockaddr *)&client_addr, &client_len);
    if (client_sockfd < 0) {
        perror("Error accepting connection");
        return -1;
    }

    if (inet_ntop(AF_INET, &client_addr.sin_addr, client_ip, INET_ADDRSTRLEN) == NULL) {
        perror("Error converting client IP");
        close(client_sockfd);
        return -1;
    }
    *port = ntohs(client_addr.sin_port);
    return client_sockfd;
}

/**************************************************************************************************
 *  Kết nối đến server qua TCP
 **************************************************************************************************/
int TCP_Connect(int sock_fd, const char *ip, int port) {
    struct sockaddr_in server_addr;
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    if (inet_pton(AF_INET, ip, &server_addr.sin_addr) <= 0) {
        perror("Invalid address");
        return -1;
    }

    if (connect(sock_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("Connection failed");
        return -1;
    }
    return 0;
}

/**************************************************************************************************
 *  Gửi một tin nhắn qua socket
 **************************************************************************************************/
int TCP_SendMessage(int sock_fd, const char *message) {
    if (send(sock_fd, message, strlen(message), 0) < 0) {
        perror("Error sending message");
        return -1;
    }
    return 0;
}

/**************************************************************************************************
 *  Nhận một tin nhắn từ client qua socket
 **************************************************************************************************/
int TCP_ReceiveMessage(int sock_fd, char *buffer, uint32_t size) {
    ssize_t bytes_received = recv(sock_fd, buffer, size, 0);
    if (bytes_received < 0) {
        perror("Error receiving message");
        return -1;
    }
    buffer[bytes_received] = '\0'; // Null terminate the string
    return bytes_received;
}

/**************************************************************************************************
 *  Đóng kết nối TCP
 **************************************************************************************************/
int TCP_CloseConnection(int sock_fd) {
    if (close(sock_fd) < 0) {
        perror("Error closing connection");
        return -1;
    }
    return 0;
}
