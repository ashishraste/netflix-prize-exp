#include "SVD.h"

SVD::SVD(MovieRatings *mRs, UserRatings *uRs, ProbeRatings *pRs): mRs(mRs), uRs(uRs),
	pRs(pRs), currentMovieId(0)
{}

SVD::~SVD() {}

void SVD::determine() {

}


void SVD::predictRatings() {

}

void SVD::calculateFeatures() {
	float userFeatures[MAX_FEATURES][USER_NUM];   	// Array of features by user
	float movieFeatures[MAX_FEATURES][MOVIE_NUM];  	// Array of features by movie
	float cache[RATINGS_NUM];

	double err, p, sq, rmse_last, rmse = 2.0;
	float cf, mf;



}
