#ifndef CS5228Project_Algorithm_h
#define CS5228Project_Algorithm_h
#include "MovieRatings.h"
#include "UserRatings.h"
#include "Database.h"
#include "Helper.h"
#include "Config.h"

class Algorithm{
public:
	Algorithm(Database *db, MovieRatings *mRs, UserRatings *uRs);
	~Algorithm();

	void setMovie(uInt movieId);
	double determine(uInt userId);
	double calBaselineEst(uInt movieId, uInt userId);
//	void predictRatings();

    //void runPearsonCC();
    //void runKNN();
    //void runSVD();

private:
	float m_dev, u_dev;
	Database *db;
	MovieRatings *mRs;
	UserRatings *uRs;
	uInt currentMovieId;
};
#endif
