#ifndef CS5228Project_Ratings_h
#define CS5228Project_Ratings_h
#define G_MEAN				3.604
#define USER_BIAS_PARAM		10
#define MOVIE_BIAS_PARAM	25

#include <iostream>
#include <math.h>
#include "Config.h"

class Ratings{
private:
    //uInt g_support;
    //float g_mean;
    //float g_std_dev;
protected:
public:
    Ratings(){};
    virtual ~Ratings(){};
    //virtual void dumpAllRatings() = 0;
    //virtual void dumpRatings(uInt id) = 0;
    //virtual void dumpAllMeans() = 0;
    //virtual void dumpAllStdDevs() = 0;
    //virtual void computeAllMeans() = 0;
    //virtual void computeAllStdDevs() = 0;
    //virtual double* & getAllMeans() = 0;
    //virtual double* & getAllStdDevs() = 0;
    //virtual double getMean(uInt id) = 0;
    //virtual double getStdDev(uInt id) = 0;
};

#endif
