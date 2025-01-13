/**************************************************************************************************
 *  Author: Nguyen Van Thanh
 *  Created on: 1/09/2025
 *  Contact: https://thanhlearningcode.github.io/Myprofile/
 *  Description: This code contains functions for managing a simple server-client communication,
 *  including functions for creating sockets, accepting and handling connections, sending and 
 *  receiving messages, and listing or removing connections.
 **************************************************************************************************/

#include "Communication.h"

static uint32_t id_counter = 1;
connect_manager_t *clients_p[MAX_CLIENTS] = { NULL };  // Khởi tạo tất cả các phần tử bằng NULL
/**************************************************************************************************
 *  Tạo socket cho server và lắng nghe kết nối
 **************************************************************************************************/
int Create_ServerSocket(int port) {
    int sock_fd = TCP_CreateSocket();

    if (sock_fd < 0) {
        perror("Không thể tạo socket");
        return -1;
    }

    if (TCP_BindSocket(sock_fd, port) < 0) {
        perror("Không thể bind socket");
        return -1;
    }

    if (TCP_ListenForConnection(sock_fd) < 0) {
        perror("Không thể lắng nghe kết nối");
        return -1;
    }

    printf("Đang lắng nghe trên cổng: %d\n", port);
   
    return sock_fd;
}

/**************************************************************************************************
 *  Thêm client vào danh sách các kết nối
 **************************************************************************************************/
static void Add_Client(connect_manager_t new_client) {
    uint8_t added = 0;

    // Tìm slot trống trong mảng clients_p
    for (int i = 0; i < MAX_CLIENTS; i++) {
        if (clients_p[i] == NULL) {
            clients_p[i] = malloc(sizeof(connect_manager_t));
            if (clients_p[i] == NULL) {
                perror("Lỗi cấp phát bộ nhớ");
                return;
            }
            clients_p[i]->client_id = new_client.client_id;
            clients_p[i]->sock_fd = new_client.sock_fd;
            clients_p[i]->in_port = new_client.in_port;
            clients_p[i]->in_addr = new_client.in_addr;
            added = 1;
            break;
        }
    }

    if (!added) {
        printf("Danh sách kết nối đầy! Không thể thêm kết nối mới.\n");
    } else {
        printf("Kết nối đã được thiết lập: ID: %d | IP Address: %s | Port No.: %d\n", new_client.client_id, new_client.in_addr, new_client.in_port);
    }
}
/**************************************************************************************************
 *  Tạo socket cho client và kết nối đến server
 **************************************************************************************************/
int Create_ClientSocket(const char *ip, int port) {
    int sock_fd = TCP_CreateSocket();

    if (sock_fd < 0) {
        perror("Không thể tạo socket");
        return -1;
    }

    if (TCP_Connect(sock_fd, ip, port) < 0) {
        perror("Kết nối thất bại");
        return -1;
    }

    connect_manager_t client = {
        .client_id = id_counter++,
        .in_addr = strdup(ip),
        .in_port = port,
        .sock_fd = sock_fd
    };

    Add_Client(client);

    return sock_fd;
}

/**************************************************************************************************
 *  Chấp nhận kết nối mới từ client
 **************************************************************************************************/
void Accept_NewConnection(int listen_fd) {
    int client_port;
    char client_ip[INET_ADDRSTRLEN];

    int client_fd = TCP_AcceptConnection(listen_fd, &client_port, client_ip);

    if (client_fd < 0) {
        perror("Không thể chấp nhận kết nối");
        return;
    }

    connect_manager_t client = {
        .client_id = id_counter++,
        .in_addr = strdup(client_ip),
        .in_port = client_port,
        .sock_fd = client_fd
    };

    Add_Client(client);
}

/**************************************************************************************************
 *  Xử lý các tin nhắn từ client
 **************************************************************************************************/
