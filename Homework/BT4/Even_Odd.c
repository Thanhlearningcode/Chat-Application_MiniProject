#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>

int num_odd = 0;  // Biến đếm số lẻ
int num_even = 0;  // Biến đếm số chẵn
#define ARR_SIZE    100  // Kích thước mảng
#define MAX_NUM     100  // Số lớn nhất có thể
#define MIN_NUM     0    // Số nhỏ nhất có thể

pthread_mutex_t mutex;  // Mutex để bảo vệ các biến chia sẻ

// Hàm thực thi của mỗi thread để đếm số lẻ
void *thread_count_odd(void *arg) {
    printf("Thread %ld bắt đầu đếm số lẻ.\n", pthread_self());
    for (int i = 0; i < ARR_SIZE; i++) {
        if (*((int *)arg + i) % 2 != 0) {
            pthread_mutex_lock(&mutex);  // Khóa mutex trước khi sửa đổi biến chia sẻ
            num_odd++;
            pthread_mutex_unlock(&mutex);  // Mở khóa mutex sau khi sửa đổi
        }
    }
    pthread_exit(NULL);  
}

// Hàm thực thi của mỗi thread để đếm số chẵn
void *thread_count_even(void *arg) {
    printf("Thread %ld bắt đầu đếm số chẵn.\n", pthread_self());
    for (int i = 0; i < ARR_SIZE; i++) {
        if (*((int *)arg + i) % 2 == 0) {
            pthread_mutex_lock(&mutex);  // Khóa mutex trước khi sửa đổi biến chia sẻ
            num_even++;    
            pthread_mutex_unlock(&mutex);  // Mở khóa mutex sau khi sửa đổi
        }
    }
    pthread_exit(NULL);  
}

int main() {
    __uint8_t num_threads = 2;  // Số lượng thread
    pthread_t thread[num_threads];  // Mảng để chứa các thread

    // Khởi tạo mảng số ngẫu nhiên
    srand(time(0));
    int num_arr[ARR_SIZE];

    // In ra mảng số ngẫu nhiên
    printf("Mảng đầu vào: [ ");
    for (int i = 0; i < ARR_SIZE; i++) {
        num_arr[i] = rand() % (MAX_NUM - MIN_NUM);
        printf("%d ", num_arr[i]);
    }
    printf("]\n");

    // Khởi tạo mutex
    if (pthread_mutex_init(&mutex, NULL) != 0) {
        perror("Không thể khởi tạo mutex");
        exit(1);
    }

    // Tạo thread đếm số lẻ
    if (pthread_create(&thread[0], NULL, thread_count_odd, (void *)num_arr) != 0) {
        perror("Không thể tạo thread");
        exit(1);
    }

    // Tạo thread đếm số chẵn
    if (pthread_create(&thread[1], NULL, thread_count_even, (void *)num_arr) != 0) {
        perror("Không thể tạo thread");
        exit(1);
    }
        
    // Chờ các thread hoàn thành
    for (int i = 0; i < num_threads; i++) {
        if (pthread_join(thread[i], NULL) != 0) {
            perror("Không thể join thread");
            exit(1);
        }
    }

    // In kết quả đếm số lẻ và số chẵn
    printf("Số lượng số lẻ: %d\n", num_odd);
    printf("Số lượng số chẵn: %d\n", num_even);

    // Hủy mutex sau khi sử dụng
    pthread_mutex_destroy(&mutex);

    return 0;
}
