#include "BaselinePredictor.h"

BaselinePredictor::BaselinePredictor(MovieRatings *mRs, UserRatings *uRs, ProbeRatings *pRs, baseline_type bType)
 				: Algorithm(), mRs(mRs), uRs(uRs), pRs(pRs)
{
	this->bType = bType;
}

BaselinePredictor::~BaselinePredictor()
{}

double BaselinePredictor::predictRatings() {
	std::vector<mRatings> realpRs;
	if(bType == GLOBAL_BASELINE)
		cout << "Global Baseline on the run" << endl;
	for (uInt mIdx = 0; mIdx < pRs->getPredictedMovieNum(); ++mIdx)
	{
		cout << "movie " << mIdx << endl;
		uShort movieId;
		pRs->getRatings(mIdx, movieId, realpRs);
		for (std::vector<mRatings>::iterator it = realpRs.begin(); it != realpRs.end(); ++ it)
		{
			uInt userId = it->getUserId();
			double predRating;
			switch (bType) {
				case NORMAL_BASELINE:
					// cout << "normal baseline called" << endl;
					predRating = calBaselineEst(movieId, userId);
					break;
				case GLOBAL_BASELINE:
					// cout << "global baseline called" << endl;
					predRating = calGBaselineEst(movieId, userId);
					break;
			}
			// cout << "MovieId: " << movieId << "\tUserId: " << userId << "\trating: " << predRating << endl;
			pRs->addRatings(predRating);
		}
		// realpRs.clear();
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

double BaselinePredictor::calGBaselineEst(uInt movieId, uInt userId) {
	PearsonCC_Sim_M *pCC = new PearsonCC_Sim_M(mRs, uRs);
	double m_bias = mRs->getBias(movieId);
	double u_bias = uRs->getBias(userId);
	double baselineEst = (double)G_MEAN + m_bias + u_bias;

	double gEst = 0;
	double baseRating, oRating;

	vector<uRatings> userRs;
	uRs->getRatings(userId, userRs); 		// ratings by userId

	for(vector<uRatings>::iterator it = userRs.begin(); it != userRs.end(); ++it)
	{
		uInt mId = it->getId();
		oRating = (double)it->getValue();
		baseRating = (double)G_MEAN + mRs->getBias(mId) + u_bias;
		gEst += ((oRating - baseRating) * pCC->computeSim(mId, movieId));
	}
	// userRs.clear();
	delete pCC;
	gEst += baselineEst;
	return gEst;
}
