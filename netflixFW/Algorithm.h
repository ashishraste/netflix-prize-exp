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
