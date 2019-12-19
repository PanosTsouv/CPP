

#include <iostream>
#include <cstring>
#include "ppm.h"
#include "array2d.h"
#include "vec3.h"
#include "image.h"
#include "Filter.h"

using namespace math;
using namespace std;
using namespace image;

bool isPositiveNumber(const std::string& s); //declaration(implementation is at the end)
bool isIntegerNumber(const std::string& s); //declaration(implementation is at the end)
bool isNumber(const std::string& s);        //declaration(implementation is at the end)

int main (int argc, char *argv[]) {
    
    string imageFile = argv[argc-1];
    bool atLeastOneFilter = true;                                       //flag which check if user's input has at least one filter
    int current = 1;                                                    //cmd argument start from 1,ignore main program
    int imageWidth = 0;                                                 //imageWidth
    int imageHeight = 0;                                                //ImageHeight
    image::Image *inputImage = new Image(imageWidth,imageHeight);

    if (imageFile.find(".") != std::string::npos)
    {
        if ((*inputImage).load(imageFile,"ppm") == true)                //check load of image
        {
            cout << "Load was successful" << endl;
        }
        else
        {
            cerr << "Fail to load the Image" << endl;                   //print error message and delete Image
            delete inputImage;
            exit(0);
        }
    }
    else
    {
        cerr << "The last argument is not imageFile" <<endl;            //print error message
        exit(0);
    }
    
    while (current < argc-1)                                            //exit loop if current show the last cmd argument
    {
        atLeastOneFilter = false;                                       //make this variable false so we have at least one filter
        if(strcmp(argv[current], "-f") == 0)                            //check if filter start with -f
        {
            #ifdef DEBUG
                cout << "Filter detected" << endl;
            #endif
            current++;                                                  //current show next argument
            if (strcmp(argv[current], "gamma") == 0)                    //check if filter is gamma
            {
                cout << "Filter gamma detected" << endl;
                current++;                                              //current show next cmd argument
                if (isPositiveNumber(argv[current]) && atof(argv[current]) >= 0.5 && atof(argv[current]) <= 2.0)        //check if gamma filter's argument is a positive float number between 0.5-2
                {
                    #ifdef DEBUG
                        cout << "Gamma's number detected" << endl;
                    #endif
                    Filter *fgamma = new FilterGamma(atof(argv[current]));  //filter gamma contains right data so we create a filter gamma
                    *inputImage = *fgamma << *inputImage;                   //apply filter gamma to given image
                    delete fgamma;                                          //delte filter gama
                    current++;                                              //current show next cmd argument
                }
                else
                {
                    delete inputImage;                                      //delete image if an error occurs
                    cerr << "Gamma filter dont have number or number isn't 0.5-2" << endl;     //print error message
                    exit(0);
                }
            }
            else if (strcmp(argv[current], "linear") == 0)                  //check if filter is linear
            {
                cout << "Filter linear detected" << endl;
                int count = 0;                                              //count check if filter has 6 arguments
                float linearNumbers[6];                                     //save arguments inside temp array
                current++;                                                  //current show next cmd argument
                while(count<6)
                {
                    if (isNumber(argv[current]))                            //check if numbers of linear filter are real numbers
                    {
                        #ifdef DEBUG
                            cout << "Linear's number detected" << endl;
                        #endif
                        linearNumbers[count] = atof(argv[current]);         //put current argument inside array
                        count++;                                            //increase count
                        current++;                                          //current show next cmd argument
                    }
                    else
                    {
                        delete inputImage;                                  //delete image if an error occurs
                        cerr << "Linear filter dont have 6 numbers" << endl;//print error message
                        exit(0);
                    }
                }
                Filter *flinear = new FilterLinear(Vec3<float>(linearNumbers[0],linearNumbers[1],linearNumbers[2]),Vec3<float>(linearNumbers[3],linearNumbers[4],linearNumbers[5]));  //if all data of linear filter is right create a linear filter
                *inputImage = *flinear << *inputImage;                      //apply filter to given image
                delete flinear;                                             //delete filter
            }
            else if (strcmp(argv[current], "blur") == 0)                    //check if filter is blur
            {
                cout << "Filter blur detected" << endl;
                current++;                                                  //current show next cmd argument
                if (isIntegerNumber(argv[current]) && (atoi(argv[current]) % 2 == 1))   //check if blur number is integer and odd 
                {
                    #ifdef DEBUG
                        cout << "Blur's number detected" << endl;
                    #endif
                    Filter *fblur = new FilterBlur(atof(argv[current]));    //if filter blur's data is right create a filter blur
                    *inputImage = *fblur << *inputImage;                    //apply filter bluer to given image
                    delete fblur;                                           //delete filter
                    current++;                                              //current show next cmd argument
                }
                else
                {
                    delete inputImage;                                      //delete image if an error occurs
                    cerr << "Blur filter dont have number or number isn't integer positive odd number" << endl; //print error message
                    exit(0);
                }
            }
            else if (strcmp(argv[current], "laplace") == 0)                 //check if filter is laplace
            {
                cout << "Filter laplace detected" << endl;
                current++;                                                  //current show next cmd argument
                Filter *flaplace = new FilterLaplace();                     //if filter laplace's data is right create a filter laplace
                *inputImage = *flaplace << *inputImage;                     //apply filter laplace to given image
                delete flaplace;                                            //delete laplace filter
            }
            else
            {
                delete inputImage;                                          //delete image if an error occurs
                cerr << "Wrong filter's name or filter's name is missing" << endl;  //print error message
                exit(0);
            }
        }
        else
        {
            delete inputImage;                                              //delete image if an error occurs
            cerr << "All filters should have -f or previous filter has more numbers as argument" << endl;   //print error message
            exit(0);
        }
    }
    if (atLeastOneFilter)                                                   //check if cmd arguments have at least one filter
    {
        delete inputImage;                                                  //delete image if an error occurs
        cerr << "Program should use at least one filter" << endl;           //print error message
        exit(0);
    }

    string partA = imageFile.substr(0, imageFile.find_last_of('/')+1);      //find the last / so we can skip path of file
    string partB = imageFile.substr(imageFile.find('/')+1, imageFile.size());   
    if((*inputImage).save(partA + "filtered_" + partB,"ppm"))               //check save of image and add "filtered" at the start of image file  
    {
        cout << "Save was successful" <<endl;
    }              
    delete inputImage;                                                      //delete image
}//end of main

