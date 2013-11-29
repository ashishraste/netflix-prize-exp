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
const uInt K_LIMIT = 500;

enum sim_type{
    PEARSONCC_SIM_U,
    COS_SIM_U,
    PEARSONCC_SIM_M,
    COS_SIM_M,
};

class Similarity
{
public:
    Similarity(){};
    virtual ~Similarity(){};
    virtual double computeSim(uInt id1, uInt id2) = 0;
};

class PearsonCC_Sim_U:public Similarity
{
private:
    MovieRatings *mRs;
    UserRatings  *uRs;
public:
    PearsonCC_Sim_U():Similarity() {};
    PearsonCC_Sim_U(MovieRatings *m, UserRatings *u):Similarity(), mRs(m), uRs(u) {};
    ~PearsonCC_Sim_U() {};
    double computeSim(uInt id1, uInt id2);
};

class PearsonCC_Sim_M:public Similarity
{
private:
    MovieRatings *mRs;
    UserRatings  *uRs;
public:
    PearsonCC_Sim_M():Similarity() {};
    PearsonCC_Sim_M(MovieRatings *m, UserRatings *u):Similarity(), mRs(m), uRs(u) {};
    ~PearsonCC_Sim_M() {};
    double computeSim(uInt id1, uInt id2);
};

class Cosine_Sim_M:public Similarity
{
private:
    MovieRatings *mRs;
public:
    Cosine_Sim_M():Similarity() {};
    Cosine_Sim_M(MovieRatings *m):Similarity(), mRs(m) {};
    ~Cosine_Sim_M() {};
    double computeSim(uInt id1, uInt id2);
};

class Cosine_Sim_U:public Similarity
{
private:
    UserRatings  *uRs;
public:
    Cosine_Sim_U():Similarity() {};
    Cosine_Sim_U(UserRatings *u):Similarity(), uRs(u) {};
    ~Cosine_Sim_U() {};
    double computeSim(uInt id1, uInt id2);
};


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
    
    vector<objectSim>* pMovieKNN;
    vector<objectSim>* pUserKNN;
    
    void computeUserKNN(uInt mId, uInt uId);
    void computeMovieKNN(uInt mId, uInt uId);
    double runUserPredictor();
    double runMoviePredictor();
public:
    KNN();
    KNN(MovieRatings *mrs, UserRatings *urs, ProbeRatings *prs, int k, sim_type simT = PEARSONCC_SIM_M);
    ~KNN();
    
    virtual double predictRatings();
};


#endif
