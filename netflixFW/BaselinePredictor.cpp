#include "BaselinePredictor.h"

BaselinePredictor::BaselinePredictor(MovieRatings *mRs, UserRatings *uRs, ProbeRatings *pRs)
 				: Algorithm(), mRs(mRs), uRs(uRs), pRs(pRs)
{
	double rmse = predictRatings();
	cout << "RMSE: " << rmse << endl;
}

BaselinePredictor::~BaselinePredictor()
{}

double BaselinePredictor::predictRatings() {
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
			pRs->addRatings(predRating);
		}
	}
	cout << "Calculating RMSE" << endl;
	double rmse = pRs->RMSE();
	return rmse;
}

double BaselinePredictor::calBaselineEst(uInt movieId, uInt userId) {
	double m_bias = mRs->getBias(movieId);
	double u_bias = uRs->getBias(userId);
	double baselineEst = (double)G_MEAN + m_bias + u_bias;

	if (baselineEst > 5) baselineEst = 5;
	else if (baselineEst < 1) baselineEst = 1;

	return baselineEst;
}
