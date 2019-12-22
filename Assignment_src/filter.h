#ifndef FILTERS_
#define FILTERS_
#ifndef DEBUG
//#define DEBUG
#endif

#include "image.h"

class Filter
{
    public:
        Filter(){}                                                           //declaration of default constructor
        virtual ~Filter(){}                                                  //declaration of virtual destructor
        virtual image::Image operator << (const image::Image & image) = 0;   //declaration of pure virtual operator
};


class FilterGamma: public Filter 
{
    float gamma;                                                  //class atrribute

    public:
        FilterGamma();                                            //declaration of default constructor

        FilterGamma(float gamma);                                 //declaration of constructor

        ~FilterGamma();                                           //declaration of destructor

        image::Image operator << (const image::Image & image);    //declaration of operator

        float getGamma();                                         //declaration of get method

        void setGamma(float gamma);                               //declaration of set method
};

class FilterLinear: public Filter
{
    math::Vec3<float> a;                                          //class attribute a(a1,a2,a3)
    math::Vec3<float> c;                                          //class attribute c(c1,c2,c3)

    public:
        FilterLinear();                                           //declaration of default constructor

        FilterLinear(math::Vec3<float> a, math::Vec3<float> c);   //declaration of constructor

        ~FilterLinear();                                          //declaration of destructor

        image::Image operator << (const image::Image & image);    //declaration of operator

        math::Vec3<float> getLinearTripleA();                      //declaration of get method

        math::Vec3<float> getLinearTripleC();                      //declaration of get method

        void setLinearTripleA(math::Vec3<float> a);                //declaration of set method

        void setLinearTripleC(math::Vec3<float> c);                //declaration of set method
};

class FilterBlur: public Filter,public math::Array2D<float>
{
    protected:
        int N;                                                              //class attribute
    public:
        FilterBlur();                                                       //declaration of default constructor

        FilterBlur(int N);                                                  //declaration of constructor

        ~FilterBlur();                                                      //declaration of destructor

        image::Image operator << (const image::Image & image);              //declaration of operator

        int getN();                                                         //declaration of get method

        void setN(int N);                                                   //declaration of set method
    protected:
        int checkTheBOundsOfArray(int current, int minValue, int maxValue); //declaration of method which check bounds
};

class FilterLaplace: public FilterBlur
{
    public:
        FilterLaplace();                                                    //declaration of default constructor

        ~FilterLaplace();                                                   //declaration of destructor
};


#endif //PURE_VIRTUAL_FUNCTIONS_