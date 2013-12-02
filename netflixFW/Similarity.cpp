//
//  Similarity.cpp
//  CS5228Project
//
//  Created by OrangeR on 1/12/13.
//  Copyright (c) 2013 OrangeR. All rights reserved.
//

#include "Similarity.h"
double PearsonCC_Sim_M::computeSim(uInt id1, uInt id2)
{
    double sim = 0;
    vector<mRatings> *mrs1;
    vector<mRatings> *mrs2;
    //take the smaller vector as the main vector to loop
    if((*mRs)[id1].size() < (*mRs)[id2].size())
    {
        mrs1 = &(*mRs)[id1];
        mrs2 = &(*mRs)[id2];
    }
    else
    {
        mrs1 = &(*mRs)[id2];
        mrs2 = &(*mRs)[id1];
    }
    
    vector<uInt> indices_1;
    vector<uInt> indices_2;
    for(int i = 0; i < mrs1->size(); i ++)
    {
        uInt idx = binarySearch<mRatings>(*mrs2, mrs1->at(i));
        if(mrs2->at(idx).getId() == mrs1->at(i).getId())
        {
            indices_1.push_back(i);
            indices_2.push_back(idx);
        }
    }
    double sum_1 = 0;
    double sum_2 = 0;
    for(int i = 0; i < indices_1.size(); i ++)
    {
        double mean_1 = uRs->getMean(mrs1->at(indices_1.at(i)).getId());
        double mean_2 = uRs->getMean(mrs2->at(indices_2.at(i)).getId());
        double rui_1 = mrs1->at(indices_1.at(i)).getValue();
        double rui_2 = mrs2->at(indices_2.at(i)).getValue();
        sim += (rui_1 - mean_1) * (rui_2 - mean_2);
        sum_1 += pow(rui_1 - mean_1, 2);
        sum_2 += pow(rui_2 - mean_2, 2);
    }
    if(indices_1.size() != 0)
    {
        //cout << sim / (sqrt(sum_1) * sqrt(sum_2)) << endl;
        return sim / (sqrt(sum_1) * sqrt(sum_2));
    }
    else
        return 0;
}

double PearsonCC_Sim_U::computeSim(uInt id1, uInt id2)
{
    double sim = 0;
    vector<uRatings> *urs1;
    vector<uRatings> *urs2;
    //take the smaller vector as the main vector to loop
    if((*uRs)[id1].size() < (*uRs)[id2].size())
    {
        urs1 = &(*uRs)[id1];
        urs2 = &(*uRs)[id2];
    }
    else
    {
        urs1 = &(*uRs)[id2];
        urs2 = &(*uRs)[id1];
    }
    
    vector<uInt> indices_1;
    vector<uInt> indices_2;
    for(int i = 0; i < urs1->size(); i ++)
    {
        uInt idx = binarySearch<uRatings>(*urs2, urs1->at(i));
        if(urs2->at(idx).getId() == urs1->at(i).getId())
        {
            indices_1.push_back(i);
            indices_2.push_back(idx);
        }
    }
    double sum_1 = 0;
    double sum_2 = 0;
    for(int i = 0; i < indices_1.size(); i ++)
    {
        double mean_1 = uRs->getMean(urs1->at(indices_1.at(i)).getId());
        double mean_2 = uRs->getMean(urs2->at(indices_2.at(i)).getId());
        double rui_1 = urs1->at(indices_1.at(i)).getValue();
        double rui_2 = urs2->at(indices_2.at(i)).getValue();
        sim += (rui_1 - mean_1) * (rui_2 - mean_2);
        sum_1 += pow(rui_1 - mean_1, 2);
        sum_2 += pow(rui_2 - mean_2, 2);
    }
    if(indices_1.size() != 0)
    {
        cout << sim / (sqrt(sum_1) * sqrt(sum_2)) << endl;
        return sim / (sqrt(sum_1) * sqrt(sum_2));
    }
    else
        return 0;
}

double Cosine_Sim_M::computeSim(uInt id1, uInt id2)
{
    double sim = 0;
    double len1 = 0;
    double len2 = 0;
    vector<mRatings> *mrs1;
    vector<mRatings> *mrs2;
    
    (*mRs)[id1].size() > (*mRs)[id2].size() ? mrs1 = &(*mRs)[id1],mrs2 = &(*mRs)[id2] : mrs1 = &(*mRs)[id2],mrs2 = &(*mRs)[id1];
    
    uInt idx = 0;
    for(int i = 0; i < mrs1->size(); i ++)
    {
        len1 += pow(mrs1->at(i).getValue(), 2);
        if(idx < mrs2->size())
        {
            uInt position = binarySearch<mRatings>(*mrs1, mrs2->at(idx));
            if(mrs1->at(position).getId() == mrs2->at(idx).getId())
                sim += mrs1->at(position).getValue() * mrs2->at(idx).getValue();
            len2 += pow(mrs2->at(i).getValue(), 2);
            idx ++;
        }
    }
    
    return sim / (sqrt(len1) * sqrt(len2));
}

double Cosine_Sim_U::computeSim(uInt id1, uInt id2)
{
    double sim = 0;
    double len1 = 0;
    double len2 = 0;
    vector<uRatings> *urs1;
    vector<uRatings> *urs2;
    
    (*uRs)[id1].size() > (*uRs)[id2].size() ? urs1 = &(*uRs)[id1],urs2 = &(*uRs)[id2] : urs1 = &(*uRs)[id2],urs2 = &(*uRs)[id1];
    
    uInt idx = 0;
    for(int i = 0; i < urs1->size(); i ++)
    {
        len1 += pow(urs1->at(i).getValue(), 2);
        if(idx < urs2->size())
        {
            uInt position = binarySearch<uRatings>(*urs1, urs2->at(idx));
            if(urs1->at(position).getId() == urs1->at(idx).getId())
                sim += urs1->at(position).getValue() * urs2->at(idx).getValue();
            len2 += pow(urs2->at(i).getValue(), 2);
            idx ++;
        }
    }
    
    return sim / (sqrt(len1) * sqrt(len2));
}

double SVD_Sim_M::computeSim(uInt id1, uInt id2)
{

    double svd_sim = 0;
    double len1 = 0;
    double len2 = 0;
    for(uInt i = 0; i < MAX_FEATURES; i ++)
    {
        svd_sim += pSVD->movieFeatures[id1][i] * pSVD->movieFeatures[id2][i];
        len1 += pow(pSVD->movieFeatures[id1][i], 2);
        len2 += pow(pSVD->movieFeatures[id2][i], 2);
    }
    
    return svd_sim / (sqrt(len1) * sqrt(len2));
}

double SVD_Sim_U::computeSim(uInt id1, uInt id2)
{
    return 0;
}
