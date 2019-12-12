#include <iostream>
#include <fstream>
#include <string>


#define READ
#define WRITE

namespace image
{
#ifdef READ

    float * ReadPPM(const char * filename, int * w, int * h )
    {
        std::string format;
        int width;
        int height;
        int maxNumberOfPixel;
        int arraySize;
        float * arrayData;
        std::ifstream inputFile(filename, std::ios::in | std::ios::binary);

        //check if file is open
        if (!inputFile.is_open())
        {
            std::cerr << "Could not open the file for reading" << filename << std::endl;
            return nullptr;
        }
        else
        {
            inputFile >> format;
            if (format.compare("P6") != 0)//check format if it is P6,if not : return null
            {
                std::cerr << "file has wrong format" << filename << std::endl;
                return nullptr;
            }
            else
            {
                //read width,height and range and check them
                inputFile >> width >> height >> maxNumberOfPixel;
                if ((width < 0) || (height < 0))
                {
                    std::cerr << "Dimensions of image can't be negative numbers" << std::endl;
                    return nullptr;
                }
                else if ((maxNumberOfPixel < 0) || (maxNumberOfPixel > 255))
                {
                    std::cerr << "Wrong max number of pixel of format P6" << std::endl;
                    return nullptr;
                }
                else
                {
                    arraySize = width*height*3;//size of data whick image contains are X*Y(R,B,G)
                    (*w) = width;
                    (*h) = height;
                    
                    inputFile.ignore(256, '\n');//ignone lines if between data and header there are empty lines
                    unsigned char* tempData = new unsigned char [arraySize];//store data as chars

                    arrayData = new float [arraySize];//store the data which we will return...we should make the data float type

                    inputFile.read(reinterpret_cast<char *>(tempData), arraySize);

                    for (int i = 0; i < arraySize; ++i) { 
                        *(arrayData + i) = *(tempData + i)/ 255.f;//make the data float numbers range [0,1]
                    }
                    
                    delete[] tempData;//delete temp array from memory
                }
            }
        }
        inputFile.close();
        return arrayData;//return the pointer which show the start of array
    }
#endif
#if defined WRITE
    bool WritePPM(const float * data, int w, int h, const char * filename)
    {
        std::ofstream outputFile(filename, std::ios::out | std::ios::binary | std::ios::trunc);
        if (!outputFile.is_open())
        {
            std::cerr << "Could not open the file for writting" << filename << std::endl;
            return false;;
        }
        else
        {
            outputFile << "P6 " << w << " " << h << " 255\n";
            char* tempData = new  char [w * h * 3];
            for (int i = 0; i < w * h * 3; ++i) { 
                *(tempData + i) = (*(data + i)*255.f);//make the data 0-255 again
            }
            
            outputFile.write(tempData, w * h * 3);
            outputFile.close();
            delete[] tempData;
            return true;
        }
    }
#endif
} //namespace image