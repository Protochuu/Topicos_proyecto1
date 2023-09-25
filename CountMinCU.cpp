#include <iostream>
#include <vector>
#include <string>

#include "CountMinCU.h"
#include "MurMurhash3.h"

uint64_t CountMinCU::hash(std::string key, int seed){
	uint64_t out;
		
	MurmurHash3_x64_128(key.c_str(), key.size(), seed, &out);

	return out % cols;
}

// CountMinCU::CountMinCU(int d, int w){
// 	this->freqs = std::vector<std::vector<uint64_t>>(d, std::vector<uint64_t>(w, 0));
// 
// 	this->rows = d;
// 	this->cols = w;
// }

void CountMinCU::increment_count(std::string element){
	int min_i = 0;
	int min_j = hash(element, 0);

	for(int i = 0; i < this->cols; i++){
		uint64_t d = hash(element, i);

		if(freqs[i][d] < freqs[min_i][min_j]){
			min_i = i;
			min_j = d;
		}
	}

	freqs[min_i][min_j]++;
}

uint64_t CountMinCU::retrieve_count(std::string element){
	uint64_t min_value = freqs[0][this->hash(element, 0)];

	for(int i = 0; i < this->cols; i++)
		int count = freqs[i][this->hash(element, i)];

		if (count < min_value){
			min_value = count;
		}
	}

	return min_value;
}

