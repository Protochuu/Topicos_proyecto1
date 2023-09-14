#include <vector>
using namespace std;

class CountMinSketch{
    private:
    vector<vector<int>> freq_matrix;
    int row_len;
    int col_len;

    public:
    //initialization
    CountMinSketch(int d, int w){
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

    void increment_count(int element){
        for(int i = 0; i < this->col_len; i++){
            freq_matrix[i][hash(element, this->row_len, i)] ++;
        }
    }

    int retrieve_count(int element){
        int min_value = freq_matrix[0][hash(element, this->row_len, 0)];
        for(int i = 0; i < this->col_len; i++){
            int current_count = freq_matrix[i][hash(element, this->row_len, i)];
            if  (current_count < min_value){
                min_value = current_count;
            }
        }
        return min_value;
    }

    //test hash function
    int hash(int key, int len, int seed){
        return key%len;
    }

};