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
//		double err = 0, errSum = 0;
		cout << "movie " << mIdx+1 << endl;
		uShort movieId;
        realpRs.clear();
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
				default:
					predRating = calBaselineEst(movieId, userId);
					break;
			}
//			err = it->getValue() - predRating ;
//			errSum += (err * err);
//			cout << it->getValue() << " " << predRating << " " << err*err  << endl;
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
	double baselineEst = G_MEAN + m_bias + u_bias;

	if (baselineEst > 5) baselineEst = 5;
	else if (baselineEst < 1) baselineEst = 1;

	return baselineEst;
}

double BaselinePredictor::calGBaselineEst(uInt movieId, uInt userId) {
	PearsonCC_Sim_M *pCC = new PearsonCC_Sim_M(mRs, uRs);
	double u_bias = uRs->getBias(userId);
	double baselineEst = G_MEAN + mRs->getBias(movieId) + u_bias;
	double gEst = 0;

	vector<uRatings> userRs;
	uRs->getRatings(userId, userRs); 		// ratings by userId

	// Rui = Bui + [Sum(Ruj - Buj) * Wij]
	for(vector<uRatings>::iterator it = userRs.begin(); it != userRs.end(); ++it)
	{
		uInt mId = it->getId();
		double diff = (double)it->getValue() - G_MEAN - mRs->getBias(mId) - u_bias;
		gEst += (diff * (pCC->computeSim(mId, movieId) / SIM_FACTOR));
	}
	gEst += baselineEst;

	delete pCC;

	if (gEst > 5) gEst = 5;
	else if (gEst < 1) gEst = 1;

	return gEst;
}
