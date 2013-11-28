#ifndef CS5228Project_Algorithm_h
#define CS5228Project_Algorithm_h

#define MAX_RATINGS     100480508     // Ratings in entire training set (+1)
#define MAX_CUSTOMERS   480190        // Customers in the entire training set (+1)
#define MAX_MOVIES      17771         // Movies in the entire training set (+1)
#define MAX_FEATURES    64            // Number of features to use
#define MIN_EPOCHS      120           // Minimum number of epochs per feature
#define MAX_EPOCHS      200           // Max epochs per feature

#define MIN_IMPROVEMENT 0.0001        // Minimum improvement required to continue current feature
#define INIT            0.1           // Initialization value for features
#define LRATE           0.001         // Learning rate parameter
#define K               0.015         // Regularization parameter used to minimize over-fitting

#include "MovieRatings.h"
#include "UserRatings.h"
#include "ProbeRatings.h"
#include "Database.h"
#include "Helper.h"
#include "Config.h"

class SVD {
public:
	SVD(MovieRatings *mRs, UserRatings *uRs, ProbeRatings *pRs);
	virtual ~SVD();

	void determine();
	void predictRatings();
	void calculateFeatures();

private:
	uInt currentMovieId;
	MovieRatings *mRs;
	UserRatings *uRs;
	ProbeRatings *pRs;
};

#endif /* CS5228Project_Algorithm_h */
