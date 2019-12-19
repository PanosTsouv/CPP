#ifndef DEBUG
//#define DEBUG
#endif

#include <iostream>

using namespace std;

namespace math{

    template <class T>
    Array2D<T>::Array2D(unsigned int width, unsigned int height, const T * data_ptr): width(width), height(height)  //set width and height
    {
        #ifdef DEBUG
            cout << "Default constructor of Array2d called" << endl;
        #endif
        setData(data_ptr);                                                                                          //see setData
    }

    //copy constructor
    template <class T>
    Array2D<T>::Array2D(const Array2D<T> &src) : width(src.width), height(src.height)                               //set src's width and height
    {
        #ifdef DEBUG
            cout << "Copy constructor of Array2d called" << endl;
        #endif
        setData(src.buffer.data());                                                                                 //see setData
    }

    //destructor
    template <class T>
    Array2D<T>::~Array2D()
    {
        #ifdef DEBUG
            cout << "Destructor delete an Array2d" << endl;
        #endif
    }

    template <class T>
    const unsigned int Array2D<T>::getWidth() const
    {
        return width;                                                                                               //return width of object's array
    }

    template <class T>
    const unsigned int Array2D<T>::getHeight() const
    {
        return height;                                                                                              //return height of object's array
    }

    template <class T>
    T * Array2D<T>::getRawDataPtr()
    {
        return buffer.data();                                                                                       //return data ponter od data inside object's array
    }

    template <class T>
    void Array2D<T>::setData(const T * const & data_ptr)
    {
        if(width > 0 && height > 0)                                                                                 //if width and height are > 0 else return nothing
        {
            this->buffer.clear();                                                                                   //clear buffer which contains data because it could have data inside
            for (int i = 0; i < width*height; i++) 
            {
                if (data_ptr != 0)                                                                                  //if data ponter = 0 means that we dont have given data so go to else and set data as zero
                {
                    this->buffer.push_back(*(data_ptr + i));                                                        //if !=0 set the given data
                }
                else
                {
                    this->buffer.push_back(0);
                }
            }
        }
        else
        {
            return;                                                                                                 
        }      
    }

    template <class T>
    T & Array2D<T>::operator () (unsigned int x, unsigned int y)
    {
        return buffer.at(width * y + x);                                                                            //return the object inside a spesific position
    }

    template <class T>
    Array2D<T> & Array2D<T>::operator = (const Array2D & right)
    {
        width = right.width;                                                                                        //left object's width take right object's width
        height = right.height;                                                                                      //left object's height take right object's height
        setData(right.buffer.data());                                                                               //see setData
        return *this;                                                                                               //return new left object
    }

}//end namespace