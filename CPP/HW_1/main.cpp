#ifndef __PROGTEST__
#include <cstdio>
#include <cstdlib>
#include <cstdint>
#include <cstring>
#include <cassert>
#include <cmath>
#include <cctype>
#include <climits>

#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <list>
#include <algorithm>
#include <functional>
#include <memory>
using namespace std;

const uint16_t ENDIAN_LITTLE = 0x4949;
const uint16_t ENDIAN_BIG    = 0x4d4d;

#endif /* __PROGTEST__ */

unsigned long int Size;
bool checker_read = true;
bool checker_write = true;
vector<uint8_t> in;
vector<uint8_t> final_array;
uint8_t ** temporary;
bool readHeader(unsigned int *, unsigned int *, unsigned int *, unsigned int *);
vector<uint8_t> readBin(const string&);
void writeBin(const std::string &, const std::vector<uint8_t> &);

bool flipImage ( const char  * srcFileName,
                 const char  * dstFileName,
                 bool          flipHorizontal,
                 bool          flipVertical )
{

    unsigned int width, height, channels, bits, bytes_per_pixel;
    uint8_t tmp;
    checker_read = true;
    checker_write = true;
    // read from file
    in = readBin(srcFileName);
    if(!checker_read) return false;
    //check if endianness is valid
    if((uint16_t)in[0] == 73) {
        if((uint16_t)in[1] != 73) return false;
    } else if((uint16_t)in[0] == 77) {
        if((uint16_t)in[1] != 77) return false;
    } else return false;

    Size = in.size();

    if(!readHeader(&width, &height, &channels, &bits)) return false;

    bytes_per_pixel = (channels * bits) / 8;
    if(bytes_per_pixel * width * height + 8 != Size) return false;

    temporary = (uint8_t **) malloc(height * sizeof(uint8_t *));
    for(unsigned i = 0; i < height; i++)
        temporary[i] = (uint8_t *) malloc(width * bytes_per_pixel * sizeof(uint8_t));

    int counter = 8;
    for(unsigned i = 0; i < height; i++) {
        for(unsigned j = 0; j < width * bytes_per_pixel; j++) {
            temporary[i][j] = in[counter];
            counter++;
        }
    }

    if(flipHorizontal) {
        for(unsigned i = 0; i < height; i++) {
            for(unsigned j = 0; j < width / 2; j++) {
                for(unsigned k = 0; k < bytes_per_pixel; k++) {
                    tmp = temporary[i][k + j * bytes_per_pixel];
                    temporary[i][k + j * bytes_per_pixel] = temporary[i][(width - 1) * bytes_per_pixel - j * bytes_per_pixel + k];
                    temporary[i][(width - 1) * bytes_per_pixel - j * bytes_per_pixel + k] = tmp;
                }
            }
        }
    }

    if(flipVertical) {
        for(unsigned i = 0; i < height / 2; i++) {
            for(unsigned j = 0; j < width * bytes_per_pixel; j++) {
                tmp = temporary[i][j];
                temporary[i][j] = temporary[height - 1 - i][j];
                temporary[height - 1 - i][j] = tmp;
            }
        }
    }

    for(unsigned i = 0; i < 8; i++)
        final_array.push_back(in[i]);

    for(unsigned i = 0; i < height; i++) {
        for(unsigned j = 0; j < width * bytes_per_pixel; j++)
            final_array.push_back(temporary[i][j]);
    }

    for(unsigned i = 0; i < height; i++)
        free(temporary[i]);
    free(temporary);

    writeBin(dstFileName, final_array);
    if(!checker_write) {
        final_array.clear();
        return false;
    }
    final_array.clear();

    return true;

}

#ifndef __PROGTEST__
bool identicalFiles ( const char * fileName1,
                      const char * fileName2 )
{
    vector<uint8_t> vec1 = readBin(fileName1);
    vector<uint8_t> vec2 = readBin(fileName2);
    if(vec1.size() != vec2.size()) {
        cout << "different sizes of files" << endl;
        return false;
    }
    for(unsigned i = 0; i < vec1.size(); i++) {
        if(vec1[i] != vec2[i]) {
            cout << "different values at: " << i << endl;
            return false;
        }
    }
    return true;
}

