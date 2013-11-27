#include "Algorithm.h"

//#define G_MEAN          3.604
#define USER_DEV_PARAM  10
#define MOVIE_DEV_PARAM 25


Algorithm::Algorithm(Database *db, MovieRatings *mRs, UserRatings *uRs): db(db),
		mRs(mRs), uRs(uRs), m_dev(0), u_dev(0), currentMovieId(0)
{
	mRs -> computeAllBias();
	uRs -> computeAllBias(mRs);
}

Algorithm::~Algorithm() {}

void Algorithm::setMovie(uInt movieId) {
	currentMovieId = movieId;
}


double Algorithm::determine(uInt userId) {
	// cout << ((*mRs)[1])[0].getValue() << endl;

	return calBaselineEst(currentMovieId, userId);
}

double Algorithm::calBaselineEst(uInt movieId, uInt userId) {
	double m_bias = mRs -> getBias(movieId);
	double u_bias = uRs -> getBias(userId);
	double baselineEst = (double)G_MEAN + m_bias + u_bias;

	if (baselineEst > 5) baselineEst = 5;
	else if (baselineEst < 1) baselineEst = 1;

	return baselineEst;
}



