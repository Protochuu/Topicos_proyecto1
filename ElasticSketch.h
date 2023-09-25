#include <string>

#include "etl/unordered_map.h"
#include "CountMinCU.h"

struct ElasticSketchBucket {
	std::string element;
	uint64_t positive_count = 0;
	bool replaced = false;
	uint64_t negative_count = 0;
};

class ElasticSketch {
private:
	std::unordered_map<std::string, ElasticSketchBucket, 0> table;
	CountMinCU count_min_sketch;

public:
	void increment_count(std::string element);
	uint64_t retrieve_count(std::string element);
};
