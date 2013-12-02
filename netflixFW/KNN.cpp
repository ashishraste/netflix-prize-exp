//
//  KNN.cpp
//  CS5228Project
//
//  Created by OrangeR on 28/11/13.
//  Copyright (c) 2013 OrangeR. All rights reserved.
//

#include "KNN.h"
/******************************KNN********************************/
KNN::KNN():Algorithm() {}

KNN::KNN(MovieRatings *mrs, UserRatings *urs, ProbeRatings *prs, SVD *psvd, int k, sim_type simT):Algorithm()
{
    mRs = mrs;
    uRs = urs;
    pRs = prs;
    k_value = k;
    sim_T = simT;

    pmovieSimCache = new float[M_CACHE_SIZE];
    for(uInt i = 0; i < M_CACHE_SIZE; i ++)
    {
        pmovieSimCache[i] = -2;
    }
    switch (simT) {
        case PEARSONCC_SIM_M:
            sim = new PearsonCC_Sim_M(mRs, uRs);
            break;
        case PEARSONCC_SIM_U:
            sim = new PearsonCC_Sim_U(mRs, uRs);
            break;
        case COS_SIM_M:
            sim = new Cosine_Sim_M(mRs);
            break;
        case COS_SIM_U:
            sim = new Cosine_Sim_U(uRs);
            break;
        case SVD_FEATURE_SIM_M:
            sim = new SVD_Sim_M(psvd);
            break;
        case SVD_FEATURE_SIM_U:
            sim = new SVD_Sim_U(psvd);
            break;
        default:
            break;
    }
    filePath = DATABASE_PATH + (sim_T == PEARSONCC_SIM_M ? MOVIEPCCSIMFILE : MOVIECOSSIMFILE);
    if(simT != SVD_FEATURE_SIM_M && simT != SVD_FEATURE_SIM_U)
        loadAllMoviePairSimilarities();
}
KNN::~KNN()
{
    delete []pmovieSimCache;
    if(pMovieKNN != NULL) delete pMovieKNN;
    if(pUserKNN != NULL) delete pUserKNN;
    
    if (sim != NULL) delete  sim;
}

void KNN::computeMovieKNN(uInt mId, uInt uId)
{
    pMovieKNN->clear();
    for(vector<uRatings>::iterator it = (*uRs)[uId].begin(); it != (*uRs)[uId].end(); ++ it)
    {
        if(it->getId() != mId)
        {
            objectSim simTemp = objectSim(it->getId(), it->getValue(), getMoviePairSim(mId, it->getId()));
            if(k_value >= (*uRs)[uId].size())
            {
                pMovieKNN->push_back(simTemp);
            }
            else
            {
                uInt idx = binarySearch<objectSim>(*pMovieKNN, simTemp);
                insert<objectSim>(*pMovieKNN, simTemp, idx);
                if(pMovieKNN->size() > k_value)
                    pMovieKNN->pop_back();
            }
        }
    }
}
void KNN::computeUserKNN(uInt mId, uInt uId)
{
    /*
    pUserKNN->clear();
    for(vector<mRatings>::iterator it = (*mRs)[mId].begin(); it != (*mRs)[mId].end(); ++ it)
    {
        if(it->getId() != uId)
        {
            objectSim simTemp;

            if(k_value >= (*mRs)[uId].size())
            {
                pUserKNN->push_back(simTemp);
            }
            else
            {
                uInt idx = binarySearch<objectSim>(*pUserKNN, simTemp);
                insert<objectSim>(*pUserKNN, simTemp, idx);
                if(pUserKNN->size() > k_value)
                    pUserKNN->pop_back();
            }
        }
    }
     */
}

double KNN::runMoviePredictor()
{
    pMovieKNN = new vector<objectSim>();

    //predict
    for(uInt i = 0; i < pRs->getPredictedMovieNum(); i ++)
    {
        uShort movieId = 0;
        vector<mRatings> mRatsTemp;
        pRs->getRatings(i, movieId, mRatsTemp);
        
        for(vector<mRatings>::iterator it = mRatsTemp.begin(); it != mRatsTemp.end(); ++ it)
        {
            double predRatings = 0;
            double sim_sum = 0;
            computeMovieKNN(movieId, it->getId());
            for(uInt j = 0; j < pMovieKNN->size(); j ++)
            {
                predRatings += (pMovieKNN->at(j).getRating() - mRs->getMean(pMovieKNN->at(j).getId())) * pMovieKNN->at(j).getSim();
                sim_sum += pMovieKNN->at(j).getSim();
            }
            if(pMovieKNN->size() == 0)
            {
                predRatings = mRs->getMean(movieId);
                pRs->addRatings(predRatings);
            }
            else
            {
                predRatings = mRs->getMean(movieId) + predRatings / sim_sum;
                if(predRatings > 5) predRatings = 5;
                else if(predRatings < 1) predRatings = 1;
                pRs->addRatings(predRatings);
            }
            //cout << movieId << "\t" << it->getId() << "\t" << predRatings << endl;
        }
        cout << "Movie " << movieId << endl;
    }
    return pRs->RMSE();
}
double KNN::runUserPredictor()
{
    /*
    pUserKNN = new vector<objectSim>();
    
    for(uInt i = 0; i < pRs->getPredictedMovieNum(); i ++)
    {
        uShort movieId = 0;
        vector<mRatings> mRatsTemp;
        pRs->getRatings(i, movieId, mRatsTemp);
        
        for(vector<mRatings>::iterator it = mRatsTemp.begin(); it != mRatsTemp.end(); ++ it)
        {
            double predRatings = 0;
            double sim_sum = 0;
            computeUserKNN(movieId, it->getId());
            for(uInt j = 0; j < pUserKNN->size(); j ++)
            {
                predRatings += (pUserKNN->at(j).getRating() - uRs->getMean(pUserKNN->at(j).getId())) * pUserKNN->at(j).getSim();
                sim_sum += pUserKNN->at(j).getSim();
            }
            if(pUserKNN->size() == 0)
            {
                predRatings = uRs->getMean(it->getId());
                pRs->addRatings(predRatings);
            }
            else
            {
                predRatings = uRs->getMean(it->getId()) + predRatings / sim_sum;
                if(predRatings > 5) predRatings = 5;
                else if(predRatings < 1) predRatings = 1;
                pRs->addRatings(predRatings);
            }
            //cout << movieId << "\t" << it->getId() << "\t" << predRatings << endl;
        }
        cout << "Movie " << movieId << endl;
     }
    return pRs->RMSE();
     */
    return 0;
}