bool isPositiveNumber(const string& s)                                          
{
    bool flag = false;
    string::const_iterator it = s.begin();
    while (it != s.end())                                                   //check all chars if contain at least a number
    {
        if(isdigit(*it)){
            flag = true;
        }
        it++;
    }
    it = s.begin();
    while (it != s.end() && isdigit(*it) || (*it == '.' && s.find_last_of('.') == s.find_first_of('.'))) ++it;  //check all chars for '.' and if number has only one time '.'
    return !s.empty() && it == s.end() && flag == true;
}

bool isIntegerNumber(const string& s)
{
    string::const_iterator it = s.begin();
    while (it != s.end() && isdigit(*it)) ++it;
    return !s.empty() && it == s.end();
}

bool isNumber(const string& s)
{
    bool flag = false;
    string::const_iterator it = s.begin();
    while (it != s.end())                                                   //check all chars if contain at least a number
    {  
        if(isdigit(*it)){
            flag = true;
        }
        it++;
    }
    it = s.begin();
     //check all chars for '.','-' and if number has only one time '.','-' and '-' is at position 0
    while (it != s.end() && isdigit(*it) || (*it == '.' && s.find_last_of('.') == s.find_first_of('.')) || (*it == '-' && s.find_last_of('-') == 0 && s.find_first_of('-')==0)) ++it;
    return !s.empty() && it == s.end() && flag == true;
}