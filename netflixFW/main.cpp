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
#include "BaselinePredictor.h"

using namespace std;

int main(int argc, const char * argv[])
{    
    // insert code here...
    MovieRatings *mRs = new MovieRatings();
    UserRatings *uRs = new UserRatings();
    ProbeRatings *pRs = new ProbeRatings();
    Database db;

    //db.loadDatabase(DATABASE_PATH + MOVIEDATABASE, DATABASE_PATH + USERDATABASE, *mRs, *uRs);
    //mRs->dumpRatings(17770);
    //vector<mRatings> temp = (*mRs)[1];
    //cout << ((*mRs)[1])[0].getValue() << endl;
    //cout << temp[1]. << endl;
    //double *p = mRs->getAllMeans();
    //for(int i = 0; i < mRs->getMovieNum(); i ++)
    //{
    //    cout << p[i] << endl;
    //}

    db.loadDatabase(DATABASE_PATH + MOVIEDATABASE, DATABASE_PATH + USERDATABASE, *mRs, *uRs);
    db.loadProbeDatabase(DATABASE_PATH + PROBEDATABASE, *pRs);

    mRs->computeAllBias();
    uRs->computeAllBias(mRs);

    BaselinePredictor *bp = NULL;

    int predType;
    cout << "We have the following predictors, choose one: \n1. Baseline predictor \n2. KNN \n3. SVD \n4. KNNSVD blend" << endl;
    cin >> predType;

    switch (predType) {
    	case 1:
    		{
    			cout << "Running the Baseline predictor" << endl;
    			bp = new BaselinePredictor(mRs, uRs, pRs);
    			break;
    		}
    	case 2:
    		break;
    	case 3:
    		break;
    	case 4:
    		break;
    	default:
    		cout << "option number is wrong, please try again!" << endl;
    		break;
    }

    cout << "Calculating RMSE" << endl;
    double rmse = pRs->RMSE();
    cout << "RMSE: " << rmse << endl;

    delete mRs;
    delete uRs;
    delete pRs;

    if (NULL != bp) delete bp;

    return 0;
}

