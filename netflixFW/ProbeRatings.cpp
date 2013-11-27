#include "ProbeRatings.h"
#include <utility>

ProbeRatings::ProbeRatings()
{
	realRatings = new std::vector< std::vector<mRatings>* >();
	predictedRatings = new std::vector<double> ();
}

ProbeRatings::~ProbeRatings()
{
    for(std::vector< std::vector<mRatings>* >::iterator it = realRatings->begin();
        it != realRatings->end(); ++ it)
    {
        std::vector<mRatings>* pTemp = *it;
        pTemp->clear();
        delete pTemp;
    }
    realRatings->clear();
    delete realRatings;
    predictedRatings->clear();
    delete predictedRatings;
}

uInt ProbeRatings::getPredictedMovieNum()
{
    return uInt(mIds.size());
}

void ProbeRatings::addPredictedMId(uShort movieId)
{
    mIds.push_back(movieId);
}

void ProbeRatings::addRatings(double &prediction)
{
    predictedRatings->push_back(prediction);
}

void ProbeRatings::addRatings(uShort movieId, std::vector<mRatings> &pRs)
{
    std::vector<mRatings>* pTemp = new std::vector<mRatings>();
    for(std::vector<mRatings>::iterator it = pRs.begin(); it != pRs.end(); ++ it)
    {
        pTemp->push_back(*it);
    }

    mIds.push_back(movieId);
    realRatings->push_back(pTemp);
}

void ProbeRatings::getRatings(uInt idx, uShort &movieId, std::vector<mRatings> &pRs)
{
    if(idx > mIds.size())
    {
        std::cerr << "ProbeRatings::getRatings, index out of range!" << std::endl;
        return ;
    }
    movieId = mIds.at(idx);
    for(std::vector<mRatings>::iterator it = realRatings->at(idx)->begin(); it != realRatings->at(idx)->end(); ++ it)
    {
        pRs.push_back(*it);
    }
}

void ProbeRatings::dumpAllRatings()
{
    for(int i = 0; i < mIds.size(); i ++)
    {
        dumpRatings(i);
    }
}

void ProbeRatings::dumpRatings(uInt idx)
{
    if(idx > mIds.size() - 1)
    {
        std::cerr << "ProbeRatings::dumpRatings, index out of range!" << std::endl;
        return ;
    }
    else
    {
        // std::cout << " MovieId: " << mIds.at(idx) << ":" << std::endl;
        for(std::vector<mRatings>::iterator it = realRatings->at(idx)->begin(); it != realRatings->at(idx)->end(); ++ it)
        {
            // std::cout << it->getId() << "," << it->getValue() << std::endl;
        }
    }
}

double ProbeRatings::RMSE()
{
    uInt num = 0;
    double rmse = 0;
    for(int i = 0; i < realRatings->size(); i ++)
    {
        num += realRatings->at(i)->size();
    }

    if(num != predictedRatings->size())
    {
        std::cerr << "Prediction is incomplete!" << std::endl;
        return -1;
    }
    else
    {
        uInt index = 0;
        for(int i = 0; i < realRatings->size(); i ++)
        {
            for(std::vector<mRatings>::iterator it = realRatings->at(i)->begin();
                it != realRatings->at(i)->end(); ++ it)
            {
                rmse += pow(predictedRatings->at(index) - it->getValue(), 2);
                index ++;
            }
        }
        return sqrt(rmse / num);
    }
}

