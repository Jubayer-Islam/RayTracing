

#ifndef SCREEN_HPP
#define SCREEN_HPP

#include <cstdint>
#include <vector>
#include "Vector3.hpp"



using color = vec3;

class Screen{
    uint64_t _width;
    uint64_t _height;
    std::vector<color> _data;
public:
    Screen():_width(1024), _height(1024){
        _data.resize(_width*_height);
    }
    Screen(uint64_t  width, uint64_t  height):_width(width), _height(height){
        _data.resize(width * height);
    }
    void setPixel(uint64_t  x, uint64_t  y, vec3 c);
    uint64_t getWidth() const;
    uint64_t getHeight() const;
    void printScreenToPPMFile(std::ofstream& ppmFile);
    void clear();
    void saveAsPPM(const char *filename);
    void saveAsPNG(const char *filename);
};

#endif //SCREEN_HPP
