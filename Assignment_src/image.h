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
        Image(unsigned int width = 0, unsigned int height = 0);
        bool load(const std::string & filename, const std::string & format);
        bool save(const std::string & filename, const std::string & format);
    };
}
#endif