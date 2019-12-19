#include <iostream>
#include <string>
#include <vector>
#include "ppm.h"
#include "image.h"
#include "vec3.h"

using namespace std;
using namespace math;


namespace image
{
    //Default constructor without arguments set all 0
    Image::Image(unsigned int width, unsigned int height):Array2D<Vec3<float>>(width, height)
    {
        #ifdef DEBUG
            cout << "Default constructor of Image called" << endl;
        #endif
    }

    //Copy constructor
    Image::Image(const Image &src):Array2D<Vec3<float>>(src)
    {
        #ifdef DEBUG
            cout << "Copy constructor of Image called" << endl;
        #endif
    }

    //destructor
    Image::~Image()
    {
        #ifdef DEBUG
            cout << "Destructor delete an Image" << endl;
        #endif
    }

    bool Image::load(const std::string & filename, const std::string & format)
    {
        if (filename.find(format) != std::string::npos) {                                                   //check if filename contains given format
            if(format.compare("ppm") == 0){                                                                 //check if format is ppm

                float* array = ReadPPM(filename.c_str(), (int*) &width, (int*) &height);                    //if both of above statements are true then read the file and save the data
                if (array != nullptr){                                                                      //if the file had data
                    buffer.clear();                                                                         //we use clear because image could have data inside
                    for (int i = 0; i < width*height*3; i=i+3)                                              //for all triple of colors
                    {
                        buffer.push_back(Vec3<float>(*(array + i), *(array + i + 1), *(array + i + 2)));    //load every pixel in Image's buffer
                    }
                    delete array;                                                                           //delete array 
                    return true;                                                                            //return true load was successful
                }
                else 
                {
                    cerr << "Cound not load file's data" << endl;                                           //print error message return false
                    return false;
                }
            }
            else
            {
                cerr << "Format is not ppm" << endl;                                                        //print error message return false
                return false;
            }
        }
        else
        {
            cerr << "Format is not same with file extension" << endl;                                       //print error message return false
            return false;
        }
    }

    bool Image::save(const std::string & filename, const std::string & format)
    {
        if (filename.find(format) != std::string::npos) {                                                   //check if filename contains given format
            if(format.compare("ppm") == 0){                                                                 //check if format is ppm
                return WritePPM((float*)buffer.data(), width, height, filename.c_str());
            }
            else
            {
                cerr << "Format is not ppm" << endl;                                                        //print error message return false
                return false;
            }
        }
        else
        {
            cerr << "Format is not same with file extension" << endl;                                       //print error message return false
            return false;
        }
    }


}//end namespace 

