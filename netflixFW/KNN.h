//
//  KNN.h
//  CS5228Project
//
//  Created by OrangeR on 28/11/13.
//  Copyright (c) 2013 OrangeR. All rights reserved.
//

#ifndef CS5228Project_KNN_h
#define CS5228Project_KNN_h
#include "Algorithm.h"
#include "Similarity.h"

const uInt M_CACHE_SIZE = (MOVIE_NUM - 1) * MOVIE_NUM / 2;
const uInt U_CACHE_SIZE = USER_NUM / 24 * (USER_NUM + 1) / 100;
const uInt K_LIMIT = MOVIE_NUM + 1;


typedef struct objectSim{
    uInt itemId;
    uByte rating;
    float sim;
    objectSim()
    {
        itemId = 0;
        rating = 0;
        sim = 0;
    }
    objectSim(uInt i, uByte r, float s)
    {
        itemId = i;
        rating = r;
        sim = s;
    }
    
    uInt getId(){ return itemId;}
    uByte getRating() {return rating;}
    float getSim(){ return sim;}
    float getSortingV(){return sim;}
    objectSim operator=(const objectSim &source)
    {
        itemId = source.itemId;
        rating = source.rating;
        sim = source.sim;
        return source;
    }
}objectSim;

typedef struct sim_cache{
    uInt itemId;
    float sim;
    sim_cache()
    {
        itemId = 0;
        sim = 0;
    }
    sim_cache(uInt i, float s)
    {
        itemId = i;
        sim = s;
    }
    uInt getSortingV() { return itemId;}
    sim_cache operator=(const sim_cache &source)
    {
        itemId = source.itemId;
        sim = source.sim;
        return source;
    }
    bool operator== (const sim_cache &source)
    {
        if(itemId == source.itemId)
            return true;
        else
            return false;
    }
}sim_cache;

class KNN:public Algorithm
{
private:
    MovieRatings *mRs;
    UserRatings  *uRs;
    ProbeRatings *pRs;
    Similarity   *sim;
    int k_value;
    sim_type sim_T;
    uInt mCacheUsed;
    uInt uCacheUsed;
    string filePath;
    //vector<sim_cache>* pMovieCache[MOVIE_NUM];
    //vector<sim_cache>* pUserCache[USER_NUM];
    //float pmovieSimCache[M_CACHE_SIZE];
    float *pmovieSimCache;
    vector<objectSim>* pMovieKNN;
    vector<objectSim>* pUserKNN;
    
    bool genAllMoviePairSimilarity();
    bool loadAllMoviePairSimilarities();
    void computeUserKNN(uInt mId, uInt uId);
    void computeMovieKNN(uInt mId, uInt uId);
    double runUserPredictor();
    double runMoviePredictor();
    //void cacheMovieSim(const sim_cache &cacheUint);
    //void cacheUserSim(const sim_cache &cacheUint);
    //void
    //void cacheSim(vector<sim_cache> &p, sim_cache &cacheUnit, uInt &cacheUsed, const uInt cacheLimit);
    //bool isCacheHit(vector<sim_cache> &p, sim_cache &cacheUnit);
    //double fetchSimFromCache(uInt id_smaller, uInt id_larger);
public:
    KNN();
    KNN(MovieRatings *mrs, UserRatings *urs, ProbeRatings *prs, SVD *psvd, int k, sim_type simT = PEARSONCC_SIM_M);
    ~KNN();
    double getMoviePairSim(uInt mId1, uInt mId2);
    //double getUserSim(uInt uId1, uInt uId2);
    virtual double predictRatings();
};


#endif
