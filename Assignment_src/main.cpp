#include <iostream>
#include <vector>
#include <cstring>
#include "ppm/ppm.h"
#include "array2d.h"
#include "vec3.h"
#include "image.h"
#include "filter.h"

using namespace math;
using namespace std;
using namespace image;

bool isIntegerNumber(const std::string& s); //declaration(implementation is at the end)
bool isNumber(const std::string& s);        //declaration(implementation is at the end)

int main (int argc, char *argv[]) {
    
    string imageFile = argv[argc-1];
    bool atLeastOneFilter = true;                                       //flag which check if user's input has at least one filter
    int current = 1;                                                    //cmd argument start from 1,ignore main program
    int imageWidth = 0;                                                 //imageWidth
    int imageHeight = 0;                                                //ImageHeight
    vector<Filter*> userFilters;                                        //contains all user's filters
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
    
    while (current < (argc-1))                                            //exit loop if current show the last cmd argument
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
				if (isNumber(argv[current]) && strtof(argv[current], NULL) >= 0.5 && strtof(argv[current], NULL) <= 2.0)        //check if gamma filter's argument is a positive float number between 0.5-2
                {
                    #ifdef DEBUG
                        cout << "Gamma's number detected" << endl;
                    #endif
					Filter *fgamma = new FilterGamma(strtof(argv[current], NULL));  //filter gamma contains right data so we create a filter gamma
                    userFilters.insert(userFilters.begin(), fgamma);        //add filter to vector with all filters...add at front so the first filter will be at the end
                    current++;                                              //current show next cmd argument
                }
                else
                {   
                    while(!userFilters.empty())                             //if an error occurs we should delete filters which be created
                    {
                        delete userFilters.back();
                        userFilters.pop_back();
                    }
                    delete inputImage;                                      //delete image if an error occurs
                    cerr << "Gamma filter dont have number or number isn't 0.5-2 or has more than one number" << endl;     //print error message
                    exit(0);
                }
            }
            else if (strcmp(argv[current], "linear") == 0)                  //check if filter is linear
            {
                cout << "Filter linear detected" << endl;
                int count = 0;                                              //count check if filter has 6 arguments
                float linearNumbers[6];                                     //save arguments inside temp array
                current++;                                                  //current show next cmd argument
                while (count < 6)
                {
                    if (isNumber(argv[current]))                            //check if numbers of linear filter are real numbers
                    {
                        #ifdef DEBUG
                            cout << "Linear's number detected" << endl;
                        #endif
                        linearNumbers[count] = strtof(argv[current], NULL); //put current argument inside array
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
                Filter* flinear = new FilterLinear(Vec3<float>(linearNumbers[0], linearNumbers[1], linearNumbers[2]), Vec3<float>(linearNumbers[3], linearNumbers[4], linearNumbers[5]));  //if all data of linear filter is right create a linear filter
                userFilters.insert(userFilters.begin(),flinear);            //add filter to vector with all filters...add at front so the first filter will be at the end
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
                    FilterBlur *fblur = new FilterBlur(atoi(argv[current]));//if filter blur's data is right create a filter blur
                    userFilters.insert(userFilters.begin(),fblur);          //add filter to vector with all filters...add at front so the first filter will be at the end
                    current++;                                              //current show next cmd argument
                }
                else
                {
                    while(!userFilters.empty())                             //if an error occurs we should delete filters which be created
                    {
                        delete userFilters.back();
                        userFilters.pop_back();
                    }
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
                userFilters.insert(userFilters.begin(),flaplace);           //add filter to vector with all filters...add at front so the first filter will be at the end
            }
            else
            {
                while(!userFilters.empty())                                 //if an error occurs we should delete filters which be created
                {
                    delete userFilters.back();
                    userFilters.pop_back();
                }
                delete inputImage;                                          //delete image if an error occurs
                cerr << "Wrong filter's name or filter's name is missing" << endl;  //print error message
                exit(0);
            }
        }
        else
        {
            while(!userFilters.empty())                                     //if an error occurs we should delete filters which be created
            {
                delete userFilters.back();
                userFilters.pop_back();
            }
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

    while(!userFilters.empty())                                             //use a filter and delete it until vector is empty
    {
        *inputImage = *userFilters.back() << *inputImage;
        delete userFilters.back();
        userFilters.pop_back();
    }

    string partA = imageFile.substr(0, imageFile.find_last_of('/')+1);      //find the last / so we can skip path of file
    string partB = imageFile.substr(imageFile.find('/')+1, imageFile.size());   
    if((*inputImage).save(partA + "filtered_" + partB,"ppm"))               //check save of image and add "filtered" at the start of image file  
    {
        cout << "Save was successful" <<endl;
    }          
    delete inputImage;                                                     //delete image
}//end of main



bool isIntegerNumber(const string& s)
{
    string::const_iterator it = s.begin();
    while (it != s.end() && isdigit(*it)) ++it;
    return !s.empty() && it == s.end();
}

bool isNumber(const string& s)
{
    if (s.find_first_not_of("1234567890.-") != string::npos)                                            //check if s contains theses chars
    {
        return false;
    }
    if (s.find_last_of('.') != s.find_first_of('.'))                                                    //check if s contains char '.' one time 
    {
        return false;
    }
    if (s.find_last_of('-') != s.find_first_of('-'))                                                    //check if s contains char '-' one time 
    {
        return false;
    }
    if (s.find_first_of('-') != 0 && s.find('-') != std::string::npos)                                  //check if s contains 2 chars and are '-' and '.' 
    {
        return false;
    }
    if (s.length() == 2 && s.find('-') != std::string::npos && s.find('.') != std::string::npos)        //check if s contains only 1 char and is '.'
    {
        return false;
    }
    if (s.length() == 1 && (s.find('-') != std::string::npos || s.find('.') != std::string::npos))      //check if s contains only 1 char and is '-' 
    {
        return false;
    }
    return true;                                                                                        //if all statements above are true return true
}