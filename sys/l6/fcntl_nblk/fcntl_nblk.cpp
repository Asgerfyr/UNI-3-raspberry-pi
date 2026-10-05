#include <unistd.h>
#include <fcntl.h> // fcntl() defined here
#include <errno.h> // errno & standard error codes defined here
#include <iostream>

#define BUF_SIZE 128

int main(int argc, char* argv[]) {
  char buffer[BUF_SIZE];

  // Get all flags for standard input (keyboard) FD
  int flags = fcntl(STDIN_FILENO, F_GETFL, 0);
  if (flags < 0) { perror("fcntl()"); return EXIT_FAILURE; }

  // Set standard input (keyboard) FD to non-blocking mode
  // and set all other flags to original values
  int ret = fcntl(STDIN_FILENO, F_SETFL, flags | O_NONBLOCK);
  if (ret < 0) { perror("fcntl()"); return EXIT_FAILURE; }

  // Write to standard output (screen)
  const char prompt[] = "Enter some text: ";
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

  buffer[bytes] = '\0'; // Null-terminate string in buffer

  // Echo back to screen
  const char reply[] = "You entered: ";
  write(STDOUT_FILENO, reply, sizeof(reply));
  write(STDOUT_FILENO, buffer, bytes);

  return EXIT_SUCCESS;
}
