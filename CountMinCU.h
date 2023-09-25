#include <iostream>
#include <vector>
#include <string>

#ifndef COUNTMINCU
#define COUNTMINCU

template <size_t W, size_t D>
class CountMinCU {
private:
	std::vector<std::vector<uint64_t>> freqs;
	uint32_t rows = D;
	uint32_t cols = W;

	uint64_t hash(std::string key, int seed);
public:
	void increment_count(int element);
	uint64_t retrieve_count(int element);
    void set_count(std::string element, uint64_t count);
};

#endif
