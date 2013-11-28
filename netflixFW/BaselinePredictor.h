#ifndef CS5228Project_BaselinePredictor_h
#define CS5228Project_BaselinePredictor_h

#include "Algorithm.h"

class BaselinePredictor : Algorithm {
public:
	BaselinePredictor(MovieRatings *mRs, UserRatings *uRs, ProbeRatings *pRs);
	virtual ~BaselinePredictor();
	double calBaselineEst(uInt movieId, uInt userId);
	double predictRatings();

private:
	MovieRatings *mRs;
	UserRatings *uRs;
	ProbeRatings *pRs;
};

#endif /* CS5228Project_BaselinePredictor_h */
