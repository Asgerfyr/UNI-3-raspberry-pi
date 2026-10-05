#include <iostream>
#include <fstream>
#include <string>
#include <thread>
#include <fcntl.h>
#include <unistd.h>
#include <poll.h>


#include <csignal>

volatile sig_atomic_t running = 1;

void handle_sigint(int)
{
    running = 0;
}


int main() {
    std::thread::id id = std::this_thread::get_id(); // Get unique thread ID

    int fd = open("testfifo",O_RDONLY);
    if(fd == -1){
        perror("failed to open");
        return -1;
    }

    struct pollfd pfd{};
    pfd.fd = fd;
    pfd.events = POLLIN;

    char buffer[1];
    int ret{};
    
    while(running){

        ret = poll(&pfd, 1, 100);

        if(ret > 0 && (pfd.revents & POLLIN)){
            int bites = read(fd,buffer,sizeof(buffer));
            if(bites != sizeof(buffer)){
                close(fd);
                perror("failed to read");
                return -1;
            }
            std::cout << buffer[0];
        }

    }

    int res = close(fd);
    if(fd == -1){
        perror("failed to close");
    }

    /* [Open file 'testfifo' using std::ifstream] */
    /* [Do forever]
    /*  [Read line from file with std::getline] */
    /*  [Print 'id' and line using std::cout] */

    return 0;
}