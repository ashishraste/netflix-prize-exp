//
//  ProbeRatings.h
//  CS5228Project
//
//  Created by OrangeR on 26/11/13.
//  Copyright (c) 2013 OrangeR. All rights reserved.
//

#ifndef CS5228Project_ProbeRatings_h
#define CS5228Project_ProbeRatings_h
//#include "Helper.h"
#include "MovieRatings.h"
#include "UserRatings.h"
//#include "helper"
//#include "Database.h"
#include <string>
#include <utility>

class ProbeRatings:public Ratings
{
private:
    std::vector< std::vector<mRatings>* > *realRatings;
    std::vector<double> *predictedRatings;
    std::vector<uShort> mIds;
    double m_rmse;
public:
    ProbeRatings();
    ~ProbeRatings();
    uInt getPredictedMovieNum();
    
    void addRatings(double &prediction);
    void addRatings(uShort movieId, std::vector<mRatings> &pRs);
    void getRatings(uInt idx, uShort &movieId, std::vector<mRatings> &pRs);
    void dumpAllRatings();
    void dumpRatings(uInt idx);
    //void dumpAllPredictedRatings();
    //void dumpPredcitedRatings();
    void savePredictions(const std::string &path, const std::string &file_name);
    double RMSE();
};
#endif
