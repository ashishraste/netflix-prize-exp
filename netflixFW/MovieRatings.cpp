//
//  MovieRatings.cpp
//  CS5228Project
//
//  Created by OrangeR on 15/11/13.
//  Copyright (c) 2013 OrangeR. All rights reserved.
//

#include "MovieRatings.h"

MovieRatings::MovieRatings():Ratings()
{
    for(int i = 0; i < MOVIE_NUM; i ++)
    {
        means[i] = 0;
        std_devs[i] = 0;
        bias[i] = 0;
        std::vector<mRatings> *newMR = new std::vector<mRatings>();
        perMovieRatings[i] = newMR;
    }
    isBiasComputed = false;
    isMeansComputed = false;
    isStdDevsComputed = false;
}

MovieRatings::~MovieRatings()
{
    for(int i = 0; i < MOVIE_NUM; i++)
        delete perMovieRatings[i];
}

uInt MovieRatings::getMovieNum()
{
    return MOVIE_NUM;
}

uInt MovieRatings::getSupport(uInt mId)
{
    return uInt(perMovieRatings[mId -1]->size());
}

uByte MovieRatings::getRating(uInt mId, uInt uId)
{
    return perMovieRatings[mId -1]->at(uId - 1).getValue();
}

void MovieRatings::addRating(uInt mId, mRatings mR)
{
    perMovieRatings[mId -1]->push_back(mR);
}

void MovieRatings::dumpRatings(uInt mId)
{
    int num = 1;
    for(std::vector<mRatings>::iterator it = perMovieRatings[mId -1]->begin(); it != perMovieRatings[mId -1]->end(); ++ it)
    {
        std::cout << num ++ << " " << it->getId() << " " << it->getValue() << std::endl;
    }
}

void MovieRatings::getRatings(uInt mId, std::vector<mRatings> &mRs)
{
    for(std::vector<mRatings>::iterator it = perMovieRatings[mId -1]->begin(); it != perMovieRatings[mId - 1]->end(); ++ it)
        mRs.push_back(*it);
}

std::vector<mRatings>& MovieRatings::operator[](uInt mId)
{
    return *(perMovieRatings[mId - 1]);
}

void MovieRatings::computeAllMeans()
{
    if(isMeansComputed)
        return;
    else
    {
        for(int i = 0; i < MOVIE_NUM; i ++)
        {
            double sum = 0;
            for(std::vector<mRatings>::iterator it = perMovieRatings[i]->begin(); it != perMovieRatings[i]->end(); ++ it)
            {
                sum += it->getValue();
            }
            means[i] = sum / perMovieRatings[i]->size();
        }
        isMeansComputed = true;
    }
}

void MovieRatings::dumpAllMeans()
{
    if(isMeansComputed)
    {
        for(int i = 0; i < MOVIE_NUM; i ++)
            std::cout << "Movie " << i + 1 << "'s mean: " << means[i] << std::endl;
    }
    else
    {
        std::cerr << "Means are not computed" << std::endl;
        return;
    }
}

double MovieRatings::getMean(uInt mId)
{
    if(isMeansComputed)
        return means[mId -1];
    else
    {
        std::cerr<< "Movie " << mId << "'s mean are not computed" << std::endl;
        return -1;
    }
}

double* MovieRatings::getAllMeans()
{
    if(isMeansComputed)
        return means;
    else
        return NULL;
}

void MovieRatings::computeAllStdDevs()
{
    if(!isStdDevsComputed)
    {
        if(!isMeansComputed)
            computeAllMeans();
        
        for(int i = 0; i < MOVIE_NUM; i ++)
        {
            double sum = 0;
            for(std::vector<mRatings>::iterator it = perMovieRatings[i]->begin(); it != perMovieRatings[i]->end(); ++ it)
            {
                sum += pow(it->getValue(),2);
            }
            std_devs[i] = sqrt(sum / perMovieRatings[i]->size() - pow(means[i],2));
        }
        isStdDevsComputed = true;
    }
}

void MovieRatings::dumpAllStdDevs()
{
    for(int i = 0; i < MOVIE_NUM ; i ++)
    {
        std::cout << "Movie " << i + 1 << "'s standard deviation:" << std_devs[i] << std::endl;
    }
}

double MovieRatings::getStdDev(uInt mId)
{
    if(isStdDevsComputed)
        return std_devs[mId -1];
    else
    {
        std::cerr<< "Standard deviations are not computed" << std::endl;
        return -1;
    }
}

double* MovieRatings::getAllStdDevs()
{
    if(isStdDevsComputed)
        return std_devs;
    else
        return NULL;
}

void MovieRatings::computeAllBias(){
	if (isBiasComputed)
		return;
	else {
		for(int i = 0; i < MOVIE_NUM; i ++) {
			double m_dev = 0;
			for(std::vector<mRatings>::iterator it = perMovieRatings[i]->begin(); it != perMovieRatings[i]->end(); ++ it) {
				m_dev += ((double)it->getValue() - (double)G_MEAN);
			}
			bias[i] = m_dev / (double)(MOVIE_BIAS_PARAM + perMovieRatings[i]->size());
		}
		isBiasComputed = true;
	}
}

void MovieRatings::setBias(uInt mId, double bi)
{
    bias[mId - 1] = bi;
}

double MovieRatings::getBias(uInt mId)
{
    if(isBiasComputed)
        return bias[mId - 1];
    else
        return -1;
}

double* MovieRatings::getAllBias()
{
    if(isBiasComputed)
        return bias;
    else
        return NULL;
}
