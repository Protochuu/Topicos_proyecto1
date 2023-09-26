#include <string>
#include <array>
#include "CountMinCU.h"

#ifndef ELASTIC_SKETCH
#define ELASTIC_SKETCH

struct ElasticSketchBucket {
	std::string element;
	uint64_t positive_count = 0;
	bool replaced = false;
	bool is_empty = true;
	uint64_t negative_count = 0;
};

class ElasticSketch : public Sketch {
private:
    std::vector<ElasticSketchBucket> hash_table;
	CountMinCU count_min_sketch;

    int w;

public:
    ElasticSketch(int d, int w) {
        this->count_min_sketch = CountMinCU(d, w);
        this->hash_table = std::vector<ElasticSketchBucket>(w, ElasticSketchBucket{});
        this->w = w;
    }

	void increment_count(std::string element);
	uint64_t retrieve_count(std::string element);
	ElasticSketchBucket *get_bucket(std::string element);
};

#endif