#include "SVD.h"

SVD::SVD(MovieRatings *mRs, UserRatings *uRs, ProbeRatings *pRs): Algorithm(), mRs(mRs), uRs(uRs),
	pRs(pRs), currentMovieId(0)
{
	for (int f = 0; f < MAX_FEATURES; ++f)
	{
		for (int i = 0; i < MOVIE_NUM; ++i)
			movieFeatures[f][i] = (float)INIT;
		for (int i = 0; i < USER_NUM; i++)
			userFeatures[f][i] = (float)INIT;
	}
	for (int cacheId = 0; cacheId < MAX_RATINGS; ++cacheId)
		cache[cacheId] = 0.0;

	calculateFeatures();
	predictRatings();
}

SVD::~SVD()
{}

void SVD::determine() {

}


void SVD::predictRatings() {
	std::vector<mRatings> realpRs;

}

void SVD::calculateFeatures() {
	double err, p, sq, prevRmse, rmse = 2.0;
	float cf, mf;

	uInt movieId, userId;
	for (int f = 0; f < 2 && f < MAX_FEATURES; ++f) {
		cout << "Calculating feature: " << f << endl;

		for (int e = 0; (e < MIN_EPOCHS) || (rmse <= prevRmse - MIN_IMPROVEMENT); ++e) {
			sq = 0;
		    prevRmse = rmse;
		    int cacheId = 0;
		    for (int i = 0; i < USER_NUM; ++i) {

		    }
		}

	}


}
