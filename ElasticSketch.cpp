#include <string>
#include <cstring>

#include "CountMinCU.h"
#include "ElasticSketch.h"
#include "MurmurHash3.h"

ElasticSketchBucket *ElasticSketch::get_bucket(std::string element){
    uint64_t out;

    char *buffer = new char[element.size() + 1];
    strcpy(buffer, element.c_str());

    MurmurHash3_x64_128(buffer, element.size(), 0, &out);

    uint64_t hash_index = out % (this->w);

    ElasticSketchBucket *bucket = &hash_table[hash_index];

    return bucket;
}

void ElasticSketch::increment_count(const std::string element){
    int threshold = 8;

    ElasticSketchBucket *bucket = get_bucket(element);

    if (bucket->is_empty){
        bucket->element= element;
        bucket->positive_count = 1;
        bucket->is_empty = false;
    } 
    else if (bucket->element == element){
        bucket->positive_count += 1;
    }
    else {
        bucket->negative_count += 1;
        double ratio = bucket->negative_count/bucket->positive_count;
        if (ratio < threshold){
            count_min_sketch.increment_count(bucket->element);
        }
        else {
            count_min_sketch.set_count(bucket->element,bucket->positive_count);
            bucket->element = element;
            bucket->positive_count = 1;
            bucket->replaced = true;
            bucket->negative_count = 1;
        }
    }
}

uint64_t ElasticSketch::retrieve_count(std::string element){
    ElasticSketchBucket *bucket = get_bucket(element);
    if ((bucket->is_empty) && (bucket->element == element)){
        return count_min_sketch.retrieve_count(element);
    }
    else if(bucket->replaced){
        return bucket->positive_count + count_min_sketch.retrieve_count(element);
    }
    else{
        return bucket->positive_count;
    }
}