void Client_Handler(void) {
    for (int i = 0; i < MAX_CLIENTS; i++) {
        if (clients_p[i] != NULL && clients_p[i]->sock_fd > 0) {
            char buffer[BUFFER_SIZE];
            int bytes_received = TCP_ReceiveMessage(clients_p[i]->sock_fd, buffer, BUFFER_SIZE);

            if (bytes_received < 0) {
                perror("Lỗi khi nhận tin nhắn");
                return;
            } else if (bytes_received == 0) {
                printf("\nKết nối đã đóng: %s trên cổng %d\n", clients_p[i]->in_addr, clients_p[i]->in_port);
                Remove_Client(clients_p[i]->client_id);
            } else {
                printf("\nTin nhắn nhận từ: %s\n", clients_p[i]->in_addr);
                printf("Cổng: %d\n", clients_p[i]->in_port);
                printf("Tin nhắn nhận được: %s\n", buffer);
            }
        }
    }
}

/**************************************************************************************************
 *  Gửi tin nhắn đến một client cụ thể
 **************************************************************************************************/
void Send_ToClient(char *message, uint32_t client_id) {
    for (int i = 0; i < MAX_CLIENTS; i++) {
        if (clients_p[i] != NULL && clients_p[i]->client_id == client_id) {
            if (TCP_SendMessage(clients_p[i]->sock_fd, message) < 0) {
                perror("Lỗi khi gửi tin nhắn");
                return;
            }
        }
    }
}

/**************************************************************************************************
 *  Xóa client khỏi danh sách kết nối
 **************************************************************************************************/
void Remove_Client(uint32_t client_id) {
    uint8_t id_found = 0;
    for (int i = 0; i < MAX_CLIENTS; i++) {
        if (clients_p[i] != NULL && clients_p[i]->client_id == client_id) {
            if (TCP_CloseConnection(clients_p[i]->sock_fd) < 0) {
                perror("Lỗi khi đóng kết nối");
                return;
            }

            printf("Đã đóng kết nối: ID: %d | IP Address: %s | Port No.: %d\n", clients_p[i]->client_id, clients_p[i]->in_addr, clients_p[i]->in_port);
            free(clients_p[i]);
            clients_p[i] = NULL;
            id_found = 1;
            break;
        }
    }

    if (!id_found) {
        printf("Không tồn tại kết nối với ID: %d\n", client_id);
    }
}

/**************************************************************************************************
 *  Xóa tất cả các client khỏi danh sách kết nối
 **************************************************************************************************/
void Remove_AllClients(void) {
    for (int i = 0; i < MAX_CLIENTS; i++) {
        if (clients_p[i] != NULL) {
            if (TCP_CloseConnection(clients_p[i]->sock_fd) < 0) {
                perror("Lỗi khi đóng kết nối");
                return;
            }

            printf("Đã đóng kết nối: ID: %d | IP Address: %s | Port No.: %d\n", clients_p[i]->client_id, clients_p[i]->in_addr, clients_p[i]->in_port);
            free(clients_p[i]);
            clients_p[i] = NULL;
        }
    }
}

/**************************************************************************************************
 *  Liệt kê tất cả các kết nối hiện tại
 **************************************************************************************************/
void List_AllConnections(void) {
    uint8_t is_empty = 1;
    for (int i = 0; i < MAX_CLIENTS; i++) {
        if (clients_p[i] != NULL) {
            printf("ID Kết nối: %d | IP Address: %s | Port No. : %d\n", clients_p[i]->client_id, clients_p[i]->in_addr, clients_p[i]->in_port);
            is_empty = 0;
        }
    }
    if (is_empty) {
        printf("Không có kết nối hoạt động.\n");
    }
}

/**************************************************************************************************
 *  Lấy địa chỉ IP của máy chủ
 **************************************************************************************************/
void Get_MyIp(int sock_fd) {
    struct sockaddr_in local_addr;
    socklen_t addr_len = sizeof(local_addr);

    if (getsockname(sock_fd, (struct sockaddr *)&local_addr, &addr_len) == -1) {
        perror("getsockname");
        return;
    }

    char ip[INET_ADDRSTRLEN];
    inet_ntop(AF_INET, &local_addr.sin_addr, ip, sizeof(ip));
    int port = ntohs(local_addr.sin_port);

    printf("Socket đã bind vào IP Address: %s, Port No.: %d\n", ip, port);
}
