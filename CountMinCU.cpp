#include <iostream>
#include <vector>
#include <string>

#include "CountMinCU.h"
#include "Murmurhash3.h"

template <size_t W, size_t D>
uint64_t CountMinCU<W, D>::hash(std::string key, int seed){
	uint64_t out;
		
	MurmurHash3_x64_128(key.c_str(), key.size(), seed, &out);

	return out % cols;
}

template <size_t W, size_t D>
void CountMinCU<W, D>::increment_count(std::string element){
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

template <size_t W, size_t D>
void CountMinCU<W, D>::set_count(std::string element, uint64_t count) {
    int min_i = 0;
    int min_j = hash(element, 0);

    for(int i = 0; i < this->cols; i++){
        uint64_t d = hash(element, i);

        if(freqs[i][d] < freqs[min_i][min_j]){
            min_i = i;
            min_j = d;
        }
    }

    freqs[min_i][min_j] = count;
}

template <size_t W, size_t D>
uint64_t CountMinCU<W, D>::retrieve_count(std::string element){
	uint64_t min_value = freqs[0][this->hash(element, 0)];

	for(int i = 0; i < this->cols; i++){
		int count = freqs[i][this->hash(element, i)];

		if (count < min_value){
			min_value = count;
		}
	}

	return min_value;
}

