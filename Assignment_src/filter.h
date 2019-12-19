#ifndef PURE_VIRTUAL_FUNCTIONS_
#define PURE_VIRTUAL_FUNCTIONS_
#ifndef DEBUG
//#define DEBUG
#endif

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
    protected:
        int checkTheBOundsOfArray(int current, int minValue, int maxValue); //declaration of method which check bounds
};

class FilterLaplace: public FilterBlur
{
    protected:
        int N;                                                              //class attribute
    public:
        FilterLaplace();                                                    //declaration of default constructor

        ~FilterLaplace();                                                   //declaration of destructor
};


#endif //PURE_VIRTUAL_FUNCTIONS_