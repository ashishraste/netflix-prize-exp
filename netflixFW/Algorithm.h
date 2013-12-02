//
//  Algorithm.h
//  CS5228Project
//
//  Created by OrangeR on 26/11/13.
//  Copyright (c) 2013 OrangeR. All rights reserved.
//

#ifndef CS5228Project_Algorithm_h
#define CS5228Project_Algorithm_h
#include "MovieRatings.h"
#include "UserRatings.h"
#include "ProbeRatings.h"
#include "Helper.h"
#include "Config.h"

class Algorithm{
public:
    Algorithm(){};
    virtual ~Algorithm() {};
    virtual double predictRatings() = 0;
};
#endif
