#include <iostream>
#include <string>
#include <vector>
#include "ppm.h"
#include "image.h"

using namespace std;
using namespace math;
using namespace image;

    
bool Image::load(const std::string & filename, const std::string & format)
{
    if (filename.find(format) != std::string::npos) {
        if(format.compare("ppm")){
            int imageWidth = 0;
            int imageHeight = 0;

            float* array = ReadPPM(filename.c_str(), &imageWidth, &imageHeight);
            if (array != nullptr){
                for (int i = 0; i < imageWidth*imageHeight*3; i=i+3)
                {
                    buffer.push_back(Vec3<float>(*(array + i), *(array + i + 1), *(array + i + 2)));
                }
                return true;
            }
            else 
            {
                cout << "Cound not load file's data" << endl;
                return false;
            }
        }
        else
        {
            cout << "Format is not ppm" << endl;
            return false;
        }
    }
    else
    {
        cout << "Format is not same with file extension" << endl;
        return false;
    }
        



}




