#ifndef CS5228Project_Algorithm_h
#define CS5228Project_Algorithm_h
#include "MovieRatings.h"
#include "UserRatings.h"
#include "ProbeRatings.h"
#include "Database.h"
#include "Helper.h"
#include "Config.h"

// defines for SVD
#define MAX_FEATURES    64
#define MIN_EPOCHS      120           // Minimum number of epochs per feature
#define MAX_EPOCHS      200           // Max epochs per feature

#define MIN_IMPROVEMENT 0.0001        // Minimum improvement required to continue current feature
#define INIT            0.1           // Initialization value for features
#define LRATE           0.001         // Learning rate parameter
#define K               0.015         // Regularization parameter used to minimize over-fitting


class Algorithm{
public:
	Algorithm(MovieRatings *mRs, UserRatings *uRs, ProbeRatings *pRs);
	~Algorithm();

	void setMovie(uInt movieId);
	double determine(uInt userId);
	double calBaselineEst(uInt movieId, uInt userId);
	void predictRatings();
    //void runPearsonCC();
    //void runKNN();

    void runSVD();
    void calculateFeatures();

private:
	MovieRatings *mRs;
	UserRatings *uRs;
	ProbeRatings *pRs;
	uInt currentMovieId;
};
#endif
