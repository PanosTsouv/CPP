#include <iostream>

#include "array2d.h"
using namespace std;
using namespace math;

template <class T>
Array2D<T>::Array2D(unsigned int width, unsigned int height, const T * data_ptr): width(width), height(height)
{
    cout << "Default constructor called" << endl;
    setData(data_ptr);
}

template <class T>
Array2D<T>::Array2D(const Array2D<T> &src) : width(src.width), height(src.height)
{
    cout << "Copy constructor called" << endl;
    setData(src.buffer.data());
}

template <class T>
Array2D<T>::~Array2D()
{
    cout << "Destructor delete an item" << endl;
}

template <class T>
const unsigned int Array2D<T>::getWidth() const
{
    return width;
}

template <class T>
const unsigned int Array2D<T>::getHeight() const
{
    return height;
}

template <class T>
T * Array2D<T>::getRawDataPtr()
{
    return buffer.data();
}

template <class T>
void Array2D<T>::setData(const T * const & data_ptr)
{
    if(width != 0 && height !=0)
    {
        if(buffer.empty())
            for (int i = 0; i < width*height; i++) 
            {
                if (data_ptr != nullptr)
                {
                    buffer.push_back(*(data_ptr + i));
                }
                else
                {
                    buffer.push_back(0);
                }
            }
        else if(!buffer.empty())
        {
            for (int i = 0; i < width*height; i++)
            {
                if (data_ptr != nullptr)
                {
                    *(buffer.data() + i) = *(data_ptr + i);
                }
                else
                {
                    buffer.push_back(0);
                }
            }
        }
    }
    else
    {
        cerr << "Dimensions of image can't be 0---this object will be deleted" << endl;
        delete this;
        return; 
    }
    
}

template <class T>
T & Array2D<T>::operator () (unsigned int x, unsigned int y)
{
    return buffer.at(width * y + x);
}

template <class T>
Array2D<T> & Array2D<T>::operator = (const Array2D & right)
{
    width = right.width;
    height = right.height;
    setData(right.buffer.data());
    return *this;
}