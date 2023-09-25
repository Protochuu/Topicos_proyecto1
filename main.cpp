#include <MurmurHash3.h>
#include "CountMin.h"

#include <iostream>

int main(){
	const char *key = "Hola";

	uint64_t out;

	MurmurHash3_x64_128(key, 4, 0, &out);

	std::cout << out;
	
	return 0;
}
