#ifndef CS5228Project_ProbeRatings_h
#define CS5228Project_ProbeRatings_h
//#include "Helper.h"
#include "MovieRatings.h"
#include "UserRatings.h"
//#include "helper"
//#include "Database.h"
#include <string>
#include <utility>
/*
typedef struct mIdIdx{
    unsigned short mId;
    unsigned short idx;
    
    mIdIdx(){
        mId = 0;
        idx = 0;
    }
    
    mIdIdx(unsigned short m, unsigned short i)
    {
        mId = m;
        idx = i;
    }
    
    uInt getId()
    {
        return mId;
    }
    
    uInt getValue()
    {
        return idx;
    }
    
    void setId(unsigned short m)
    {
        mId = m;
    }
    void setValue(unsigned short i)
    {
        idx = i;
    }

}mIdIdx;
*/

class ProbeRatings:public Ratings
{
private:
    std::vector< std::vector<mRatings>* > *realRatings;
    std::vector<double> *predictedRatings;
    std::vector<uShort> mIds;
    double m_rmse;
public:
    ProbeRatings();
    ~ProbeRatings();
    uInt getPredictedMovieNum();
    
    void addRatings(double &prediction);
    void addRatings(uShort movieId, std::vector<mRatings> &pRs);
    void getRatings(uInt idx, uShort &movieId, std::vector<mRatings> &pRs);
    void dumpAllRatings();
    void dumpRatings(uInt idx);
    //void dumpAllPredictedRatings();
    //void dumpPredcitedRatings();
    void savePredictions(const std::string &path, const std::string &file_name);
    double RMSE();
};
#endif
