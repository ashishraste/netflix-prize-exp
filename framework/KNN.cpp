//
//  KNN.cpp
//  CS5228Project
//
//  Created by OrangeR on 15/11/13.
//  Copyright (c) 2013 OrangeR. All rights reserved.
//

#include "KNN.h"

void binarySearchInsert(vector<double> &knnVal, vector<uInt> &knnMId, double pcValue, uInt mId, uInt k)
{
    if(knnVal.size() == 0)
    {
        knnVal.push_back(pcValue);
        knnMId.push_back(mId);
        return;
    }
    
    int start = 0;
    int end= int(knnVal.size() - 1);
    int mid = 0;
    
    double currentValue = 0;
    while(start <= end){
        mid = (start + end) / 2;
        currentValue = knnVal.at(mid);
        if(currentValue == pcValue)
        {
            break;
        }
        else if(currentValue > pcValue)
            start = mid + 1;
        else
            end = mid - 1;
    }
    
    if(knnVal.size() == k)
    {
        if(mid == k -1)
            if(knnVal.at(mid) < pcValue)
            {
                knnVal.insert(knnVal.begin() + mid, pcValue);
                knnVal.erase(knnVal.begin() + knnVal.size() - 1);
                knnMId.insert(knnMId.begin() + mid, mId);
                knnMId.erase(knnMId.begin() + knnMId.size() - 1);
                
            }
            else
            {
                //do nothing
            }
        else
        {
            if(knnVal.at(mid) < pcValue)
            {
                knnVal.insert(knnVal.begin() + mid, pcValue);
                knnMId.insert(knnMId.begin() + mid, mId);
            }
            else
            
            {
                knnVal.insert(knnVal.begin() + mid + 1, pcValue);
                knnMId.insert(knnMId.begin() + mid + 1, mId);
            }
        }
        
    }
    /*
    if((p.at(mid).userIdHi << 3) + p.at(mid).userIdLo < newUId)
        if(mid == p.size() - 1)
            p.push_back(mR);
        else
            p.insert(p.begin() + mid + 1, mR);
        else
            p.insert(p.begin() + mid, mR);
    */
    
    //return mid;

    
}
void kNN_BruteForce(MovieRatings &mRs, uInt K, vector<double> *knnVal, vector<int> *knnMId)
{
    for(uInt i = 0; i < mRs.getMovieNum() - 1; i ++)
    {
        double pcValue = 0;
        for(uInt j = i + 1; j < mRs.getMovieNum(); j ++)
        {
            pcValue = calMMPearsonCorrelation(mRs, i + 1, j + 1);
            
        }
    }
}