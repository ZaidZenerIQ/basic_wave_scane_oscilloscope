#include "data_calc.hpp"

float clac_mean(std::vector<float> vec){
    float carry = 0;
    for(float v : vec)carry+=v;
    return carry/vec.size();
}