#ifndef CS5228Project_MovieUserRatings_h
#define CS5228Project_MovieUserRatings_h
#include "Ratings.h"
#include <vector>

const uByte UID_MASK = 0x07;
const uByte RATING_MASK = 0x0F;
typedef struct mRatings{
    
    unsigned short userIdHi;
    uByte userIdLo:4, value:4;
    
    mRatings(uInt uId, uByte rating)
    {
        userIdHi = uId >> 3;
        userIdLo = uId & UID_MASK;
        value = rating;
    }
    
    mRatings(unsigned short uIdHi, uByte rating)
    {
        userIdHi = uIdHi;
        value = rating & RATING_MASK;
        userIdLo = (rating - value) >> 4;
    }
    mRatings()
    {
        userIdHi = 0;
        userIdLo = 0;
        value = 0;
    }
    
    uInt getId()
    {
        return (userIdHi * 8) + userIdLo;
    }
    int getValue()
    {
        return int(value);
    }
    uInt getUserId()
    {
        return (userIdHi * 8) + userIdLo;
    }
    void setUerId(uInt uId)
    {
        userIdHi = uId >> 3;
        userIdLo = uId & UID_MASK;
    }
}mRatings;

class MovieRatings:public Ratings{
private:
    double means[MOVIE_NUM];
    double std_devs[MOVIE_NUM];
    double bias[MOVIE_NUM];
    std::vector<mRatings> * perMovieRatings[MOVIE_NUM];
    bool isMeansComputed;
    bool isStdDevsComputed;
    bool isBiasComputed;
public:
    MovieRatings();
    ~MovieRatings();
    
    uInt getMovieNum();
    uInt getSupport(uInt mId);
    
    void addRating(uInt mId, mRatings mR);
    void dumpRatings(uInt mId);
    uByte getRating(uInt mId, uInt uId);
    void getRatings(uInt mId, std::vector<mRatings> &mR);
    std::vector<mRatings>& operator[](uInt mId);

    void computeAllMeans();
    void dumpAllMeans();
    double getMean(uInt mId);
    double* getAllMeans();
    
    void computeAllStdDevs();
    void dumpAllStdDevs();
    double getStdDev(uInt mId);
    double* getAllStdDevs();

    void computeAllBias();
    void setBias(uInt mId, double bi);
    double getBias(uInt mId);
    double* getAllBias();
};
#endif
