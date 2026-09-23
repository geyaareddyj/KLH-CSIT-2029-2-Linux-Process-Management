#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
    int source, destination;
    char buffer[100];
    int n;

    // Open source file for reading
    source = open("source.txt", O_RDONLY);

    // Open destination file for writing
    // Create it if it does not exist
    // Truncate it if it already exists
    destination = open("copy.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);

    if (source < 0 || destination < 0) {
        printf("Error opening file\n");
        return 1;
    }

    // Read from source and write to destination
    while ((n = read(source, buffer, sizeof(buffer))) > 0) {
        write(destination, buffer, n);
    }

    // Close both files
    close(source);
    close(destination);

    printf("File copied successfully.\n");

    return 0;
}
