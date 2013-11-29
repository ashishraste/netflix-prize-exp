#include <iostream>
#include <string>
#include "Config.h"
#include "UserRatings.h"
#include "MovieRatings.h"
#include "Database.h"
#include "BaselinePredictor.h"
#include "SVD.h"
#include "KNN.h"

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

//    vector<uRatings> userRs = (*uRs)[1];
//    cout << "num of ratings: " << userRs.size() << endl;
//    for (int i=0; i < userRs.size(); ++i) {
//    	cout << "movieId: " << userRs.at(i).getId()  <<  "\trating: " << userRs.at(i).getValue()  << endl;
//    }

    Algorithm *al = NULL;

    int predType;
    double rmse;
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
    		cout << "Running KNN predictor, Pearson correlation for item-item similarity, K=50" << endl;
    		al = new KNN(mRs, uRs, pRs, 50);
    		break;
    	}
    	case 3:
    	{
    		cout << "Running the SVD predictor" << endl;
    		al = new SVD(mRs, pRs);
    		break;
    	}
    	case 4:
    		break;
    	default:
    		cout << "option number is wrong, please try again!" << endl;
    		break;
    }
    rmse = al->predictRatings();
    cout << "RMSE: " << rmse << endl;

    delete mRs;
    delete uRs;
    delete pRs;

    if (NULL != al) delete al;

    return 0;
}

