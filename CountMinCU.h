#include <iostream>
#include <vector>
#include <string>

#ifndef COUNTMINCU
#define COUNTMINCU

class CountMinCU {
private:
	std::vector<std::vector<uint64_t>> freqs;
	uint32_t rows;
	uint32_t cols;

	uint64_t hash(std::string key, int seed);
public:
	CountMinCU(int d, int w);

	void increment_count(int element);

	uint64_t retrieve_count(int element);
};

#endif