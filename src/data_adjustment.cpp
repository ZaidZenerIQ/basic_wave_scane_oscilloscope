#include "data_adjustment.hpp"
#include <cstdlib>
#include <vector>
#include <iostream>
float first_adjustment(float value,int wave_size,int pos){
    float tens = 5;
    if (wave_size==0){
        wave_size=1;
        tens=1;
    }
    if (wave_size<0){
        wave_size=std::abs(wave_size);
        tens = float(wave_size)/10;
        //std::cout<<">>>>>"<<tens<<'\n';
    }
    return (250.0-pos) - (value)*(wave_size*tens); //!
}

std::vector<float> dump_Interpolator(std::vector<float> input){
    std::vector<float> output;
    return output;
}

