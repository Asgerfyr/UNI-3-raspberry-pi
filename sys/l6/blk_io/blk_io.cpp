#include <iostream>
#include <unistd.h>

#define BUF_SIZE 128

int main(int argc, char* argv[]) {
  char buffer[BUF_SIZE];

  // Write to standard output (screen)
  const char prompt[] = "Enter some text: ";
  write(STDOUT_FILENO, prompt, sizeof(prompt));

  // Read from standard input (keyboard)
  ssize_t bytes = read(STDIN_FILENO, buffer, BUF_SIZE-1);
  if (bytes < 0) { perror("read() failed"); return EXIT_FAILURE; }
  std::cout << "read() completed!\n";

  buffer[bytes] = '\0'; // Null-terminate string in buffer

  // Write back to screen
  const char reply[] = "You entered: ";
  write(STDOUT_FILENO, reply, sizeof(reply));
  write(STDOUT_FILENO, buffer, bytes);

  return EXIT_SUCCESS;
}

