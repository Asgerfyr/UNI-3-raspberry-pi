#include <iostream>
#include <cmath>


int main(int argc, char* argv[]){
    unsigned long long cnt = 0;
    for(unsigned long long k = 0; k < 100000000000;k++){
      unsigned long long l = sqrt(k);
      if (l%2==0) { ++cnt;}
    }
    std::cout << cnt;
}