# Biến chứa trình biên dịch
CC = gcc

# Các cờ biên dịch
CFLAGS = -Wall -pthread -IInc  # Thêm -IInc để chỉ định thư mục chứa các tệp header

# Danh sách các tệp nguồn
SRC = Src/Socket.c Src/Communication.c Src/Display.c Src/main.c Src/Thread.c

# Danh sách các tệp đối tượng (tệp .o)
OBJ = $(SRC:.c=.o)

# Tên tệp thực thi (output file)
TARGET = chat_app

# Mục tiêu mặc định để tạo tệp thực thi
all: $(TARGET)

# Quy tắc tạo tệp thực thi từ các tệp đối tượng
$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $(TARGET) $(CFLAGS)

# Quy tắc biên dịch các tệp .c thành các tệp .o
%.o: %.c
	$(CC) -c $< -o $@ $(CFLAGS)

# Quy tắc dọn dẹp (remove các tệp đối tượng và tệp thực thi)
clean:
	rm -f Src/*.o $(TARGET)  # Xóa các tệp .o trong thư mục Src và tệp thực thi

# Tùy chọn: Làm lại (clean và build lại)
rebuild: clean all
