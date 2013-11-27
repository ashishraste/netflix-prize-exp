//
//  ProbeRatings.h
//  CS5228Project
//
//  Created by OrangeR on 26/11/13.
//  Copyright (c) 2013 OrangeR. All rights reserved.
//

#ifndef CS5228Project_ProbeRatings_h
#define CS5228Project_ProbeRatings_h
#include "MovieRatings.h"
#include "UserRatings.h"

typedef struct pRatings{
    std::vector<mRatings> *p;
    pRatings *next;
}pRatings;

class ProbeRatings:public Ratings
{
private:
    int pNum;
    pRatings *pRs;
public:
    

};

#endif
