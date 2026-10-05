#include <iostream>

// "fcntl.h" defines open() and flags
#include <fcntl.h>
// "unistd.h" defines read(),write() and close()
#include <unistd.h>

int main(int argc, char* argv[]){
    
    int fd{};
    fd = open("./out", O_WRONLY|O_CREAT|O_APPEND,S_IRUSR|S_IWUSR|S_IXUSR);

    if(fd == -1){
        perror("We dident open the bitch, life is ass, failing");
        return EXIT_FAILURE;
    }


    char str[] = "Hello man!!\n";

    ssize_t res{};
    
    res = write(fd, str, sizeof(str)-1);

    if(res == -1){
        perror("We failed to write, not good");

    }else if(res < sizeof(str)-1){
        perror("We did not write everything, but this is fine 🔥🔥");
    }



    res = close(fd);

    if(res == -1){
        perror("We failed to close, ur file is fucked, i will fix it");
        return EXIT_FAILURE;
    }


    std::cout << "write did good 👍" << std::endl;


    fd = open("./out", O_RDONLY);

    if(fd == -1){
        perror("We dident open the bitch, life is ass, failing");
        return EXIT_FAILURE;
    }


    char buf[sizeof(str)];
    
    res = read(fd, buf, sizeof(buf)-1);

    if(res == -1){
        perror("We failed to read, not good");

    }else if(res < sizeof(buf)-1){
        perror("We did not read everything, but this is fine 🔥🔥");
    }


    std::cout << buf << std::endl;

    res = close(fd);

    if(res == -1){
        perror("We failed to close, ur file is fucked, i will fix it");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}