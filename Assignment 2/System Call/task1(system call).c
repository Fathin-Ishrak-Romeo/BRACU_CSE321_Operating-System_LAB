#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char *argv[]) {
    int file_descriptor;
    char input[1024];
    ssize_t bytes_written;

    if (argc != 2) {
        printf("Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    file_descriptor = open(argv[1], O_WRONLY | O_CREAT | O_APPEND, 0644);
    if (file_descriptor == -1) {
        perror("Error opening file");
        return 1;
    }

    printf("File '%s' opened successfully. Enter strings to write to the file (type '-1' to exit):\n", argv[1]);

    while (1) {
        printf("Enter string: ");
        fgets(input, sizeof(input), stdin);

        input[strcspn(input, "\n")] = '\0';

        if (strcmp(input, "-1") == 0) {
            break;
        }

        bytes_written = write(file_descriptor, input, strlen(input));
        if (bytes_written == -1) {
            perror("Error writing to file");
            close(file_descriptor);
            return 1;
        }

        write(file_descriptor, "\n", 1);
    }

    close(file_descriptor);
    printf("Data written to file successfully. File closed.\n");

    return 0;
}
