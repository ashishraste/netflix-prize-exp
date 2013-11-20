//
//  Helper.h


#ifndef framework_Helper_h
#define framework_Helper_h
#include <string>
#include <dirent.h>
#include <iostream>
#include <fstream>
#include "MovieRatings.h"
#include "UserRatings.h"
using namespace::std;

int strToInt(string str);
int loadData(const std::string dir, MovieRatings &mRs, UserRatings &uRs);
double calUUPearsonCorrelation(UserRatings &uRs, uInt uId1, uInt uId2);
double calMMPearsonCorrelation(MovieRatings &mRs, uInt mId1, uInt mId2);
double calculatePearsonCorrelation(MovieRatings &mRs, UserRatings &uRs, int Id1, int Id2);

#endif
