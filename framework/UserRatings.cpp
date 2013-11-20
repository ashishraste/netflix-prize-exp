//
//  UserRatings.cpp

#include "UserRatings.h"

UserRatings::UserRatings()
{
    //Ratings();
    for(int i = 0; i < USER_NUM; i ++)
    {
        means[i] = 0;
        std_devs[i] = 0;
        std::vector<uRatings> *newUR = new std::vector<uRatings>();
        perUserRatings[i] = newUR;
    }
}

UserRatings::~UserRatings()
{
    for(int i = 0; i < USER_NUM; i ++)
        delete perUserRatings[i];
}

uInt UserRatings::getUserNum()
{
    return USER_NUM;
}

uInt UserRatings::getSupport(uInt uId)
{
    return perUserRatings[uId - 1]->size();
}

float UserRatings::getMean(uInt uId)
{
    //return means.at(uId -1);
    return means[uId -1];
}

float UserRatings::getStd_dev(uInt uId)
{
    //return std_devs.at(uId - 1);
    return std_devs[uId -1];
}

uByte UserRatings::getRating(uInt mId, uInt uId)
{
    return 1;
}

float UserRatings::computeMean(uInt uId)
{
    if(means[uId] > 0)
        return means[uId - 1];
    else
    {
        std::vector<uRatings> *vp = perUserRatings[uId - 1];
        float ratSum = 0;
        for(std::vector<uRatings>::iterator it = vp->begin(); it != vp->end(); ++ it)
        {
            ratSum += int(it->value);
        }
    
        means[uId - 1] = ratSum / perUserRatings[uId - 1]->size();
    }
    return means[uId - 1];
}

void UserRatings::computeMean()
{
    for(int i = 0; i < USER_NUM; i ++)
    {
        computeMean(i + 1);
    }
}

float UserRatings::computeStd_dev(uInt uId)
{
    std::vector<uRatings> *vp = perUserRatings[uId - 1];
    float std_dev = 0;
    for(std::vector<uRatings>::iterator it = (*vp).begin(); it != (*vp).end(); ++ it )
    {
        std_dev += pow(float(it->value), 2);
    }
    std_devs[uId -1] = (sqrt(std_dev / perUserRatings[uId - 1]->size() - pow(means[uId - 1], 2)));
    return std_dev;
}
void UserRatings::computeStd_dev()
{
    for(int i = 0; i < USER_NUM; i ++)
        computeStd_dev(i + 1);
}

uInt UserRatings::binarySearchInsert(std::vector<uRatings> &p, uRatings mR)
{
    if(p.size() == 0)
    {
        p.push_back(mR);
        return 0;
    }
    
    int start = 0;
    int end = p.size() - 1;
    int mid = 0;
    
    while(start <= end){
        mid = (start + end) / 2;
        if(p.at(mid).movieId == mR.movieId)
        {
            return mid;
        }
        else if(p.at(mid).movieId < mR.movieId)
            start = mid + 1;
        else
            end = mid - 1;
    }
    if(p.at(mid).movieId < mR.movieId)
        if(mid == p.size() - 1)
            p.push_back(mR);
        else
            p.insert(p.begin() + mid + 1, mR);
        else
            p.insert(p.begin() + mid, mR);
    
    return mid;
}

void UserRatings::addRatingWithAscending(uInt uId, uRatings uR)
{
    binarySearchInsert(*(perUserRatings[uId - 1]), uR);
}

void UserRatings::addRating(uInt uId, uRatings uR)
{
    perUserRatings[uId -1]->push_back(uR);
}

void UserRatings::dumpRatings(uInt uId)
{
    int num = 1;
    for(std::vector<uRatings>::iterator it = perUserRatings[uId -1]->begin(); it != perUserRatings[uId -1]->end(); ++ it)
    {
        std::cout << num ++ << " " << it->movieId << "," << uInt(it->value) << std::endl;
    }
}

void UserRatings::dumpStd_dev(uInt uId)
{
    std::cout << std_devs[uId -1] << std::endl;;
}

void UserRatings::dumpStd_dev()
{
    for(int i = 0; i < USER_NUM; i ++)
        std::cout << std_devs[i] << std::endl;
}

bool UserRatings::isMovieRatedByUser(uInt mId, uInt uId)
{
    return true;
}
