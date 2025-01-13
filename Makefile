# Biến để chỉ định trình biên dịch và các cờ biên dịch
CC = gcc
CFLAGS = -Wall -pthread

# Các tệp nguồn
SRC = Socket.c Communication.c Display.c main.c Thread.c

# Các tệp đối tượng tương ứng với các tệp nguồn
OBJ = $(SRC:.c=.o)

# Tên tệp thực thi cuối cùng
TARGET = chat_app

# Mục tiêu mặc định để biên dịch tệp thực thi
all: $(TARGET)

# Quy tắc để tạo tệp thực thi từ các tệp đối tượng
$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $(TARGET) $(CFLAGS)

# Quy tắc biên dịch các tệp nguồn thành các tệp đối tượng
%.o: %.c
	$(CC) -c $< -o $@

# Mục tiêu dọn dẹp: Xóa các tệp đối tượng và tệp thực thi
clean:
	rm -f $(OBJ) $(TARGET)

# Mục tiêu rebuild: Dọn dẹp và biên dịch lại
rebuild: clean all

# Mục tiêu giúp đỡ để người dùng biết các lệnh có sẵn trong Makefile
help:
	@echo "Available targets:"
	@echo "  all       - Build the project (default target)"
	@echo "  clean     - Remove object files and executable"
	@echo "  rebuild   - Clean and rebuild the project"
	@echo "  help      - Show this help message"
