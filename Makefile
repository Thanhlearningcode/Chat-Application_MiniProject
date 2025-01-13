CC = gcc
CFLAGS = -Wall -pthread

# Tệp nguồn
SRC =  Socket.c Communication.c Display.c main.c

# Tệp đối tượng
OBJ = $(SRC:.c=.o)

# Tên của tệp thực thi
TARGET = chat_app

# Mục tiêu mặc định để tạo tệp thực thi
all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $(TARGET) $(CFLAGS)

# Quy tắc biên dịch .c thành .o
%.o: %.c
	$(CC) -c $< -o $@

# Dọn dẹp tệp đối tượng và tệp thực thi
clean:
	rm -f *.o $(TARGET)

# Tùy chọn: Làm lại (clean và build lại)
rebuild: clean all
