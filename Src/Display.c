/**************************************************************************************************
 *  Chat Application Demo
 *  -------------------------------------------------------------------------------------------------------------------
 *  \verbatim
 *  Author: Nguyen Van Thanh
 *  Created on: 1/09/2025
 *  Contact: https://thanhlearningcode.github.io/Myprofile/
 *  This software provides a demo chat application that supports multiple commands.
 *  \endverbatim
 **************************************************************************************************/

#include "Display.h"

/* Cấu trúc lưu trữ lệnh */
typedef struct {
    const char *command;
    const char *description;
} Command_t;

/**************************************************************************************************
 *  Mảng các lệnh cho menu
 *  -------------------------------------------------------------------------------------------------------------------
 *  Các lệnh dưới đây được định nghĩa trong mảng commands[] và được sử dụng để tương tác với
 *  ứng dụng chat demo.
 **************************************************************************************************/
static const Command_t commands[] = {
    {"help",                           "Display user interface options"          },
    {"myIp",                           "Display the server's IP address"         },
    {"myPort",                         "Display the server's port"               },
    {"connect <ip> <port>",            "Connect to a remote server"              },
    {"list",                           "Display the list of active connections"  },
    {"terminate <connection id>",      "Terminate a specific connection"         },
    {"send <connection id> <message>", "Send a message to a specific connection" },
    {"exit",                           "Exit the application"                    },
};

/**************************************************************************************************
 *  Hàm hiển thị menu
 *  -------------------------------------------------------------------------------------------------------------------
 *  Hàm DisplayMenu sẽ hiển thị các lệnh người dùng có thể nhập để tương tác với ứng dụng.
 **************************************************************************************************/
void DisplayMenu (void) {
int i = 0;
int SIZE = sizeof(commands) / sizeof(commands[0]);
    /* In ra tiêu đề của menu */
        printf("\n*** Welcome to My ChatApllication ***\n\n");
        printf("USING COMMANDS:\n");

    /* Duyệt và in ra các lệnh */
    for (; i < SIZE ;) {
        printf("%d. %-35s : %s\n", i + 1, commands[i].command, commands[i].description);
        i++;
    }
    printf("\n Gõ Phím ở đây \n");
}
void GoodBye_Custommer (void) {
    printf("Thank you for using my service");
}
