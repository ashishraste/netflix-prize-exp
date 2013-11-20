//
//  MovieRatings.cpp

#include "MovieRatings.h"

MovieRatings::MovieRatings()
{
    //Ratings();
    for(int i = 0; i < MOVIE_NUM; i ++)
    {
        means[i] = 0;
        std_devs[i] = 0;
        std::vector<mRatings> *newMR = new std::vector<mRatings>();
        perMovieRatings[i] = newMR;
    }
}

MovieRatings::~MovieRatings()
{
    for(int i = 0; i < MOVIE_NUM; i++)
        delete perMovieRatings[i];
    //~Ratings();
}

uInt MovieRatings::getSupport(uInt mId)
{
    return perMovieRatings[mId -1]->size();
}

uInt MovieRatings::getMovieNum()
{
    return MOVIE_NUM;
}

float MovieRatings::getMean(uInt mId)
{
    //return means.at(mId -1);
    return means[mId -1];
}


float MovieRatings::getStd_dev(uInt mId)
{
    //return std_devs.at(mId -1);
    return std_devs[mId -1];
}

uByte MovieRatings::getRating(uInt mId, uInt uId)
{
    return 1;
}

float MovieRatings::computeMean(uInt mId)
{
    if(means[mId -1] > 0)
        return means[mId -1];
    else{
        std::vector<mRatings> *vp = perMovieRatings[mId - 1];
        int ratSum = 0;
        for(std::vector<mRatings>::iterator it = vp->begin(); it != vp->end(); ++ it )
        {
            ratSum += int(it->value);
        }
        means[mId - 1] = ratSum / perMovieRatings[mId - 1]->size();
    }
    
    return means[mId -1];
}

float MovieRatings::computeStd_dev(uInt mId)
{
    std::vector<mRatings> *vp = perMovieRatings[mId - 1];
    float std_dev = 0;
    for(std::vector<mRatings>::iterator it = (*vp).begin(); it != (*vp).end(); ++ it )
    {
        std_dev += pow(float((*it).value), 2);
    }
    //std::cout << " " << std_dev << " " << means[mId -1] << " " << perMovieRatings[mId -1]->size() << std::endl;
    std_devs[mId -1] = sqrt(std_dev / perMovieRatings[mId -1]->size() - pow(means[mId - 1], 2));
    //std::cout << std_devs[mId -1] << std::endl;
    return std_dev;
}
int MovieRatings::binarySearch(std::vector<mRatings> &p, mRatings &mR)
{
    int start = 0;
    int end= int(p.size() - 1);
    int mid = 0;
    
    uInt newUId = mR.getUserId();
    while(start <= end){
        mid = (start + end) / 2;
        uInt currentUId = p.at(mid).getUserId();
        if(currentUId == newUId)
        {
            mR.value = p.at(mid).value;
            return mid;
        }
        else if(currentUId < newUId)
            start = mid + 1;
        else
            end = mid - 1;
    }
    mR.value = 0;
    return -1;
}
uInt MovieRatings::binarySearchInsert(std::vector<mRatings> &p, mRatings mR)
{
    if(p.size() == 0)
    {
        p.push_back(mR);
        return 0;
    }
    
    int start = 0;
    int end= int(p.size() - 1);
    int mid = 0;
    
    uInt newUId = (mR.userIdHi << 3) + mR.userIdLo;
    while(start <= end){
        mid = (start + end) / 2;
        uInt currentUId = (p.at(mid).userIdHi << 3) + p.at(mid).userIdLo;
        if(currentUId == newUId)
        
        {
            return mid;
        }
        else if(currentUId < newUId)
            start = mid + 1;
        else
            end = mid - 1;
    }

    if((p.at(mid).userIdHi << 3) + p.at(mid).userIdLo < newUId)
        if(mid == p.size() - 1)
            p.push_back(mR);
        else
            p.insert(p.begin() + mid + 1, mR);
    else
        p.insert(p.begin() + mid, mR);
    
    return mid;
}

void MovieRatings::addRatingWithAscending(uInt mId, mRatings mR)
{
    binarySearchInsert(*(perMovieRatings[mId -1]), mR);
}
void MovieRatings::addRating(uInt mId, mRatings mR)
{
    perMovieRatings[mId -1]->push_back(mR);
}
void MovieRatings::dumpStd_dev()
{
    for(int i = 0; i < MOVIE_NUM ; i ++)
    {
        std::cout << std_devs[i] << std::endl;
    }
}
void MovieRatings::dumpRatings(uInt mId)
{
    int num = 1;
    for(std::vector<mRatings>::iterator it = perMovieRatings[mId -1]->begin(); it != perMovieRatings[mId -1]->end(); ++ it)
    {
        std::cout << num ++ << " " << it->userIdHi << 3 + (it->userIdLo & UID_MASK) << "," << uInt(it->value) << std::endl;
    }
}

bool MovieRatings::isMovieRatedByUser(uInt mId, mRatings &mR)
{
    return (binarySearch(*(perMovieRatings[mId - 1]), mR) < 0 ? false : true);
    //if(search(*(perMovieRatings[mId -1]), mR) < 0)
    //    return false;
    //else
    //    return true;
}
void MovieRatings::getRating(uInt mId, uInt idx, mRatings &mR)
{
    mR.setUerId(perMovieRatings[mId - 1]->at(idx).getUserId());
    mR.value = perMovieRatings[mId -1]->at(idx).value;
}
