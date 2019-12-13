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
    Image::Image(unsigned int width, unsigned int height):Array2D<Vec3<float>>(width, height)
    {}

    bool Image::load(const std::string & filename, const std::string & format)
    {
        if (filename.find(format) != std::string::npos) {
            if(format.compare("ppm") == 0){

                float* array = ReadPPM(filename.c_str(), (int*) &width, (int*) &height);
                if (array != nullptr){
                    for (int i = 0; i < width*height*3; i=i+3)
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
    bool Image::save(const std::string & filename, const std::string & format)
    {
        if (buffer.empty()) return false;

		const char *p_path = filename.c_str();
		if (format == "ppm")
			return WritePPM((float *)buffer.data(), width, height, p_path);
		else
		return false;
    }


}//end namespace 

