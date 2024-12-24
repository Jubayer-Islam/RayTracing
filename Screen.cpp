


#include "Screen.hpp"

#include <iostream>
#include <fstream>
#include "lodepng.h"

void printHeader(std::ofstream& ppmFile, const unsigned int width, const unsigned int height) {
    ppmFile << "P3" << std::endl; // Magic Number, we're doing a pixelmap here
    ppmFile << width << " " << height << std::endl;   // We need to specify width/height
    ppmFile << "255" << std::endl;    // Maximum value
}


void write_color(std::ostream& out, const color& pixel_color) {
    auto r = pixel_color.x();
    auto g = pixel_color.y();
    auto b = pixel_color.z();

    // Translate the [0,1] component values to the byte range [0,255].
    int rbyte = int(255.999 * r);
    int gbyte = int(255.999 * g);
    int bbyte = int(255.999 * b);

    // Write out the pixel color components.
    out << rbyte << ' ' << gbyte << ' ' << bbyte << '\n';
}

void Screen::printScreenToPPMFile(std::ofstream& ppmFile) {
    printHeader(ppmFile, _width ,_height);
    for( int y = 0; y < _height; y++) {
        for( int x = 0; x < _width; x++) {
            write_color(ppmFile, _data[_width*y + x]);
        }
        ppmFile << "\n";
    }
}

void Screen::setPixel(uint64_t  x, uint64_t  y, vec3 c){
    _data[_width*y + x] = c;
}
uint64_t  Screen::getWidth() const{
    return _width;
}
uint64_t  Screen::getHeight() const{
    return _height;
}
void Screen::clear(){
    for(auto& i: _data){
        i = {0,0,0};
    }
}

void Screen::saveAsPPM(const char *filename){
    std::ofstream ppmFile(filename);
    printScreenToPPMFile(ppmFile);
}

void Screen::saveAsPNG(const char *filename) {
    std::vector<unsigned char> temp_data;
    for(auto pixel: _data) {
        temp_data.push_back(int(255.999 * pixel.x()));
        temp_data.push_back(int(255.999 * pixel.y()));
        temp_data.push_back(int(255.999 * pixel.z()));
        temp_data.push_back(int(255.0));
    }
    unsigned error = lodepng::encode(filename, temp_data, _width, _height);
    std::cout << error << std::endl;

}
