#include <iostream>

using namespace std;


#include "ppm.h"
#include "array2d.h"
#include "vec3.h"



int main (int argc, char *argv[]) {
    int imageWidth = 0;
    int imageHeight = 0;

    int imageWidth1 = 0;
    int imageHeight1 = 0;
    
    float* array = image::ReadPPM("Image01.ppm", &imageWidth, &imageHeight);
    float* array1 = image::ReadPPM("Image03.ppm", &imageWidth1, &imageHeight1);
    bool a = image::WritePPM(array, imageWidth, imageHeight, "Image02.ppm");
    bool b = image::WritePPM(array, imageWidth1, imageHeight1, "Image04.ppm");
    std::cout <<a << std::endl;
    
    std::vector<Vec3<float>> buffer;
    for (int i = 0; i < imageWidth*imageHeight*3; i=i+3)
    {
        buffer.push_back(Vec3<float>(*(array + i), *(array + i + 1), *(array + i + 2)));
    }

    std::vector<Vec3<float>> buffer1;
    for (int i = 0; i < imageWidth1*imageHeight1*3; i=i+3)
    {
        buffer1.push_back(Vec3<float>((*(array1 + i))*255.F, (*(array1 + i + 1))*255.F, (*(array1 + i + 2))*255.F));
    }

    Array2D<Vec3<float>> aray2dObj(imageWidth, imageHeight, buffer.data());
    Array2D<Vec3<float>> copyObj(imageWidth1, imageHeight1);
    cout << buffer[2][0] << "   " << buffer[2][1] << endl;
    cout << aray2dObj.getRawDataPtr() << "   " << copyObj.getRawDataPtr() << endl;
    copyObj.setData(buffer1.data());
    aray2dObj = copyObj;
    cout << aray2dObj.getRawDataPtr() << "   " << copyObj.getRawDataPtr() << endl;
    for (int j = 0; j < 3; j++)
    {
        for (int i = 0; i < 3; i++)
        {
            cout << aray2dObj(i,j)[0] << " " << aray2dObj(i,j)[1] << " " << aray2dObj(i,j)[2] << "  copy  " << copyObj(i,j)[0] << " " << copyObj(i,j)[1] << " " << copyObj(i,j)[2] <<  endl;
        }
    }
}