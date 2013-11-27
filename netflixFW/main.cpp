//
//  main.cpp
//  CS5228Project
//
//  Created by OrangeR on 8/11/13.
//  Copyright (c) 2013 OrangeR. All rights reserved.
//

#include <iostream>
#include <string>
#include "Config.h"
#include "UserRatings.h"
#include "MovieRatings.h"
#include "Database.h"
#include "Algorithm.h"

using namespace std;

int main(int argc, const char * argv[])
{    
    // insert code here...
    MovieRatings *mRs = new MovieRatings();
    UserRatings *uRs = new UserRatings();
    Database db;
    db.loadDatabase(DATABASE_PATH + MOVIEDATABASE, DATABASE_PATH + USERDATABASE, *mRs, *uRs);
    //mRs->dumpRatings(17770);
    //vector<mRatings> temp = (*mRs)[1];
    //cout << ((*mRs)[1])[0].getValue() << endl;
    //cout << temp[1]. << endl;
    //double *p = mRs->getAllMeans();
    //for(int i = 0; i < mRs->getMovieNum(); i ++)
    //{
    //    cout << p[i] << endl;
    //}

    Algorithm *al = new Algorithm(&db, mRs, uRs);
    al -> determine(2);

    delete mRs;
    delete uRs;
    return 0;
}

