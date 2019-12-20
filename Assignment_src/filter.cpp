#include <iostream>
#include <vector>
#include "vec3.h"
#include "image.h"
#include "filter.h"
#include "math.h"

using namespace std;
using namespace math;
using namespace image;

/******************************************************
** FilterGamma Constructors-Destructor & Operator << **
******************************************************/

//Default constructor
FilterGamma::FilterGamma(){}

//Constructor
FilterGamma::FilterGamma(float gamma)
{
    #ifdef DEBUG 
        cout << "Gamma filter constructor called" << endl; 
    #endif
    this->gamma = gamma;                                           //initialization of class attribute
}

//Destructor
FilterGamma::~FilterGamma()
{
    #ifdef DEBUG
        cout << "Delete a Gamma filter" << endl;
    #endif  
}

//implementation of pure virtual operator from base abstract class Filter
Image FilterGamma::operator << (const Image & image)
{
    Image newImage(image);                                         //copy of image which is given as argument

	for (unsigned int i = 0; i < newImage.getHeight(); i++)                 //for every pixel of newImage(height give us the rows and width give us the columns)
    {
		for (unsigned int j = 0; j < newImage.getWidth(); j++)
        {
            newImage(j,i)[0] = pow(newImage(j,i)[0], gamma);       //Red color^gamma    |
            newImage(j,i)[1] = pow(newImage(j,i)[1], gamma);       //Green color^gamma  |=>(current pixel)^gamma
            newImage(j,i)[2] = pow(newImage(j,i)[2], gamma);       //Blue color^gamma   |
        }
    }
    return newImage;                                               //return newImage
}


/*******************************************************
** FilterLinear Constructors-Destructor & Operator << **
*******************************************************/

//Default constructor
FilterLinear::FilterLinear(){}


//Constructor
FilterLinear::FilterLinear(Vec3<float> a, Vec3<float> c)
{
    #ifdef DEBUG
        cout << "Linear filter constructor called" << endl;
    #endif
    this->a = a;                                                    //initialization of class attribute
    this->c = c;                                                    //initialization of class attribute
}

//Destructor
FilterLinear::~FilterLinear()
{
    #ifdef DEBUG
        cout << "delete a Linear filter" << endl;
    #endif
}

//implementation of pure virtual operator from base abstract class Filter
Image FilterLinear::operator << (const Image & image)
{
    Image newImage(image);                                          //copy of image which is given as argument

	for (unsigned int i = 0; i < newImage.getHeight(); i++)                  //for every pixel of newImage(height give us the rows and width give us the columns)
    {
		for (unsigned int j = 0; j < newImage.getWidth(); j++)
        {
            newImage(j,i) = a * newImage(j,i) + c;                  //(R,G,B)*(a1,a2,a3)+(c1,c2,c3)

            newImage(j,i) = newImage(j,i).clampToUpperBound(1);     //ckeck if pixels's value is > 1,if true pixel's value become 1
            newImage(j,i) = newImage(j,i).clampToLowerBound(0);     //ckeck if pixels's value is < 0,if true pixel's value become 0
        }
    }
    return newImage;                                                //return newImage
}

/***********************************************************************************
** FilterBlur Constructors-Destructor & Operator << & checkTheBOundsOfArray method**
***********************************************************************************/

FilterBlur::FilterBlur(){}

FilterBlur::FilterBlur(int N):Array2D<float>(N,N)
{
    #ifdef DEBUG
        cout << "Filter blur Constructor called" << endl;
    #endif
    this->N = N;                                                     //initialization of class attribute
    for (int i = 0; i < N*N; i++) {
        buffer[i] = 1.f/(N*N);                                       //initialization of filter blur array N*N with value (1.0/N*N)
    }
}

FilterBlur::~FilterBlur()
{
    #ifdef DEBUG
        cout << "Delete a blur filter" << endl;
    #endif
}

Image FilterBlur::operator << (const image::Image & image)
{
    Image inputImage(image);
    Image newImage(image.getWidth(), image.getHeight());
	for (unsigned int i = 0; i < image.getHeight(); i++)
    {
		for (unsigned int j = 0; j < image.getWidth(); j++)
        {
            for (int n = -N/2; n <= N/2; n++) {
				for (int m = -N/2; m <= N/2; m++) {
                    newImage(j,i) += (inputImage(checkTheBOundsOfArray(j + n, 0, image.getWidth()-1),checkTheBOundsOfArray(i + m, 0, image.getHeight()-1))*(this->buffer[((m + N/2) * N) + n + N/2]));
                }
            }
            newImage(j,i) = newImage(j,i).clampToUpperBound(1);
            newImage(j,i) = newImage(j,i).clampToLowerBound(0);
        }
    }
    return newImage;
}

int FilterBlur::checkTheBOundsOfArray(int current, int minValue, int maxValue)    //return max or min or current
{
    if (current > maxValue)
    {
        return maxValue;
    }
    if(current < minValue)
    {
        return minValue;
    }
    return current;
}

/******************************************
** FilterLaplace Constructors-Destructor **
******************************************/

FilterLaplace::FilterLaplace():FilterBlur(this->N = 3)                           //called FilterBlur constructor
{
    #ifdef DEBUG
        cout << "Filter laplace Constructor called" << endl;
    #endif
    for (int i = 0; i < N*N; i++) {
        if(i % 2 == 0)
        {
            this->buffer[i] = 0;
            if (i / 2 == 2)
            {                                                                                             //| 0 |  1 | 0 |
                this->buffer[i] = -4;                                             //initialization of array | 1 | -4 | 1 |
            }                                                                                             //| 0 |  1 | 0 |
        }
        else
        {
            this->buffer[i] = 1;
        }
    }
}

FilterLaplace::~FilterLaplace()
{
    #ifdef DEBUG
        cout << "Delete a laplace filter" << endl;
    #endif
}