#include <iostream>
#include <fstream>
#include <string>


namespace image
{
    float * ReadPPM(const char * filename, int * w, int * h )
    {
        std::string format;
        int width;
        int height;
        int maxNumberOfPixel;
        int arraySize;
        float * arrayData;                                                                      //array whick hold the input data
        std::ifstream inputFile(filename, std::ios::in | std::ios::binary);

        if (!inputFile.is_open())                                                               //check if file is open
        {
            std::cerr << "Could not open the file for reading " << filename << std::endl;        //print error message,close stream and return null
            inputFile.close();
            return nullptr;
        }
        else
        {
            inputFile >> format;
            if (format.compare("P6") != 0)                                                      //check format if it is P6,if not : return null
            {
                std::cerr << "file has wrong format" << filename << std::endl;                  //print error message,close stream and return null
                inputFile.close();
                return nullptr;
            }
            else
            {
                inputFile >> width >> height >> maxNumberOfPixel;                               //read width,height and range and check them
                if ((width < 0) || (height < 0))
                {
                    std::cerr << "Dimensions of image can't be negative numbers" << std::endl;  //print error message,close stream and return null
                    inputFile.close();
                    return nullptr;
                }
                else if ((maxNumberOfPixel < 0) || (maxNumberOfPixel > 255))
                {
                    std::cerr << "Wrong max number of pixels of format P6" << std::endl;        //print error message,close stream and return null
                    inputFile.close();
                    return nullptr;
                }
                else
                {
                    arraySize = width*height*3;                                                 //size of data whick image contains are X*Y(R,B,G)
                    (*w) = width;
                    (*h) = height;
                    
                    inputFile.ignore(1, '\n');                                                  //if header and data are in same line extract 1 char (space)
                                                                                                //if header and data are in different line extract '\n'
                    unsigned char* tempData = new unsigned char [arraySize];                    //store data as chars

                    arrayData = new float [arraySize];                                          //store the data which we will return...we should make the data float type
                    inputFile.read(reinterpret_cast<char *>(tempData), arraySize);

                    for (int i = 0; i < arraySize; ++i) { 
                        *(arrayData + i) = *(tempData + i)/ 255.f;                              //make the data float numbers range [0,1]
                    }
                    delete[] tempData;//delete temp array from memory
                }
            }
        }
        if (inputFile.peek() != EOF || inputFile.fail() == true)                                //check if any error occurs while we were reading drom file
        {
            std::cerr << "Could not read all data of file...Check if dimensions or max number of pixels are missing or dimensions ara wrong" << std::endl;       //print error message,close stream and return null
            inputFile.close();
            return nullptr;
        }
        inputFile.close();                                                                      //close stream
        return arrayData;                                                                       //return the pointer which show the start of array
    }

    bool WritePPM(const float * data, int w, int h, const char * filename)
    {
        std::ofstream outputFile(filename, std::ios::out | std::ios::binary | std::ios::trunc);
        if (!outputFile.is_open())                                                              //check if file is open
        {
            std::cerr << "Could not open the file for writting " << filename << std::endl;       //print error message
            outputFile.close();                                                                 //close stream and return false
            return false;
        }
        else
        {
            outputFile << "P6 " << w << " " << h << " 255\n";
            char* tempData = new  char [w * h * 3];
            for (int i = 0; i < w * h * 3; ++i) {
                *(tempData + i) = (*(data + i)*255.f);                                          //make the data chars 0-255 again
            }
            
            outputFile.write(tempData, w * h * 3);                                              //write data
            outputFile.close();                                                                 //close stream
            delete[] tempData;                                                                  //delete temp array and return true
            if (outputFile.fail())                                                              //check if any error occurs while we were writing the data
            {
                std::cerr << "Could not write data" << std::endl;                               //print error message
                outputFile.close();                                                             //close stream and return false
                return false;
            }
            return true;
        }
    }
} //namespace image