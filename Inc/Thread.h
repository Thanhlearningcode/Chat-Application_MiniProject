#ifndef THREAD_MANAGER_H
#define THREAD_MANAGER_H

#include <pthread.h>

/**
 * @brief Tạo luồng để chấp nhận kết nối từ client.
 * 
 * @param[in] listen_fd Socket của server.
 * @return 0 nếu thành công, khác 0 nếu có lỗi.
 */
int CreateAcceptConnectionThread(int listen_fd);

/**
 * @brief Tạo luồng để xử lý giao tiếp với client.
 * 
 * @return 0 nếu thành công, khác 0 nếu có lỗi.
 */
int CreateClientHandlerThread(void);

#endif /* THREAD_MANAGER_H */
