#include <MurmurHash3.h>
#include "CountMin.h"

#include <iostream>
#include <fstream>
#include <string>

int main(){
	std::ifstream dataset;

	dataset.open("Mendeley.txt");

	std::string line;

	while( getline(dataset, line) ){
		std::cout << line << std::endl;
	}

	dataset.close();

	return 0;
}
