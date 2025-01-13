/**************************************************************************************************
 *  Header File: DisplayMenu.h
 *  -------------------------------------------------------------------------------------------------------------------
 *  \verbatim
 *  This header file contains the declaration for the function DisplayMenu, which is used to display
 *  the available commands to the user in the chat application. The file also includes necessary 
 *  include guards to prevent multiple inclusions of the same header file.
 *
 *  Author: Nguyen Van Thanh
 *  GitHub: https://thanhlearningcode.github.io/Myprofile/
 *  \endverbatim
 **************************************************************************************************/


#ifndef DISPLAY_MENU_H_   
#define DISPLAY_MENU_H_   

#include <stdio.h>
#include <stdint.h>     
#include <string.h>  // Để sử dụng strtok, strcmp, strcspn
#include <stdlib.h>  // Để sử dụng atoi, exit
#define MAX_COMMAND_LENGTH 100

/**************************************************************************************************
 *  Hàm DisplayMenu
 *  -------------------------------------------------------------------------------------------------------------------
 *  \brief
 *  Hàm này hiển thị các lệnh người dùng có thể nhập để tương tác với ứng dụng.
 *  
 *  \details
 *  Khi gọi hàm này, nó sẽ in ra các lệnh mà người dùng có thể sử dụng trong ứng dụng chat,
 *  bao gồm các lệnh như "help", "myIp", "connect <ip> <port>", v.v.
 *  
 *  \return
 *  Không có giá trị trả về.
 **************************************************************************************************/
void DisplayMenu       (void);   
/**************************************************************************************************
 *  Hàm DisplayMenu
 *  -------------------------------------------------------------------------------------------------------------------
 *  \brief
 *  Hàm này hiển thị lệnh tạm biệt khác hàng 
 */
void GoodBye_Custommer (void);
#endif /* DISPLAY_MENU_H_ */   
