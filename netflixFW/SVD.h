#ifndef CS5228Project_SVD_h
#define CS5228Project_SVD_h

#include "Algorithm.h"
#include "BaselinePredictor.h"
#include "Similarity.h"
class BaselinePredictor;

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

class SVD : public Algorithm {
public:
	SVD(MovieRatings *mRs, UserRatings *uRs, ProbeRatings *pRs, uInt fNum);
	virtual ~SVD();

	double predictRatings();
	inline double predictRating(uInt movieId, uInt userId, int feature, float cacheVal, bool bTrailing) const;

	void determine();
	void calculateFeatures();
	double calSvdRatings(uInt movieId, uInt userId);

	BaselinePredictor *bp;

	//friend class Similarity;
    friend class SVD_Sim_M;
    friend class SVD_Sim_U;
private:
	MovieRatings *mRs;
	UserRatings *uRs;
	ProbeRatings *pRs;

    uInt feature_num;
	float userFeatures[MAX_FEATURES][USER_NUM];   	// Array of features by user
	float movieFeatures[MAX_FEATURES][MOVIE_NUM];  	// Array of features by movie
	float cache[RATINGS_NUM];
};

#endif /* CS5228Project_SVD_h */
