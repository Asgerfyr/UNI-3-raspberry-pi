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

#define POLL_TIMEOUT_MS 25

int main(int argc, char* argv[]) {
  // Open gpiochip0 as read-only device
  int fd = open("/dev/gpiochip0", O_RDONLY);
  if (fd < 0) { perror("open()"); return EXIT_FAILURE; }

  // Array of structs holding file descriptors to poll
  struct pollfd fds[1];
  // struct to request level-based GPIO lines
  struct gpiohandle_request req;
  // struct to store GPIO handle data
  struct gpiohandle_data data;

  // Populate gpiohandle_request struct with 0s to be safe
  memset(&req, 0, sizeof(req));
  memset(&data, 0, sizeof(data));

  // Specify GPIO lines we want to access
  req.lineoffsets[0] = BTN_A;
  req.lineoffsets[1] = BTN_B;
  req.lineoffsets[2] = BTN_UP;
  req.lineoffsets[3] = BTN_DOWN;
  req.lineoffsets[4] = BTN_LEFT;
  req.lineoffsets[5] = BTN_RIGHT;

  
  // Set GPIO lines as inputs
  req.flags = GPIOHANDLE_REQUEST_INPUT;
  // set number of GPIO lines to request
  req.lines = 6;
  // Set a name to be shown when gpioinfo is called
  strcpy(req.consumer_label, "GPIO level monitor");

  // Use ioctl to request GPIO line event
  int ret_val = ioctl(fd, GPIO_GET_LINEHANDLE_IOCTL, &req);
  if (ret_val < 0) {
    perror("ioctl()");
    close(req.fd);
    close(fd);
    return EXIT_FAILURE;
  }

  fds[0].fd = req.fd; // Copy file descriptor to fd in struct pollfd
  fds[0].events = POLLIN; // Event to monitor: data available to read
  fds[0].revents = 0; // Reset revents before monitoring GPIO lines

  std::cout << "Monitoring button s for level events...\n";
  

  // Read events on all GPIO lines infinitely
  while (true) {
    // Use poll() to monitor all file descriptors
    int ret_val = poll(fds, 1, POLL_TIMEOUT_MS);
    // std::cout << "Waiting...\n";
    if (ret_val < 0) { // Handle error
      perror("poll()");
      close(req.fd);
      close(fd);
      return EXIT_FAILURE;
    }


    // Read all file descriptors for edge events in a loop
    if (fds[0].revents & POLLIN) { // Check if data is available
      ssize_t bytes = read(fds[0].fd, &data, sizeof(data));
      if (bytes != sizeof(data)) { perror("read"); } // Handle error
      
      for(int i = 0; i < (int)req.lines; i++){
        if(data.values[i] == 0){std::cout << "\nButton " << i << ": is pressed"; }
      }
    } // End of if (fds[i].revents & POLLIN)
  } // End of while loop

  
  close(req.fd);
  
  close(fd);
  return EXIT_SUCCESS;
}
