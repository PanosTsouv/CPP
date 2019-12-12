#ifndef _IMAGE
#define _IMAGE


#include "array2d.h"
#include "imageIO.h"
#include "vec3.h"

namespace image
{
    class Image: public Array2D<Vec3<float>>,public ImageIO
	{
    protected:
        Image(unsigned int width, unsigned int height, const Vec3<float> * data_ptr):Array2D<Vec3<float>>(width, height, data_ptr)
        {

        }
    public:
        bool load(const std::string & filename, const std::string & format) = 0;
        bool save(const std::string & filename, const std::string & format) = 0;
    };
}
#endif