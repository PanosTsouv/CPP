#include <iostream>
#include <vector>
#include "vec3.h"
#include "image.h"
#include "filter.h"
#include "math.h"

using namespace std;
using namespace math;
using namespace image;

/************************************************************************
** FilterGamma Constructors-Destructor & Operator << & set,get methods **
************************************************************************/

//Default constructor
FilterGamma::FilterGamma()
{
    #ifdef DEBUG 
        cout << "Gamma filter default constructor called" << endl;
    #endif
    this->gamma = 1.f;                                                //initialization of class attribute as 1
}

//Constructor
FilterGamma::FilterGamma(float gamma)
{
    #ifdef DEBUG 
        cout << "Gamma filter constructor called" << endl; 
    #endif
    if (gamma >= 0.5f && gamma <= 2.f)
    {
        this->gamma = gamma;                                           //initialization of class attribute
    }
    else
    {
        cerr << "Gamma argument should be 0.5-2.Default initialization as 1" << endl;
        this->gamma = 1.f;
    }
}

//Destructor
FilterGamma::~FilterGamma()
{
    #ifdef DEBUG
        cout << "Delete a Gamma filter" << endl;
    #endif  
}

float FilterGamma::getGamma()
{
    return this->gamma;                                                //return object's argument gamma
}

void FilterGamma::setGamma(float gamma)
{
    if (gamma >= 0.5f && gamma <= 2.f)
    {
        this->gamma = gamma;                                           //set user's data
    }
    else
    {
        cerr << "Gamma argument should be 0.5-2" << endl;
    }
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


/*************************************************************************
** FilterLinear Constructors-Destructor & Operator << & set,get methods **
*************************************************************************/

//Default constructor
FilterLinear::FilterLinear()
{
    #ifdef DEBUG 
        cout << "Linear filter default constructor called" << endl;
    #endif
    this->a = Vec3<float>(1, 1, 1);
    this->c = Vec3<float>(0, 0, 0);                                 //With these default values if user use the operator << we will return the input image without differences
}


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

Vec3<float> FilterLinear::getLinearTripleA()
{
    return this->a;                                                //return object's argument linear a
}

Vec3<float> FilterLinear::getLinearTripleC()
{
    return this->c;                                               //return object's argument linear c
}

void FilterLinear::setLinearTripleA(math::Vec3<float> a)          //set input a
{
    this->a = a;
}

void FilterLinear::setLinearTripleC(math::Vec3<float> c)          //set input c
{
    this->c = c;
}

//implementation of pure virtual operator from base abstract class Filter
Image FilterLinear::operator << (const Image & image)
{
    Image newImage(image);                                          //copy of image which is given as argument

	for (unsigned int i = 0; i < newImage.getHeight(); i++)         //for every pixel of newImage(height give us the rows and width give us the columns)
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

/*****************************************************************************************************
** FilterBlur Constructors-Destructor & Operator << & checkTheBOundsOfArray method & set,get methods**
*****************************************************************************************************/

//default constructor
FilterBlur::FilterBlur():Array2D<float>(this->N = 1, this->N = 1){} //With these default values if user call operator << we will returnn the input image

//constructor
FilterBlur::FilterBlur(int N):Array2D<float>(N, N)
{
    #ifdef DEBUG
        cout << "Filter blur Constructor called" << endl;
    #endif
    this->N = N;                                                     //initialization of class attribute
    for (int i = 0; i < N*N; i++) {
        *(this->buffer.data() + i) = 1.f/(N*N);                      //initialization of filter blur array N*N with value (1.0/N*N)
    }
}

//destructor
FilterBlur::~FilterBlur()
{
    #ifdef DEBUG
        cout << "Delete a blur filter" << endl;
    #endif
}

int FilterBlur::getN()                                               //return the value of class attribute N
{
    return this->N;
}

void FilterBlur::setN(int N)                                         //set the input N
{
    if (typeid(*this) != typeid(FilterLaplace))
    {
        this->N = N;
        FilterBlur* newFilter = new FilterBlur(N);
        cout << this->getRawDataPtr() << endl;
        *this = *newFilter;
        cout << this->getRawDataPtr() << endl;
        delete newFilter;
    }
}

Image FilterBlur::operator << (const image::Image & image)
{
    Image inputImage(image);
    Image newImage(image.getWidth(), image.getHeight());
	for (unsigned int i = 0; i < image.getHeight(); i++)              //for every pixel of input image i=rows(Height) j=columns(Width)
    {
		for (unsigned int j = 0; j < image.getWidth(); j++)
        {
            for (int m = -N / 2; m <= N / 2; m++) {                   //for every pixel in neighnorhood NxN of pixel (j,i), m=rows(Height) n=columns(Width) of blur filter array
				for (int n = -N / 2; n <= N / 2; n++) {
                    //new pixel (j,i) = the sum of all pixel in neighborhood NxN * the value of filter array (n,m)   (*this)() //return the filter's buffer value
                    newImage(j,i) += inputImage(checkTheBOundsOfArray(j + n, 0, image.getWidth()-1),checkTheBOundsOfArray(i + m, 0, image.getHeight()-1))*((*this)(n + N/2, m + N/2));
                }
            }
            if (typeid(*this) != typeid(FilterBlur))                   //if filter is filter blue dont need to checks Upper-Lower bound
            {
                newImage(j, i) = newImage(j, i).clampToUpperBound(1);
                newImage(j, i) = newImage(j, i).clampToLowerBound(0);
            }
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

//default constructor
FilterLaplace::FilterLaplace():FilterBlur(this->N = 3)                           //called FilterBlur constructor with default N = 3
{
    #ifdef DEBUG
        cout << "Filter laplace Constructor called" << endl;
    #endif
    for (int i = 0; i < N * N; i++) {
        if (i % 2 == 0)
        {
            *(this->buffer.data() + i) = 0;
            if (i / 2 == 2)
            {                                                                                            //| 0 |  1 | 0 |
                *(this->buffer.data() + i) = -4;                                 //initialization of array | 1 | -4 | 1 |
            }                                                                                            //| 0 |  1 | 0 |
        }
        else
        {
            *(this->buffer.data() + i) = 1;
        }
    }
}

//destructor
FilterLaplace::~FilterLaplace()
{
    #ifdef DEBUG
        cout << "Delete a laplace filter" << endl;
    #endif
}