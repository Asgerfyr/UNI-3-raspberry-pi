#include <unistd.h>
#include <sys/ioctl.h> // ioctl() defined here
#include <errno.h>
#include <iostream>

#define BUF_SIZE 128

int main(int argc, char* argv[]) {
    char buffer[BUF_SIZE];

    // 1 = enable non-blocking, 0 = disable non-blocking
    int flags = 1;

    // Set standard input (keyboard) FD to non-blocking mode
    int ret = ioctl(STDIN_FILENO, FIONBIO, &flags);
    if (ret == -1) { perror("ioctl"); return EXIT_FAILURE; }

    const char prompt[] = "Enter some text: ";
    // Write to standard output (screen)
    write(STDOUT_FILENO, prompt, sizeof(prompt));

    // Read from standard input (keyboard)
    ssize_t bytes = read(STDIN_FILENO, buffer, BUF_SIZE-1);

    std::cout << "\nread() completed!\n";

    if (bytes < 0) {
      if (errno == EAGAIN || errno == EWOULDBLOCK) {
        std::cout << "Nothing entered!\n"; }
      else { perror("read()"); }
      return EXIT_FAILURE;
    }

    // Null-terminate string in buffer
    buffer[bytes] = '\0';

    // Echo back to screen
    const char reply[] = "You entered: ";
    write(STDOUT_FILENO, reply, sizeof(reply));
    write(STDOUT_FILENO, buffer, bytes);

    return EXIT_SUCCESS;
}
