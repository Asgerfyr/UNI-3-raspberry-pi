#include <iostream>


int main(){

	int num{};

	std::cin >> num;

	for (int i = 0; i < num;i++){
		for (int j = i; j > 0; j-=1){
			if(j%2==0){
				std::cout << "\33[31m";
			}else{
				std::cout << "\33[32m";
			}
			std::cout << "*";
		}
		std::cout << std::endl;
	}

	return 0;
}
