//
//  Ratings.h
//  CS5228Project
//
//  Created by OrangeR on 15/11/13.
//  Copyright (c) 2013 OrangeR. All rights reserved.
//

#ifndef CS5228Project_Ratings_h
#define CS5228Project_Ratings_h

#include <iostream>
#include <math.h>
#include "Config.h"
const double G_MEAN = 3.604;
const uInt USER_BIAS_PARAM = 10;
const uInt MOVIE_BIAS_PARAM = 25;

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
