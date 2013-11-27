#include "Algorithm.h"

#define USER_DEV_PARAM  10
#define MOVIE_DEV_PARAM 25


Algorithm::Algorithm(MovieRatings *mRs, UserRatings *uRs, ProbeRatings *pRs): mRs(mRs), uRs(uRs),
		pRs(pRs), currentMovieId(0)
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

void Algorithm::predictRatings() {
	std::vector<mRatings> realpRs;
	for (uInt mIdx = 0; mIdx < pRs->getPredictedMovieNum(); ++mIdx)
	{
		uShort movieId;
		pRs->getRatings(mIdx, movieId, realpRs);
		for (std::vector<mRatings>::iterator it = realpRs.begin(); it != realpRs.end(); ++ it)
		{
			uInt userId = it->getUserId();
			double predRating = calBaselineEst(movieId, userId);
			// cout << "MovieId: " << movieId << "\tUserId: " << userId << "\trating: " << predRating << endl;
//			pRs->addRatings(predRating);
		}
	}
}


double Algorithm::calBaselineEst(uInt movieId, uInt userId) {
	double m_bias = mRs -> getBias(movieId);
	double u_bias = uRs -> getBias(userId);
	double baselineEst = (double)G_MEAN + m_bias + u_bias;

	if (baselineEst > 5) baselineEst = 5;
	else if (baselineEst < 1) baselineEst = 1;

	return baselineEst;
}


void Algorithm::runSVD() {

}


void Algorithm::calculateFeatures() {
	float userFeatures[MAX_FEATURES][USER_NUM];   	// Array of features by user
	float movieFeatures[MAX_FEATURES][MOVIE_NUM];  	// Array of features by movie
	float cache[RATINGS_NUM];

	double err, p, sq, rmse_last, rmse = 2.0;
	float cf, mf;

}