int main ( void )
{
    //flipImage("in_3167059.bin", "output_extra_deep_shit_00.bin", true, false);
    assert ( flipImage ( "in_3167059.bin", "output_extra_deep_shit_00.bin", true, false )
             && identicalFiles ( "output_extra_deep_shit_00.bin", "ref_3167059.bin" ) );
    /*assert ( flipImage ( "input_00.img", "output_00.img", true, false )
             && identicalFiles ( "output_00.img", "ref_00.img" ) );

    assert ( flipImage ( "input_01.img", "output_01.img", false, true )
             && identicalFiles ( "output_01.img", "ref_01.img" ) );

    assert ( flipImage ( "input_02.img", "output_02.img", true, true )
             && identicalFiles ( "output_02.img", "ref_02.img" ) );

    assert ( flipImage ( "input_03.img", "output_03.img", false, false )
             && identicalFiles ( "output_03.img", "ref_03.img" ) );

    assert ( flipImage ( "input_04.img", "output_04.img", true, false )
             && identicalFiles ( "output_04.img", "ref_04.img" ) );

    assert ( flipImage ( "input_05.img", "output_05.img", true, true )
             && identicalFiles ( "output_05.img", "ref_05.img" ) );

    assert ( flipImage ( "input_06.img", "output_06.img", false, true )
             && identicalFiles ( "output_06.img", "ref_06.img" ) );

    assert ( flipImage ( "input_07.img", "output_07.img", true, false )
             && identicalFiles ( "output_07.img", "ref_07.img" ) );

    assert ( flipImage ( "input_08.img", "output_08.img", true, true )
             && identicalFiles ( "output_08.img", "ref_08.img" ) );

    assert ( ! flipImage ( "input_09.img", "output_09.img", true, false ) );*/

    // extra inputs (optional & bonus tests)
    /*assert ( flipImage ( "extra_input_00.img", "extra_out_00.img", true, false )
             && identicalFiles ( "extra_out_00.img", "extra_ref_00.img" ) );
    assert ( flipImage ( "extra_input_01.img", "extra_out_01.img", false, true )
             && identicalFiles ( "extra_out_01.img", "extra_ref_01.img" ) );
    assert ( flipImage ( "extra_input_02.img", "extra_out_02.img", true, false )
             && identicalFiles ( "extra_out_02.img", "extra_ref_02.img" ) );
    assert ( flipImage ( "extra_input_03.img", "extra_out_03.img", false, true )
             && identicalFiles ( "extra_out_03.img", "extra_ref_03.img" ) );
    assert ( flipImage ( "extra_input_04.img", "extra_out_04.img", true, false )
             && identicalFiles ( "extra_out_04.img", "extra_ref_04.img" ) );
    assert ( flipImage ( "extra_input_05.img", "extra_out_05.img", false, true )
             && identicalFiles ( "extra_out_05.img", "extra_ref_05.img" ) );
    assert ( flipImage ( "extra_input_06.img", "extra_out_06.img", true, false )
             && identicalFiles ( "extra_out_06.img", "extra_ref_06.img" ) );
    assert ( flipImage ( "extra_input_07.img", "extra_out_07.img", false, true )
             && identicalFiles ( "extra_out_07.img", "extra_ref_07.img" ) );
    assert ( flipImage ( "extra_input_08.img", "extra_out_08.img", true, false )
             && identicalFiles ( "extra_out_08.img", "extra_ref_08.img" ) );
    assert ( flipImage ( "extra_input_09.img", "extra_out_09.img", false, true )
             && identicalFiles ( "extra_out_09.img", "extra_ref_09.img" ) );
    assert ( flipImage ( "extra_input_10.img", "extra_out_10.img", true, false )
             && identicalFiles ( "extra_out_10.img", "extra_ref_10.img" ) );
    assert ( flipImage ( "extra_input_11.img", "extra_out_11.img", false, true )
             && identicalFiles ( "extra_out_11.img", "extra_ref_11.img" ) );
    return 0;*/
}
#endif /* __PROGTEST__ */

std::vector<uint8_t> readBin(const std::string& filename) {
    // Open the file in binary mode
    // Notice ORing the flags
    std::ifstream file(filename, std::ios::in | std::ios::binary);
    if(!file.good()) {
        checker_read = false;
        return std::vector<uint8_t>();
    }
    // Check if the file exists
    if (!file.is_open()) {
        checker_read = false;
        // std::cout << "Problem with opening the file '" << filename << "'" << std::endl;
        return std::vector<uint8_t>();
    }

    // Get the size of a file
    file.seekg(0, file.end);
    size_t fileSize = file.tellg();
    file.seekg(0, file.beg);

    if(fileSize == 0) {
        checker_read = false;
        return std::vector<uint8_t>();
    }

    // Allocate appropriate number of elements in the vector
    std::vector<uint8_t> vec(fileSize);

    // Read file to vec.data(), read "fileSize" number of bytes
    file.read(reinterpret_cast<char*>(vec.data()), fileSize);

    if(file.fail())
        checker_read = false;

    if(!file)
        checker_read = false;

    if(vec.empty())
        checker_read = false;

    // Optional, will be handled in ifstream destructor
    // In case we want to reuse the file later (in the same context),
    // we should close the file explicitly.
    file.close();

    // No extra copy will be made, RVO (google it...)
    return vec;
}

void writeBin(const std::string& filename, const std::vector<uint8_t>& vec) {
    // Open the file in binary mode
    std::ofstream file(filename, std::ios::out | std::ios::binary);
    // Check if the file exists
    if (!file.is_open()) {
        checker_write = false;
        //std::cout << "Problem with opening the file '" << filename << "'" << std::endl;
        return;
    }
    // Write vec.data() of "vec.size()" number of bytes
    file.write(reinterpret_cast<const char*>(vec.data()), vec.size());

    if (!file.good()) {
        checker_write  = false;
        // std::cout << "An error has occured" << std::endl;
    }
}

bool readHeader(unsigned int * width, unsigned int * height, unsigned int * channels, unsigned int * bits) {
    uint16_t  format;
    if((uint16_t)in[0] == 73) {
        *width = ((uint16_t) in[3] << 8) + (uint16_t) in[2];
        *height = ((uint16_t) in[5] << 8) + (uint16_t) in[4];
        format = ((uint16_t) in[7] << 8) + (uint16_t) in[6];
    } else {
        *width = ((uint16_t) in[2] << 8) + (uint16_t) in[3];
        *height = ((uint16_t) in[4] << 8) + (uint16_t) in[5];
        format = ((uint16_t) in[6] << 8) + (uint16_t) in[7];
    }

    if(*width == 0 || *height == 0) return false;

    if(((uint16_t)format & 3) == 0) *channels = 1;
    else if(((uint16_t)format & 3) == 2) *channels = 3;
    else if(((uint16_t)format & 3) == 3) *channels = 4;
    else return false;

    if((((uint16_t)format & 28) >> 2) == 0) *bits = 1;
    else if((((uint16_t)format & 28) >> 2) == 3) *bits = 8;
    else if((((uint16_t)format & 28) >> 2) == 4) *bits = 16;
    else return false;

    return true;
}