#include "SSD1306.hpp"
#include <unistd.h>
#include <cstdlib>
#include <ctime>
#include <iostream>

int main(int argv, char* argc[]) {
  // Create instance of SSD1306 class
  SSD1306 oled(I2C_DEV, SSD1306_ADDR);

  // Open I2C device
  if (oled.openI2C() < 0)
    exit(EXIT_FAILURE);

  // Initialize OLED screen
  oled.init();
  usleep(100000);

  // Clear OLED screen
  oled.clear();
  usleep(100000);
  
  oled.drawBox(5,5,10,10);
  
  usleep(500000);
  // Close I2C device
  oled.closeI2C();
  
  // Exit application
  return EXIT_SUCCESS;
}
