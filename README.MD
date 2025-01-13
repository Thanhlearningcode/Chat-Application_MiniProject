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
   ```bash
   git clone https://github.com/Thanhlearningcode/A-Chat-Application-.git
