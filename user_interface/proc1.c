#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
    const char* pipe1 = "pipe1_to_pipe2"; // Pipe for Process 1 -> Process 2
    const char* pipe2 = "pipe2_to_pipe1"; // Pipe for Process 2 -> Process 1
    char buffer[100];

    // Open pipes
    int fd_write = open(pipe1, O_WRONLY); // Open pipe1 for writing
    int fd_read = open(pipe2, O_RDONLY);  // Open pipe2 for reading

    if (fd_write == -1 || fd_read == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }

    while (1) {
        // Read input from the user
        printf("Process 1: Enter a message (or 'exit' to quit): ");
        fgets(buffer, sizeof(buffer), stdin);

        // Send the message to Process 2
        write(fd_write, buffer, strlen(buffer) + 1);

        // Check for exit condition
        if (strcmp(buffer, "exit\n") == 0) {
            break;
        }

        // Read response from Process 2
        read(fd_read, buffer, sizeof(buffer));
        printf("Process 1: Received from Process 2: %s", buffer);
    }

    // Close pipes
    close(fd_write);
    close(fd_read);

    return 0;
}