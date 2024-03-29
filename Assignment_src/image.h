#ifndef _IMAGE
#define _IMAGE

#include "array2d.h"
#include "imageIO.h"
#include "vec3.h"



namespace image
{
    class Image: public math::Array2D<math::Vec3<float>>,public ImageIO
	{
    public:
        Image(unsigned int width = 0, unsigned int height = 0);                 //Declaration of default constructor

        Image(const Image &src);                                                //Declaration of copy constructor

        ~Image();                                                               //Declaration of destructor

        bool load(const std::string & filename, const std::string & format);    //Declaration of load method,see also imageio.h for full description of this pure virtual method

        bool save(const std::string & filename, const std::string & format);    //Declaration of save method,see also imageio.h for full description of this pure virtual method    
    };
}
#endif