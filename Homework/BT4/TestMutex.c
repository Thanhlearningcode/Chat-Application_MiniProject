#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

int count = 0;  // Biến chia sẻ
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;  // Khởi tạo mutex

// Hàm sẽ được thực thi bởi mỗi thread
void *thread_count_up(void *arg) {
    pthread_mutex_lock(&mutex);  // Khóa mutex trước khi thay đổi biến count

    printf("Thread %ld bắt đầu đếm với mutex.\n", pthread_self());
    for (int i = 0; i < 1000000; i++) {
        count += 1;  // Tăng biến count
    }

    pthread_mutex_unlock(&mutex);  // Mở khóa mutex
    pthread_exit(NULL);  // Kết thúc thread
}

int main() {
    __uint8_t num_threads = 3;  // Số lượng thread
    pthread_t thread[num_threads];  // Mảng chứa các identifier của thread

    printf("Trước khi đếm: %d\n", count);  // In ra giá trị ban đầu của count

    for (int i = 0; i < num_threads; i++) {
        // Tạo các thread và thực thi
        if (pthread_create(&thread[i], NULL, thread_count_up, NULL) != 0) {
            perror("Tạo thread thất bại");
            exit(1);
        }
    }

    // Đợi tất cả các thread kết thúc
    for (int i = 0; i < num_threads; i++) {
        if (pthread_join(thread[i], NULL) != 0) {
            perror("Tham gia thread thất bại");
            exit(1);
        }
    }

    printf("Sau khi đếm: %d\n", count);  // In ra giá trị của count sau khi các thread hoàn thành
    return 0;
}
