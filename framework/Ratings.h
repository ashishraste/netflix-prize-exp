//
//  Ratings.h


#ifndef framework_Ratings_h
#define framework_Ratings_h

#include <iostream>
#include <math.h>
typedef unsigned char uByte;
typedef unsigned int uInt;
const int MOVIE_NUM = 17770;
const int USER_NUM = 480189;

class Ratings{
private:
    uInt g_support;
    float g_mean;
    float g_std_dev;
protected:
    //virtual int binarySearch(void * p, int num);
    //void setSupport(uInt support){g_support = support;};
    //void setMean(float mean){g_mean = mean;};
    //void setStd_dev(float std_dev){g_std_dev = std_dev;};
public:
    //Ratings(){};
    //~Ratings(){};
    //uInt getSupport(){return g_support;};
    virtual uInt getSupport(uInt Idx);
    //uInt getMean(){return g_mean;};
    virtual float getMean(uInt Idx);
    //float getStd_dev(){return g_std_dev;};
    virtual float getStd_dev(uInt Idx);
    virtual uByte getRating(uInt mId, uInt uId);
};

#endif
