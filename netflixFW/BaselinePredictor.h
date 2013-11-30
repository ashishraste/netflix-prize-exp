#ifndef CS5228Project_BaselinePredictor_h
#define CS5228Project_BaselinePredictor_h

#include "Algorithm.h"
#include "KNN.h"

#define SIM_FACTOR 50

enum baseline_type {
	NORMAL_BASELINE,
	GLOBAL_BASELINE,
};

class BaselinePredictor : public Algorithm {
public:
	BaselinePredictor(MovieRatings *mRs, UserRatings *uRs, ProbeRatings *pRs, baseline_type bType = GLOBAL_BASELINE);
	virtual ~BaselinePredictor();
	double calBaselineEst(uInt movieId, uInt userId);
	double calGBaselineEst(uInt movieId, uInt userId);
	double predictRatings();

private:
	MovieRatings *mRs;
	UserRatings *uRs;
	ProbeRatings *pRs;
	baseline_type bType;
};

#endif /* CS5228Project_BaselinePredictor_h */
