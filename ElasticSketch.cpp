#include <string>

#include "CountMinCU.h"
#include "ElasticSketch.h"

using namespace std;

template <size_t B>
void ElasticSketchHashTable<B>::insert(string element){
    
    int out;
    int threshold = 8;
    MurmurHash3_x64_128(element.c_str(), element.size(), 0, &out);
    int hash_index = out%B;
    if (hash_table.is_empty) {
        hash_table[hash_index] = element.element;
        hash_table.positive_count = 1;
    } 
    else{
        if (hash_table.element == element.element){
            hash_table.positive_count += 1;
        }
        else {
            hash_table.negative_count += 1;
            ratio = hash_table.negative_count/hash_table.positive_count;
            if (ratio < threshold){
                c.increment_count
            }
        }
    }


}

template <size_t W, size_t D>
void ElasticSketch<W, D>::increment_count(string element){
        int out;
    int threshold = 8;
    MurmurHash3_x64_128(element.c_str(), element.size(), 0, &out);
    int hash_index = out%B;
    if (hash_table.is_empty) {
        hash_table[hash_index] = element.element;
        hash_table.positive_count = 1;
    } 
    else{
        if (hash_table.element == element.element){
            hash_table.positive_count += 1;
        }
        else {
            hash_table.negative_count += 1;
            ratio = hash_table.negative_count/hash_table.positive_count;
            if (ratio < threshold){
                count_min_sketch.increment_count(hash_table.element);

            }
        }
    }

}

template <size_t W, size_t D>
uint64_t ElasticSketch<W, D>::retrieve_count(string element){

}
