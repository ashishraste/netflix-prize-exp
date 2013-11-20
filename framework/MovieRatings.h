//
//  MovieUserRatings.h
//  CS5228Project


#ifndef framework_MovieUserRatings_h
#define framework_MovieUserRatings_h
#include "Ratings.h"
#include <vector>
const int UID_MASK = 0x07;

typedef struct mRatings{
    unsigned short userIdHi;
    uByte userIdLo:4, value:4;
    
    mRatings(uInt uId, uByte rating)
    {
        userIdHi = uId >> 3;
        userIdLo = uId & UID_MASK;
        value = rating;
    }
    mRatings()
    {
        userIdHi = 0;
        userIdLo = 0;
        value = 0;
    }
    uInt getUserId()
    {
        return (userIdHi << 3) + userIdLo & UID_MASK;
    }
    void setUerId(uInt uId)
    {
        userIdHi = uId >> 3;
        userIdLo = uId & UID_MASK;
    }
}mRatings;

//class MovieRatings:public Ratings{
class MovieRatings{
private:

    //std::vector<float> means;
    //std::vector<float> std_devs;
    double means[MOVIE_NUM];
    double std_devs[MOVIE_NUM];
    std::vector<mRatings> * perMovieRatings[MOVIE_NUM];
protected:
    //int binarySearch(std::vector<mRatings> &p, mRatings &mR);
    int binarySearch(std::vector<mRatings> &p, mRatings &mR);
    uInt binarySearchInsert(std::vector<mRatings> &p, mRatings mR);
public:

    MovieRatings();
    ~MovieRatings();
    bool isMovieRatedByUser(uInt mId, mRatings &mR);
    void dumpStd_dev();
    void dumpRatings(uInt mId);
    void addRatingWithAscending(uInt mId, mRatings mR);
    void addRating(uInt mId, mRatings mR);
    uInt getMovieNum();
    uInt getSupport(uInt mId);
    float computeMean(uInt mId);
    float computeStd_dev(uInt mId);
    float getMean(uInt mId);
    float getStd_dev(uInt mId);
    uByte getRating(uInt mId, uInt uId);
    void getRating(uInt mId, uInt idx, mRatings &mR);
};
#endif
