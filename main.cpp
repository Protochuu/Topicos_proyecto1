#include <iostream>
#include <cmath>
#include <fstream>
#include <string>
#include <unordered_map>
#include <utility>

#include "CountMin.h"
#include "ElasticSketch.h"
#include "Sketch.h"
#include "MurmurHash3.h"


void increment_real_count(std::unordered_map<std::string, int> &count, const std::string &element){
    if(count.find(element) == count.end()) {
        count[element] = 1;
    } else {
        count[element]++;
    }
}

std::pair<double, double> calculate_error(Sketch &sketch_count){
    std::ifstream dataset;
    std::string line;

    dataset.open("Mendeley.txt");

    std::unordered_map<std::string, int> real_count;

    while( getline(dataset, line) ){
        sketch_count.increment_count(line);
        increment_real_count(real_count, line);
    }

    double average_absolute_error = 0;
    double average_relative_error = 0;

    for(auto &element : real_count){
        double difference = std::abs(static_cast<double>(sketch_count.retrieve_count(element.first))
                                     - real_count[element.first]);

        average_absolute_error += difference;
        average_relative_error += difference / real_count[element.first];
    }

    average_relative_error /= real_count.size();
    average_absolute_error /= real_count.size();

    dataset.close();

    return std::make_pair(average_relative_error, average_absolute_error);
}

int main(){
    auto upper = 8192;

//    for(int w = 1024; w <= upper; w = w * 2){
//        auto sketch = ElasticSketch(4, w);
//        auto error = calculate_error(sketch);
//
//        std::cout << "ElasticSketch W: " << w << " D: " << 4 << " ERM: " << error.first << " EAM " << error.second << std::endl;
//    }

//    for(int w = 1024; w <= upper; w = w * 2){
//        auto sketch = CountMinCU(4, w);
//        auto error = calculate_error(sketch);
//
//        std::cout << "CountMinCU W: " << w << " D: " << 4 << " ERM: " << error.first << " EAM " << error.second << std::endl;
//    }

    for(int w = 1024; w <= upper; w = w * 2){
        auto sketch = CountMinSketch(4, w);
        auto error = calculate_error(sketch);

        std::cout << "CountMinSketch W: " << w << " D: " << 4 << " ERM: " << error.first << " EAM " << error.second << std::endl;
    }

	return 0;
}
