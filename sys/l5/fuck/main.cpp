#include <iostream>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

void color(const int value);
void message(const int value);

int main(){
    ssize_t pid;
    
    for(int i = 0; i < 100-1; i++){
        pid = fork();
        if(pid == -1){
            perror("fork failed");
            return -1;
        }
        if(pid != 0)break;
    }
    
    
    color(getppid()%4);
    message(getppid());

    ssize_t res{};

    if(pid != 0){
        res = waitpid(pid,NULL,0);
        if(res == -1){
            perror("failed on wait");
            return -1;
        }
    }

    return 0;
}

void color(const int value){
    switch(value) {
        case 0:
            std::cout << "\033[0m"; // Reset color
            break;
        case 1:
            std::cout << "\033[31m"; // Red
            break;
        case 2:
            std::cout << "\033[32m"; // Green
            break;
        case 3:
            std::cout << "\033[34m"; // Blue
            break;
        default:
            std::cout << "\033[0m"; // Reset color for unknown values
            break;
    }
}


void message(const int value){
    switch(value%10) {
        case 0:
            std::cout << "kys" << std::endl; // Reset color
            break;
        case 1:
            std::cout << "hang the child" << std::endl; // Red
            break;
        case 2:
            std::cout << "get him" << std::endl; // Green
            break;
        case 3:
            std::cout << "tax the rich" << std::endl; // Blue
            break;
        case 4:
            std::cout << "higher wages" << std::endl; // Blue
            break;
        case 5:
            std::cout << "equal pay" << std::endl; // Blue
            break;
        case 6:
            std::cout << "end slavery" << std::endl; // Blue
            break;
        case 7:
            std::cout << "get me free" << std::endl; // Blue
            break;
        case 8:
            std::cout << "child lives matter" << std::endl; // Blue
            break;
        case 9:
            std::cout << "end his live" << std::endl; // Blue
            break;
        default:
            std::cout << ""; // Reset color for unknown values
            break;
    }
}