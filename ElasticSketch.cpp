#include <string>

#include "CountMinCU.h"
#include "ElasticSketch.h"
#include "MurmurHash3.h"

using namespace std;

template <size_t W, size_t D>
ElasticSketchBucket *ElasticSketch<W,D>::get_bucket(string element){
    int out;
    MurmurHash3_x64_128(element.c_str(), element.size(), 0, &out);
    int hash_index = out%W;
    return &hash_table[hash_index];
}

template <size_t W, size_t D>
void ElasticSketch<W, D>::increment_count(string element){
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

template <size_t W, size_t D>
uint64_t ElasticSketch<W, D>::retrieve_count(string element){
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
