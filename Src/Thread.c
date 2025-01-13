#include "Thread.h"
#include "Socket.h"
#include "Communication.h"
#include <pthread.h>
#include <stdio.h>

/**
 * @brief Hàm chạy trong luồng để chấp nhận kết nối từ client.
 * 
 * @param[in] arg Socket của server.
 */
void *Accept_ConnectThread (void *arg) {
    int listen_fd = *((int *)arg);   /**< Mô tả socket server */
    
    while (1) {  /**< Vòng lặp vô hạn để liên tục chấp nhận kết nối */
        Accept_NewConnection (listen_fd);   /**< Chấp nhận kết nối mới từ client */
    }
}

/**
 * @brief Hàm chạy trong luồng để xử lý giao tiếp với client.
 * 
 * @param[in] arg Tham số không sử dụng.
 */
void *Handle_ClientThread (void *arg) {
    while (1) {  /**< Vòng lặp vô hạn để liên tục xử lý yêu cầu của client */
        Client_Handler();   /**< Xử lý giao tiếp với client */
    }
}

/**
 * @brief Tạo luồng để chấp nhận kết nối từ client.
 * 
 * @param[in] listen_fd Socket của server.
 * @return 0 nếu thành công, khác 0 nếu có lỗi.
 */
int CreateAcceptConnectionThread(int listen_fd) {
    pthread_t accept_thread;  /**< Biến để lưu thông tin của luồng */
    
    int result = pthread_create(&accept_thread, NULL, Accept_ConnectThread, &listen_fd);
    if (result != 0) {
        perror("Error creating accept connection thread");

     /* Note *Do sử dụng con trỏ void nên phải ép kiểu ko là lỗi nhé mặc dù kiểu trả về là int*/
        return (int)result;  /**< Trả về lỗi nếu tạo luồng không thành công */
    }
    
    return 0;  /**< Trả về 0 nếu tạo luồng thành công */
}

/**
 * @brief Tạo luồng để xử lý giao tiếp với client.
 * 
 * @return 0 nếu thành công, khác 0 nếu có lỗi.
 */
int CreateClientHandlerThread(void) {
    pthread_t handler_thread;  /**< Biến để lưu thông tin của luồng */
    
    int result = pthread_create(&handler_thread, NULL, Handle_ClientThread, NULL);
    if (result != 0) {
        perror("Error creating client handler thread");

    /* Note *Do sử dụng con trỏ void nên phải ép kiểu ko là lỗi nhé mặc dù kiểu trả về là int*/
        return (int)result;  /**< Trả về lỗi nếu tạo luồng không thành công */
    }
    
    return 0;  /**< Trả về 0 nếu tạo luồng thành công */
}
