/**
 * @file    main.c
 * @brief   Main function for chat application using server-client model
 * @details This file contains the entry point of the chat application, 
 *          initializing the server socket and handling user commands.
 *          It also creates two threads: one for accepting new connections 
 *          and another for handling client communication.
 * @version 1.0
 * @date    2025-01-13
 * 
 * @see     Socket.h, Communication.h, Display.h
 */

#include "Socket.h"         /**< Socket related functions */
#include "Communication.h"   /**< Communication related functions */
#include "Display.h"         /**< Display functions for user interaction */
#include <pthread.h>         /**< POSIX thread library */
#include <string.h>          /**< String manipulation functions like strtok, strcmp, strcspn */
#include <stdlib.h>          /**< Standard library for atoi, exit */
#include <unistd.h>          /**< Unix standard functions like close */
#define MAX_INPUT_SIZE 100   /**< Maximum size for user input */

/**
 * @brief Mutex for synchronization when accessing the client list.
 * 
 * This mutex ensures thread-safe access to the shared client list across multiple threads.
 */
pthread_mutex_t client_list_mutex = PTHREAD_MUTEX_INITIALIZER;

/**
 * @brief Thread function to accept new client connections.
 * 
 * This function runs in a separate thread and continuously waits for 
 * incoming connections, calling Accept_NewConnection() whenever 
 * a new connection is detected.
 *
 * @param[in] arg The server socket file descriptor.
 */
void *accept_connection_thread(void *arg) {
    int listen_fd = *((int *)arg);   /**< Server socket file descriptor */
    
    while (1) {  /**< Infinite loop for accepting connections */
        Accept_NewConnection(listen_fd);   /**< Accept a new client connection */
    }
}

/**
 * @brief Thread function to handle client requests.
 * 
 * This function runs in a separate thread and continuously processes 
 * client requests by calling Client_Handler().
 * 
 * @param[in] arg Unused parameter.
 */
void *client_handler_thread(void *arg) {
    while (1) {  /**< Infinite loop for handling clients */
        Client_Handler();   /**< Handle client communication */
    }
}

/**
 * @brief Main entry point for the chat application.
 * 
 * Initializes the server, creates threads for accepting connections 
 * and handling clients, and processes user input commands for the chat application.
 * 
 * @param[in] argc The number of command-line arguments.
 * @param[in] argv The array of command-line argument strings.
 * 
 * @return 0 if the program terminates successfully, otherwise an error code.
 */
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

    pthread_t accept_thread, handler_thread;  /**< Thread identifiers for connection and client handling */
    
    /**
     * @brief Create the thread to accept incoming connections.
     */
    pthread_create(&accept_thread, NULL, accept_connection_thread, &server_fd);  /**< Create accept connection thread */
    
    /**
     * @brief Create the thread to handle client communication.
     */
    pthread_create(&handler_thread, NULL, client_handler_thread, NULL);  /**< Create client handler thread */

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
