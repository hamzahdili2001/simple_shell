#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

ssize_t _getline(char **lineptr, size_t *n, int fd) {
    if (!lineptr || !n) {
        errno = EINVAL;
        return -1;
    }

    static const size_t INIT_BUFFER_SIZE = 16;
    static const size_t MAX_INPUT_SIZE = 1024 * 1024;

    if (*lineptr == NULL) {
        *lineptr = malloc(INIT_BUFFER_SIZE);
        if (*lineptr == NULL) {
            return -1;
        }
        *n = INIT_BUFFER_SIZE;
    }

    size_t pos = 0;
    while (1) {
        // Read a block of input from the file descriptor
        char buffer[INIT_BUFFER_SIZE];
        ssize_t num_read = read(fd, buffer, INIT_BUFFER_SIZE);
        if (num_read == -1) {
            if (errno == EINTR) {
                continue; // Interrupted by signal, try again
            } else {
                return -1;
            }
        } else if (num_read == 0) {
            break; // End of file
        }

        // Check if we need to resize the buffer
        if (pos + num_read >= *n) {
            *n *= 2;
            char *new_ptr = realloc(*lineptr, *n);
            if (new_ptr == NULL) {
                return -1;
            }
            *lineptr = new_ptr;
        }

        // Copy the input into the buffer
        for (size_t i = 0; i < num_read; i++) {
            (*lineptr)[pos++] = buffer[i];
            if (pos >= MAX_INPUT_SIZE) {
                return -1;
            }
            if (buffer[i] == '\n') {
                (*lineptr)[pos - 1] = '\0';
                return pos - 1;
            }
        }
    }

    if (pos > 0) {
        (*lineptr)[pos] = '\0';
        return pos;
    }

    return -1;
}

