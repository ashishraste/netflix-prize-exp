//
//  main.cpp
//  CS5228Project
//
//  Created by OrangeR on 8/11/13.
//  Copyright (c) 2013 OrangeR. All rights reserved.
//

#include <iostream>
#include <string>
#include <cstdlib>
#include "Config.h"
#include "UserRatings.h"
#include "MovieRatings.h"
#include "Database.h"
#include "SVD.h"
#include "BaselinePredictor.h"
#include "KNN.h"
#include "Helper.h"


using namespace std;

int main(int argc, const char * argv[])
{    
    // insert code here...
    
    MovieRatings *mRs = new MovieRatings();
    UserRatings *uRs = new UserRatings();
    ProbeRatings *pRs = new ProbeRatings();
    Database db;
    
    db.loadDatabase(DATABASE_PATH + MOVIEDATABASE, DATABASE_PATH + USERDATABASE, *mRs, *uRs);
    db.loadProbeDatabase(DATABASE_PATH + PROBEDATABASE, *pRs);
    
    Algorithm *al = NULL;
    SVD *pSVD = NULL;
    int predType = 0;
    double rmse = 0;
    cout << "We have the following predictors, choose one: \n1. Baseline predictor \n2. KNN \n3. SVD \n4. KNNSVD blend" << endl;
    cin >> predType;
    
    switch (predType) {
    	case 1:
    	{
    		cout << "Running the Baseline predictor" << endl;
    		al = new BaselinePredictor(mRs, uRs, pRs);
    		break;
    	}
    	case 2:
    	{
    		int kValue = 0;
    		cout << "Choose a k value from 1 to " << MOVIE_NUM << endl;
            cin >> kValue;
            if(kValue < 0 || kValue > MOVIE_NUM)
            {
                cout << "kValue invalid" << endl;
                break;
            }
            cout << "Running KNN predictor, Pearson correlation for item-item similarity, k = " << kValue << endl;
            al = new KNN(mRs, uRs, pRs, NULL, kValue);
    		break;
    	}
    	case 3:
    	{
            int featureNum = 0;
            cout << "specify how many features(1 to " << MAX_FEATURES << "):" ;
            cin >> featureNum;
            if(featureNum < 0 || featureNum > MAX_FEATURES)
            {
                cout << "feature num invalid" << endl;
                break;
            }

    		cout << "Running the SVD predictor" << endl;
    		al = new SVD(mRs, uRs, pRs, featureNum);
    		break;
    	}
    	case 4:
        {
            int kValue = 0;
            cout << "SVD blend KNN" << endl;
    		cout << "Choose a k value from 1 to " << MOVIE_NUM << endl;
            
            cin >> kValue;
            if(kValue < 0 || kValue > MOVIE_NUM)
            {
                cout << "kValue invalid" << endl;
                break;
            }
            int featureNum = 0;
            cout << "specify how many features(1 to " << MAX_FEATURES << "):" ;
            cin >> featureNum;
            if(featureNum < 0 || featureNum > MAX_FEATURES)
            {
                cout << "Feature num invalid" << endl;
                break;
            }
            cout << "Running the SVD predictor" << endl;
    		pSVD = new SVD(mRs, uRs, pRs, featureNum);
            cout << "Running KNN predictor, Pearson correlation for item-item similarity, k = " << kValue << endl;
            al = new KNN(mRs, uRs, pRs, pSVD, kValue, SVD_FEATURE_SIM_M);
        }
    		break;
    	default:
    		cout << "option number is wrong, please try again!" << endl;
    		break;
    }
    
    if(al != NULL)
    {
        rmse = al->predictRatings();
        cout << "RMSE: " << rmse << endl;
    }
    
    if(mRs != NULL) delete mRs;
    if(uRs != NULL) delete uRs;
    if(pRs != NULL) delete pRs;
    if(al  != NULL) delete al;
    if(pSVD != NULL) delete pSVD;
    return 0;
}

