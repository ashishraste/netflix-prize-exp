//
//  Similarity.h
//  CS5228Project
//
//  Created by OrangeR on 1/12/13.
//  Copyright (c) 2013 OrangeR. All rights reserved.
//

#ifndef CS5228Project_Similarity_h
#define CS5228Project_Similarity_h
#include "SVD.h"
#include "Config.h"
class SVD;
enum sim_type{
    PEARSONCC_SIM_U,
    COS_SIM_U,
    PEARSONCC_SIM_M,
    COS_SIM_M,
    SVD_FEATURE_SIM_M,
    SVD_FEATURE_SIM_U
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

class SVD_Sim_M:public Similarity
{
private:
    SVD * pSVD;
public:
    SVD_Sim_M():Similarity() {};
    SVD_Sim_M(SVD *p):Similarity(), pSVD(p) {};
    ~SVD_Sim_M() {};
    double computeSim(uInt id1, uInt id2);
};

class SVD_Sim_U:public Similarity
{
private:
    SVD *pSVD;
public:
    SVD_Sim_U():Similarity() {};
    SVD_Sim_U(SVD *p):Similarity(), pSVD(p) {};
    ~SVD_Sim_U() {};
    double computeSim(uInt id1, uInt id2);
};


#endif
