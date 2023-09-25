#include <vector>
#include <string>

using namespace std;
#ifndef CountMin
#define CountMin

class CountMinSketch{
    private:
    vector<vector<int>> freq_matrix;
    int row_len;
    int col_len;

    public:
    CountMinSketch(int d, int w);
    void increment_count(string element);
    int retrieve_count(string element);
    int hash(string key, int seed);
};
#endif