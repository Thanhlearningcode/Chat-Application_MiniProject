# Chat Application (Server-Client Model)

## Mô Tả
Ứng dụng Chat này sử dụng mô hình server-client với kết nối TCP/IP, cho phép người dùng giao tiếp với nhau qua mạng. Server quản lý các kết nối từ nhiều client đồng thời thông qua các luồng (threads). Người dùng có thể gửi và nhận tin nhắn, cũng như quản lý các kết nối client qua giao diện dòng lệnh.

## Tính Năng
- **Server quản lý kết nối**: Chấp nhận nhiều kết nối từ nhiều client.
- **Gửi/nhận tin nhắn**: Client có thể gửi và nhận tin nhắn từ server.
- **Quản lý kết nối**: Server cho phép liệt kê, ngắt kết nối, và gửi tin nhắn đến client.
- **Các lệnh từ người dùng**: Hỗ trợ các lệnh quản lý như `connect`, `list`, `terminate`, `send`, `exit`.
- **Đồng bộ hóa**: Đảm bảo các thao tác trên danh sách client được thực hiện một cách thread-safe với mutex.

## Các Lệnh Chính
- `help`: Hiển thị danh sách các lệnh có sẵn.
- `myIp`: Hiển thị địa chỉ IP của server.
- `myPort`: Hiển thị cổng mà server đang lắng nghe.
- `connect <ip> <port>`: Kết nối client tới server với địa chỉ IP và cổng chỉ định.
- `list`: Liệt kê tất cả các kết nối hiện tại.
- `terminate <connection_id>`: Ngắt kết nối với client có ID chỉ định.
- `send <connection_id> <message>`: Gửi tin nhắn đến client có ID chỉ định.
- `exit`: Ngắt kết nối với tất cả các client và đóng server.

## Hướng Dẫn Cài Đặt và Sử Dụng

### Cài Đặt
1. Clone repository về máy:
2. Di chuyển vào thư mục dự án:
 $  cd chat-app
 $  git clone https://github.com/Thanhlearningcode/A-Chat-Application-.git
3. Biên dịch ứng dụng:
 $ make
4. Chạy ứng dụng chat server:
 $  ./chat_app <port> 
Ex : ./chat_app 8080
*Chạy Client*
Để kết nối đến server, bạn có thể chạy client bằng cách sử dụng lệnh connect trong giao diện dòng lệnh:
1. Kết nối Client:
connect <server_ip> <port>
Ex : connect 127.0.0.1 8080
2.  Hiển thị thông tin của Server:
Sử dụng lệnh myIp để hiển thị địa chỉ IP của server.
    myIp
Sử dụng lệnh myPort để hiển thị cổng mà server đang
    myPort
Liệt kê các kết nối:
Để xem tất cả các kết nối đang hoạt động, sử dụng lệnh list
    list
Ngắt kết nối Client:
    terminate <connection_id>
Gửi tin nhắn đến Client:
Để gửi tin nhắn đến client có ID cụ thể, sử dụng lệnh send:
send <connection_id> <message>
Thoát khỏi Server:
exit





