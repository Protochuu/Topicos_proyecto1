#include "CountMin.h"
#include "MurmurHash3.h"

using namespace std;


CountMinSketch::CountMinSketch(int d, int w){
    for(int i = 0; i < d; i++){
        vector <int> row_matrix;
        for(int j = 0; j < w; j++){
            row_matrix.push_back(0);
        }
        freq_matrix.push_back(row_matrix);
    }

    this->row_len = w;
    this->col_len = d;
}

void CountMinSketch::increment_count(string element){
    for(int i = 0; i < this->col_len; i++){
        freq_matrix[i][hash(element, i)] ++;
    }
}

int CountMinSketch::retrieve_count(string element){
    int min_value = freq_matrix[0][hash(element, 0)];
    for(int i = 0; i < this->col_len; i++){
        int current_count = freq_matrix[i][hash(element, i)];
        if  (current_count < min_value){
            min_value = current_count;
        }
    }
    return min_value;
}

    //test hash function
int CountMinSketch::hash(string key, int seed){
    int out;
    MurmurHash3_x64_128(key.c_str(), key.size(), seed, &out);
    return out%row_len;
}