#include <vector>
#include <string>

#include "Sketch.h"

#ifndef CountMin
#define CountMin

using namespace std;

class CountMinSketch : public Sketch {
private:
    vector<vector<int>> freq_matrix;
    int row_len;
    int col_len;

public:
    CountMinSketch(int d, int w);

    void increment_count(string element);
    uint64_t retrieve_count(string element);

    int hash(string key, int seed);
};
#endif