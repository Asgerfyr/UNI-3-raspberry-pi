#include <poll.h> // poll() defined here
#include <linux/gpio.h> // GPIO character device API
#include <sys/ioctl.h> // ioctl() defined here
#include <string.h> // memset() and strlen() defined here
#include <fcntl.h> // open() and O_RDONLY defined here
#include <unistd.h> // close() defined here
#include <iostream>

// Define GPIO lines
#define BTN_A 27
#define BTN_B 22
#define BTN_UP 12
#define BTN_DOWN 16
#define BTN_LEFT 5
#define BTN_RIGHT 6

#define POLL_TIMEOUT_MS 0

int main(int argc, char* argv[]) {
  // Open gpiochip0 as read-only device
  int fd = open("/dev/gpiochip0", O_RDONLY);
  if (fd < 0) { perror("open()"); return EXIT_FAILURE; }

  // Array of structs holding file descriptors to poll
  struct pollfd fds[6];
  // Array of structs to request event-based GPIO lines
  struct gpioevent_request req[6];
  // Array of structs to store GPIO event data
  struct gpioevent_data data[6];

  // Populate gpioevent_request struct with 0s to be safe
  for (int i = 0; i < 6; ++i) {
    memset(&req[i], 0, sizeof(req[i]));
  }

  // Specify GPIO lines we want to access
  req[0].lineoffset = BTN_A;
  req[1].lineoffset = BTN_B;
  req[2].lineoffset = BTN_UP;
  req[3].lineoffset = BTN_DOWN;
  req[4].lineoffset = BTN_LEFT;
  req[5].lineoffset = BTN_RIGHT;

  for (int i = 0; i < 6; ++i) {
    // Set GPIO lines to report both rising and falling edges
    req[i].eventflags = GPIOEVENT_REQUEST_BOTH_EDGES;
    // Set GPIO lines as inputs
    req[i].handleflags = GPIOHANDLE_REQUEST_INPUT;
    // Set a name to be shown when gpioinfo is called
    strcpy(req[i].consumer_label, "GPIO event monitor");

    // Use ioctl to request GPIO line event
    int ret_val = ioctl(fd, GPIO_GET_LINEEVENT_IOCTL, &req[i]);
    if (ret_val < 0) {
      perror("ioctl()");
      for (int j = 0; j < 6; ++j) { close(req[j].fd); }
      close(fd);
      return EXIT_FAILURE;
    }

    fds[i].fd = req[i].fd; // Copy file descriptor to fd in struct pollfd
    fds[i].events = POLLIN; // Event to monitor: data available to read
    fds[i].revents = 0; // Reset revents before monitoring GPIO lines

    std::cout << "Monitoring button " << i << " for edge events...\n";
  }

  // Read events on all GPIO lines infinitely
  while (true) {
      // Use poll() to monitor all file descriptors
      int ret_val = poll(fds, 6, POLL_TIMEOUT_MS);
      // std::cout << "Waiting...\n";
      if (ret_val < 0) { // Handle error
        perror("poll()");
        for (int j = 0; j < 6; ++j) { close(req[j].fd); }
        close(fd);
        return EXIT_FAILURE;
      }

    // Read all file descriptors for edge events in a loop
    for (int i = 0; i < 6; ++i) {
      if (fds[i].revents & POLLIN) { // Check if data is available
        ssize_t bytes = read(fds[i].fd, &data[i], sizeof(data[i]));
        if (bytes != sizeof(data[i])) { perror("read"); } // Handle error
        else if (data[i].id == GPIOEVENT_EVENT_RISING_EDGE) { // Rising edge
               std::cout << "\nButton " << i << ": rising edge";
             }
        usleep(50000); // 50 ms sleep to handle debounce (accidental press)
        if (bytes != sizeof(data[i])) { perror("read"); } // Handle error
        else if (data[i].id == GPIOEVENT_EVENT_FALLING_EDGE) { // Falling edge
               std::cout << "\nButton " << i << ": falling edge";
             }
      } // End of if (fds[i].revents & POLLIN)
    } // End of for loop
  } // End of while loop

  for (int i = 0; i < 6; ++i) {
    close(req[i].fd);
  }
  close(fd);
  return EXIT_SUCCESS;
}
