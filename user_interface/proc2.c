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
    int fd_read = open(pipe1, O_RDONLY);  // Open pipe1 for reading
    int fd_write = open(pipe2, O_WRONLY); // Open pipe2 for writing

    if (fd_read == -1 || fd_write == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }

    while (1) {
        // Read message from Process 1
        read(fd_read, buffer, sizeof(buffer));
        printf("Process 2: Received from Process 1: %s", buffer);

        // Check for exit condition
        if (strcmp(buffer, "exit\n") == 0) {
            break;
        }

        // Read input from the user
        printf("Process 2: Enter a response (or 'exit' to quit): ");
        fgets(buffer, sizeof(buffer), stdin);

        // Send the response to Process 1
        write(fd_write, buffer, strlen(buffer) + 1);
    }

    // Close pipes
    close(fd_read);
    close(fd_write);

    return 0;
}