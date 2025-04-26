#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <semaphore.h>

#define PORT 8080
#define BUFFER_SIZE 1024
#define MAX_CLIENTS 10
   

// Structure to hold client data
typedef struct {
    int socket;
} client_data_t;

// Thread pool
pthread_t thread_pool[MAX_CLIENTS];
sem_t semaphore; // Semaphore to control access to the thread pool

void *handle_client(void *arg) {
    client_data_t *client_data = (client_data_t *)arg;
    char buffer[BUFFER_SIZE] = {0};

    // Read data from the client
    read(client_data->socket, buffer, BUFFER_SIZE);
    printf("Message from client: %s\n", buffer);

    // Close the socket for this client
    close(client_data->socket);
    free(client_data); // Free the allocated memory for client data
    return NULL;
}

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);

    // Initialize semaphore
    sem_init(&semaphore, 0, MAX_CLIENTS); // Initialize semaphore with MAX_CLIENTS

    // Create socket file descriptor
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    // Forcefully attaching socket to the port 8080
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt))) {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }

    // Define the type of socket created
    address.sin_family = AF_INET; // IPv4
    address.sin_addr.s_addr = INADDR_ANY; // Accept connections from any IP
    address.sin_port = htons(PORT); // Convert to network byte order

    // Bind the socket to the specified port
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    // Start listening for incoming connections
    if (listen(server_fd, 3) < 0) {
        perror("listen");
        exit(EXIT_FAILURE);
    }

    printf("Server is listening on port %d\n", PORT);

    while (1) {
        // Accept a connection
        if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) {
            perror("accept");
            exit(EXIT_FAILURE);
        }

        // Wait for a free thread
        sem_wait(&semaphore);

        // Allocate memory for client data
        client_data_t *client_data = malloc(sizeof(client_data_t));
        client_data->socket = new_socket;

        // Create a new thread to handle the client
        pthread_create(&thread_pool[new_socket % MAX_CLIENTS], NULL, handle_client, client_data);
    }

    // Close the server socket (this line will never be reached in this example)
    close(server_fd);
    sem_destroy(&semaphore); // Clean up semaphore
    return 0;
}