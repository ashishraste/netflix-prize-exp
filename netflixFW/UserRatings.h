#ifndef CS5228Project_UserMovieRatings_h
#define CS5228Project_UserMovieRatings_h

#include "Ratings.h"
#include "MovieRatings.h"
#include <vector>

typedef struct uRatings{
    unsigned short movieId;
    uByte value:4;
    
    uRatings(unsigned short mId, uByte rating)
    {
        movieId = mId;
        value = rating;
    }
    uRatings()
    {
        movieId = 0;
        value = 0;
    }
    
    uInt getId()
    {
        return movieId;
    }
    
    int getValue()
    {
        return int(value);
    }
    
    uInt getSortingV()
    {
        return getId();
    }
    
    uRatings operator=(const uRatings &source)
    {
        movieId = source.movieId;
        value = source.value;
        return source;
    }
}uRatings;

class UserRatings:public Ratings{
private:
    double means[USER_NUM];
    double std_devs[USER_NUM];
    double bias[USER_NUM];
    std::vector<uRatings> * perUserRatings[USER_NUM];
    bool isMeansComputed;
    bool isStdDevsComputed;
    bool isBiasComputed;
    
public:
    UserRatings();
    ~UserRatings();

    uInt getUserNum();
    uInt getSupport(uInt uId);
    
    void addRating(uInt uId, uRatings uR);
    void dumpRatings(uInt uId);
    uByte getRating(uInt mId, uInt uId);
    void getRatings(uInt uId, std::vector<uRatings> &uRs);
    std::vector<uRatings>& operator[](uInt uId);

    void computeAllMeans();
    void dumpAllMeans();
    double getMean(uInt uId);
    double* getAllMeans();
    
    void computeAllStdDevs();
    void dumpAllStdDevs();
    double getStdDev(uInt uId);
    double* getAllStdDevs();
    
    void computeAllBias(MovieRatings *mRs);
    void setBias(uInt uId, double bu);
    double getBias(uInt uId);
    double* getAllBias();
};
#endif
