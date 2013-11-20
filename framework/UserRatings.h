//
//  UserMovieRatings.h


#ifndef framework_UserMovieRatings_h
#define framework_UserMovieRatings_h
#include "Ratings.h"
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
}uRatings;
//class UserRatings:public Ratings
class UserRatings{
private:
    //std::vector<float> means;
    //std::vector<float> std_devs;
    float means[USER_NUM];
    float std_devs[USER_NUM];
    std::vector<uRatings> * perUserRatings[USER_NUM];
    
    
protected:
    uInt binarySearch(std::vector<uRatings> &p, uRatings uR, int &idx);
    uInt binarySearchInsert(std::vector<uRatings> &p, uRatings uR);
public:
    UserRatings();
    ~UserRatings();
    void dumpRatings(uInt uId);
    void dumpStd_dev(uInt uId);
    void dumpStd_dev();
    bool isMovieRatedByUser(uInt mId, uInt uId);
    void addRatingWithAscending(uInt uId, uRatings uR);
    void addRating(uInt uId, uRatings uR);
    uInt getUserNum();
    uInt getSupport(uInt uId);
    void computeMean();
    float computeMean(uInt uId);
    void computeStd_dev();
    float computeStd_dev(uInt uId);
    float getMean(uInt uId);
    float getStd_dev(uInt uId);
    uByte getRating(uInt mId, uInt uId);
};
#endif