/*
double KNN::getMovieSim(uInt mId1, uInt mId2)
{
    double similarity = 0;
    uInt id_larger = 0;
    uInt id_smaller = 0;

    mId1 > mId2 ? id_larger = mId1, id_smaller = mId2 : id_larger = mId2, id_smaller = mId1;
    sim_cache cacheUnit = sim_cache(id_larger, 0);
    if(isCacheHit(*(pMovieCache[id_smaller - 1]), cacheUnit))
    {
        similarity = cacheUnit.sim;
    }
    else
    {
        similarity = sim->computeSim(id_smaller, id_larger);
        cacheUnit.sim = similarity;
        cacheSim(*pMovieCache[id_smaller -1], cacheUnit, mCacheUsed, M_CACHE_SIZE);
    }

    return similarity;
}

double KNN::getUserSim(uInt uId1, uInt uId2)
{
    double similarity = 0;
    uInt id_larger = 0;
    uInt id_smaller = 0;
    
    uId1 > uId2 ? id_larger = uId1, id_smaller = uId2 : id_larger = uId2, id_smaller = uId1;
    sim_cache cacheUnit = sim_cache(id_larger, 0);
    if(isCacheHit(*(pUserCache[id_smaller - 1]), cacheUnit))
    {
        similarity = cacheUnit.sim;
    }
    else
    {
        similarity = sim->computeSim(id_smaller, id_larger);
        cacheUnit.sim = similarity;
        cacheSim(*pUserCache[id_smaller -1], cacheUnit, uCacheUsed, U_CACHE_SIZE);
    }
    return similarity;
}
*/

bool KNN::genAllMoviePairSimilarity()
{
    ofstream outFile(filePath.c_str(), ios::out|ios::binary);
    if(outFile.good())
    {
        if(outFile.is_open())
        {
            float val = 0;
            for(uInt i = 1; i <= MOVIE_NUM; i ++)
            {
                for(uInt j = i + 1; j <= MOVIE_NUM; j ++)
                {
                    //cout << i << "\t" << j << "\t" << getMoviePairSim(i, j) << endl;
                    val = getMoviePairSim(i, j);
                    outFile.write((char *)&val, sizeof(val));
                }
                cout << "MovieId :" << i << endl;
            }
        }
        else
        {
            cout << "getAllMoviePairSimilarity" << endl;
        }
        outFile.close();
    }
    return true;
}

bool KNN::loadAllMoviePairSimilarities()
{
    ifstream inFile(filePath.c_str(), ios::in|ios::binary);
    float val = 0;
    if(inFile.good())
    {
        if(inFile.is_open())
        {
            while(!inFile.eof())
            {
                for(uInt i = 0; i < M_CACHE_SIZE; i ++)
                {
                    inFile.read((char *)&val, sizeof(val));
                    if(val != 0.0f)
                    {
                        pmovieSimCache[i] = val;
                    }
                }
            }
        }
        else
        {
            cout << "loadAllMovieSimilarities Failed!" << endl;
        }
        inFile.close();
    }
    else
    {
        cout << "File not exists" << endl;
        genAllMoviePairSimilarity();
    }
    return true;
}

double KNN::getMoviePairSim(uInt mId1, uInt mId2)
{
    if(mId1 == mId2)
        return 1;

    uInt id_smaller, id_larger;

    if(mId1 > mId2)
    {
        id_smaller = mId2;
        id_larger = mId1;
    }
    else
    {
        id_smaller = mId1;
        id_larger = mId2;
    }
    
    uInt idx = 0;
    uInt base = 0;
    for(uInt i = 1; i < id_smaller; i ++)
    {
        base += i;
    }
    idx = MOVIE_NUM * (id_smaller - 1) - base + (id_larger - id_smaller) - 1;
    
    
    if(pmovieSimCache[idx] < -1)
    {
        pmovieSimCache[idx] = float(sim->computeSim(id_smaller, id_larger));
    }
    
    return pmovieSimCache[idx];
}
double KNN::predictRatings()
{
    if(k_value > K_LIMIT)
    {
        cerr << "K is too large, it should be from 1 to 500!" << endl;
        return -1;
    }
    cout << "KNN is Running..." << endl;
    double result = 0;
    cout << genTimeStamp() << endl;
    switch(sim_T)
    {
        case PEARSONCC_SIM_M:
        case COS_SIM_M:
        case SVD_FEATURE_SIM_M:
            result = runMoviePredictor();
            break;
        case PEARSONCC_SIM_U:
        case COS_SIM_U:
        case SVD_FEATURE_SIM_U:
            result = runUserPredictor();
            break;
        default:
            cerr << "Type error in KNN" << endl;
            result = - 1;
    }
    cout << "KNN Finished!!!" << endl;
    cout << genTimeStamp() << endl;
    return result;
}