#include <string>
#include <array>
#include "CountMinCU.h"


struct ElasticSketchBucket {
	std::string element;
	uint64_t positive_count = 0;
	bool replaced = false;
	bool is_empty = true;
	uint64_t negative_count = 0;
};

template<size_t W, size_t D>
class ElasticSketch {
private:
	std::array<ElasticSketchBucket, B> hash_table;
	ElasticSketchHashTable<std::string, ElasticSketchBucket, W> table;
	CountMinCU<W, D> count_min_sketch;

public:
	void increment_count(std::string element);
	uint64_t retrieve_count(std::string element);
	ElasticSketchBucket *get_bucket(std::string element);
};


