/*
 * Inspired by Simon Funk's SVD article (http://sifter.org/~simon/journal/20061211.html),
 * and MIT OCW Linear Algebra lecture notes (http://ocw.mit.edu/courses/mathematics/18-06sc-linear-algebra-fall-2011)
 * Will continue to evolve..
 */

#include "SVD.h"

SVD::SVD(MovieRatings *mRs, UserRatings *uRs, ProbeRatings *pRs)
	: Algorithm(), mRs(mRs), uRs(uRs), pRs(pRs)
{
	for (int f = 0; f < MAX_FEATURES; ++f) {
		for (int i = 0; i < MOVIE_NUM; ++i)
			movieFeatures[f][i] = (float)INIT;
		for (int i = 0; i < USER_NUM; i++)
			userFeatures[f][i] = (float)INIT;
	}
	for (int cacheId = 0; cacheId < MAX_RATINGS; ++cacheId)
		cache[cacheId] = 0.0;

	calculateFeatures();
	cout << "\nfinished calculating the features.. whoof~!" << endl;

	double rmse = predictRatings();
	cout << "RMSE: " << rmse << endl;predictRatings();
}

SVD::~SVD()
{}


double SVD::calSvdRatings(uInt movieId, uInt userId) {
    double sum = 1;

    for (int feature = 0; feature < MAX_FEATURES; ++feature) {
        sum += movieFeatures[feature][movieId] * userFeatures[feature][userId];
    }
    if (sum < 1.0) sum = 1.0;
    else if (sum > 5.0) sum = 5.0;
    return sum;
}


double SVD::predictRatings() {
	std::vector<mRatings> realpRs;
	for (uInt mIdx = 0; mIdx < pRs->getPredictedMovieNum(); ++mIdx)
	{
		uShort movieId;
		pRs->getRatings(mIdx, movieId, realpRs);
		for (std::vector<mRatings>::iterator it = realpRs.begin(); it != realpRs.end(); ++ it)
		{
			uInt userId = it->getUserId();
			double predRating = calSvdRatings(movieId, userId);
			// cout << "MovieId: " << movieId << "\tUserId: " << userId << "\trating: " << predRating << endl;
			pRs->addRatings(predRating);
		}
	}
	cout << "Calculating RMSE" << endl;
	double rmse = pRs->RMSE();
	return rmse;
}


inline double SVD::predictRating(uInt movieId, uInt userId, int feature, float cacheVal, bool bTrailing) const
{
    // Get cached value for old features or default to an average
    double sum = (cacheVal > 0) ? cacheVal : 1;

    // current feature's contribution to the rating
    sum += movieFeatures[feature][movieId] * userFeatures[feature][userId];

    // residual values of the ratings are cached
    if (bTrailing)
        sum += (MAX_FEATURES - feature - 1) * (INIT * INIT);
    if (sum < 1.0) sum = 1.0;
    else if (sum > 5.0) sum = 5.0;

    return sum;
}


void SVD::calculateFeatures() {
	double err, predRating, sq, prevRmse, rmse = 2.0;
	float userVal, movieVal;

	int userId;
	std::vector<mRatings> movieRs;

	for (int f = 0; f < 2 && f < MAX_FEATURES; ++f) {
		cout << "Calculating feature " << f << endl;
		for (int e = 0; (e < MIN_EPOCHS) || (rmse <= prevRmse - MIN_IMPROVEMENT); ++e) {
			sq = 0;
		    prevRmse = rmse;
		    int cacheId = 0;
		    for (int i = 1; i <= MOVIE_NUM; ++i) {
		    	movieRs = (*mRs)[i];
		    	for (int j = 0; j < movieRs.size(); ++j) {
		    		userId = movieRs.at(j).getUserId();
		    		predRating = predictRating(i, userId, f, cache[cacheId], true);

		    		err = 1.0 * movieRs.at(j).getValue() - predRating;
		    		sq += err*err;

		    		userVal = userFeatures[f][userId];
		    		movieVal = movieFeatures[f][i];

		    		userFeatures[f][userId] += (float)(LRATE * (err * movieVal - K * userVal));
		    		movieFeatures[f][i] += (float)(LRATE * (err * userVal - K * movieVal));

		    		++cacheId;
		    	}
		    	movieRs.clear();
		    }
		    rmse = sqrt(sq/MAX_RATINGS);
		    cout << "x = " << e * f + e << "\ty = " << rmse << "\te = " << e << endl;
		}
		int cacheId = 0;
		// cache off the residual ratings
		for (int i = 1; i <= MOVIE_NUM; ++i) {
			std::vector<mRatings> movieRs = (*mRs)[i];
		    for (int j = 0; j < movieRs.size(); ++j) {
		    	cache[cacheId] = (float)predictRating(i, movieRs.at(j).getUserId(), f, cache[cacheId], false);
		        ++cacheId;
		    }
		}
	}
}
