/**
 * @file    main.c
 * @brief   Main function for chat application using server-client model
 * @details This file contains the entry point of the chat application, 
 *          initializing the server socket and handling user commands.
 *          It also creates two threads: one for accepting new connections 
 *          and another for handling client communication.
 * @version 1.0
 * @date    2025-01-09
 * 
 * @see     Socket.h, Communication.h, Display.h
 */

#include "Socket.h"         
#include "Communication.h"   
#include "Display.h"        
#include <pthread.h>        
#include <string.h>          /**< String manipulation functions like strtok, strcmp, strcspn */
#include <stdlib.h>          /**< Standard library for atoi, exit */
#include <unistd.h>    
#include "Thread.h"


#define MAX_INPUT_SIZE 100   /**< Maximum size for user input */

/**
 * @brief Mutex for synchronization when accessing the client list.
 * 
 * This mutex ensures thread-safe access to the shared client list across multiple threads.
 */
pthread_mutex_t client_list_mutex = PTHREAD_MUTEX_INITIALIZER;


int main(int argc, char *argv[]) {
    if (argc < 2) {
        perror("Exit with error due to incorrect number of arguments\n");
        return 1;
    }

    int port = atoi(argv[1]);  /**< Port number for the server */
    int server_fd = Create_ServerSocket(port);  /**< Create the server socket */
    
    if (server_fd < 0) {
        perror("Failed to create server socket");
        return 1;
    }

/**
 * @brief Create the thread to accept incoming connections.
 */
 if (CreateAcceptConnectionThread(server_fd) != 0) {
        perror("Failed to create accept connection thread");
        return 1;
    }
/**
 * @brief Create the thread to handle client communication.
 */
    if (CreateClientHandlerThread() != 0) {
        perror("Failed to create client handler thread");
        return 1;
    }
    char input[MAX_INPUT_SIZE];  /**< Buffer to store user input */
    DisplayMenu();  /**< Display the menu to the user */

    while (1) {
        if (fgets(input, sizeof(input), stdin) == NULL) {
            if (feof(stdin)) {
                printf("End of input detected. Exiting...\n");
                break;
            } else {
                perror("Error reading input. Please try again.");
                continue;
            }
        }

        input[strcspn(input, "\n")] = '\0';  /**< Remove the trailing newline character from the input */

        char *command = strtok(input, " ");  /**< Parse the command */
        if (command == NULL) {
            printf("Invalid command. Type 'help' for a list of commands.\n");
            continue;
        }

        pthread_mutex_lock(&client_list_mutex);  /**< Lock the mutex to protect the shared client list */

        if (strcmp(command, "help") == 0) {
            DisplayMenu();  /**< Show available commands to the user */
        } else if (strcmp(command, "myIp") == 0 || strcmp(command, "myPort") == 0) {
            Get_MyIp(server_fd);  /**< Display the server's IP or port */
        } else if (strcmp(command, "connect") == 0) {
            char *ip = strtok(NULL, " ");  /**< Extract the IP address */
            char *port = strtok(NULL, " ");  /**< Extract the port number */
            if (ip == NULL || port == NULL) {
                printf("Usage: connect <ip> <port>\n");
            } else {
                int client_fd = Create_ClientSocket(ip, atoi(port));  /**< Create a client socket */
                if (client_fd < 0) {
                    printf("Failed to connect to %s:%d\n", ip, atoi(port));
                }
            }
        } else if (strcmp(command, "list") == 0) {
            List_AllConnections();  /**< List all active client connections */
        } else if (strcmp(command, "terminate") == 0) {
            char *connection_id = strtok(NULL, " ");  /**< Extract the connection ID */
            if (connection_id == NULL) {
                printf("Usage: terminate <connection id>\n");
            } else {
                Remove_Client(atoi(connection_id));  /**< Terminate the client connection with the specified ID */
            }
        } else if (strcmp(command, "send") == 0) {
            char *connection_id = strtok(NULL, " ");  /**< Extract the connection ID */
            char *message = strtok(NULL, "");  /**< Extract the message to send */
            if (connection_id == NULL || message == NULL) {
                printf("Usage: send <connection id> <message>\n");
            } else {
                Send_ToClient(message, atoi(connection_id));  /**< Send the message to the client with the specified ID */
            }
        } else if (strcmp(command, "exit") == 0) {
            Remove_AllClients();  /**< Remove all connected clients */
            TCP_CloseConnection(server_fd);  /**< Close the server socket */
            pthread_mutex_unlock(&client_list_mutex);  /**< Unlock the mutex */
            exit(0);  /**< Exit the program */
        } else {
            printf("Invalid command. Type 'help' for a list of commands.\n");
        }

        pthread_mutex_unlock(&client_list_mutex);  /**< Unlock the mutex after processing the command */
    }

    return 0;  /**< Return from the main function */
}
