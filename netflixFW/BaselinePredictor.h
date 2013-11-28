#ifndef BASELINEPREDICTOR_H_
#define BASELINEPREDICTOR_H_

#include "Algorithm.h"

class BaselinePredictor : Algorithm {
public:
	BaselinePredictor(MovieRatings *mRs, UserRatings *uRs, ProbeRatings *pRs);
	virtual ~BaselinePredictor();
	double calBaselineEst(uInt movieId, uInt userId);
	void predictRatings();

private:
	MovieRatings *mRs;
	UserRatings *uRs;
	ProbeRatings *pRs;
	uInt currentMovieId;
};

#endif /* BASELINEPREDICTOR_H_ */
