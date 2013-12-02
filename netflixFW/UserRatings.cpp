//
//  UserRatings.cpp
//  CS5228Project
//
//  Created by OrangeR on 15/11/13.
//  Copyright (c) 2013 OrangeR. All rights reserved.
//

#include "UserRatings.h"

UserRatings::UserRatings():Ratings()
{
    //Ratings();
    for(int i = 0; i < USER_NUM; i ++)
    {
        means[i] = 0;
        std_devs[i] = 0;
        bias[i] = 0;
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
    return uInt(perUserRatings[uId - 1]->size());
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

uByte UserRatings::getRating(uInt mId, uInt uId)
{
    return 1;
}

void UserRatings::getRatings(uInt uId, std::vector<uRatings> &uRs)
{
    for(std::vector<uRatings>::iterator it = perUserRatings[uId - 1]->begin(); it != perUserRatings[uId - 1]->end(); ++ it)
    {
        uRs.push_back(*it);
    }
}

std::vector<uRatings>& UserRatings::operator[](uInt uId)
{
    return *(perUserRatings[uId - 1]);
}

void UserRatings::computeAllMeans()
{
    if(isMeansComputed)
        return ;
    else
    {
        for(int i = 0; i < USER_NUM; i ++)
        {
            double sum = 0;
            for(std::vector<uRatings>::iterator it = perUserRatings[i]->begin(); it != perUserRatings[i]->end(); ++ it)
            {
                sum += it->getValue();
            }
            means[i] = sum / perUserRatings[i]->size();
        }
        isMeansComputed = true;
    }
}

void UserRatings::dumpAllMeans()
{
    for(int i = 0; i < USER_NUM; i ++)
        std::cout << "User " << i + 1 << "'s mean:" << means[i] << std::endl;
}

double UserRatings::getMean(uInt uId)
{
    return means[uId -1];
}

double* UserRatings::getAllMeans()
{
    if(isMeansComputed)
        return means;
    else
        return NULL;
}

void UserRatings::computeAllStdDevs()
{
    if(!isStdDevsComputed)
    {
        if(isMeansComputed)
            computeAllMeans();
        
        for(int i = 0; i < USER_NUM; i ++)
        {
            double sum = 0;
            for(std::vector<uRatings>::iterator it = perUserRatings[i]->begin(); it != perUserRatings[i]->end(); ++ it)
            {
                sum += pow(it->getValue(), 2);
            }
            std_devs[i] = sqrt(sum / perUserRatings[i]->size() - pow(means[i],2));
        }
        isStdDevsComputed = true;
    }
}


void UserRatings::dumpAllStdDevs()
{
    if(isStdDevsComputed)
    {
        for(int i = 0; i < USER_NUM; i ++)
            std::cout << "User " << i + 1 << "'s standard deviation:" << std_devs[i] << std::endl;
    }
}

double UserRatings::getStdDev(uInt uId)
{
    return std_devs[uId -1];
}

double* UserRatings::getAllStdDevs()
{
    if(isStdDevsComputed)
        return std_devs;
    else
        return NULL;
}

void UserRatings::computeAllBias(MovieRatings *mRs) {
	if (isBiasComputed)
		return;
	else {
		for(int i = 0; i < USER_NUM; i ++) {
			double u_dev = 0;
			for(std::vector<uRatings>::iterator it = perUserRatings[i]->begin(); it != perUserRatings[i]->end(); ++ it) {
				u_dev += ((double)it->getValue() - (double)G_MEAN - mRs->getBias(it->getId()));
			}
			bias[i] = u_dev / (double)(USER_BIAS_PARAM + perUserRatings[i]->size());
		}
		isBiasComputed = true;
	}
}

void UserRatings::setBias(uInt uId, double bi)
{
    bias[uId - 1] = bi;
}

double UserRatings::getBias(uInt uId)
{
    if(isBiasComputed)
        return bias[uId - 1];
    else
        return -1;
}

double* UserRatings::getAllBias()
{
    if(isBiasComputed)
        return bias;
    else
        return NULL;
}








