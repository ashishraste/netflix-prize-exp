#include "KNN.h"
double PearsonCC_Sim_M::computeSim(uInt id1, uInt id2)
{
    double sim = 0;
    vector<mRatings> *mrs1;
    vector<mRatings> *mrs2;
    //take the smaller vector as the main vector to loop
    (*mRs)[id1].size() < (*mRs)[id2].size() ? mrs1 = &(*mRs)[id1],mrs2 = &(*mRs)[id2] : mrs1 = &(*mRs)[id2],mrs2 = &(*mRs)[id1];
    
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
    (*uRs)[id1].size() < (*uRs)[id2].size() ? urs1 = &(*uRs)[id1],urs2 = &(*uRs)[id2] : urs1 = &(*uRs)[id2],urs2 = &(*uRs)[id1];
    
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
            if(mrs2->at(position).getId() == mrs1->at(i).getId())
                sim += mrs2->at(position).getValue() * mrs1->at(i).getValue();
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
            if(urs2->at(position).getId() == urs1->at(i).getId())
                sim += urs2->at(position).getValue() * urs1->at(i).getValue();
            len2 += pow(urs2->at(i).getValue(), 2);
            idx ++;
        }
    }
    
    return sim / (sqrt(len1) * sqrt(len2));
}

KNN::KNN():Algorithm() {}

KNN::KNN(MovieRatings *mrs, UserRatings *urs, ProbeRatings *prs, int k, sim_type simT):Algorithm()
{
    mRs = mrs;
    uRs = urs;
    pRs = prs;
    k_value = k;
    sim_T = simT;
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
        default:
            break;
    }
}
KNN::~KNN()
{
    if(pMovieKNN != NULL) delete pMovieKNN;
    if(pUserKNN != NULL) delete pUserKNN;
    if (sim != NULL) delete  sim;
    //Algorithm::~Algorithm();
}

void KNN::computeMovieKNN(uInt mId, uInt uId)
{
    pMovieKNN->clear();
    for(vector<uRatings>::iterator it = (*uRs)[uId].begin(); it != (*uRs)[uId].end(); ++ it)
    {
        if(it->getId() != mId)
        {
            //if the both rated item'size is small then the K value, just calculate all the similarities.
            objectSim simTemp = objectSim(it->getId(), it->getValue(), sim->computeSim(mId, it->getId()));
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
    pUserKNN->clear();
    for(vector<mRatings>::iterator it = (*mRs)[mId].begin(); it != (*mRs)[mId].end(); ++ it)
    {
        if(it->getId() != uId)
        {
            objectSim simTemp = objectSim(it->getId(), it->getValue(), sim->computeSim(uId, it->getId()));
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
                pRs->addRatings(predRatings);
            }
            cout << movieId << " " << it->getId() << " " << predRatings << endl;
        }
    }
    return pRs->RMSE();
}
double KNN::runUserPredictor()
{
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
                pRs->addRatings(predRatings);
            }
        }
    }
    return pRs->RMSE();
}

double KNN::predictRatings()
{
    if(k_value > K_LIMIT)
    {
        cerr << "K is too large, it should be from 1 to 500!" << endl;
        return -1;
    }
    cout << "Runing KNN" << endl;
    switch(sim_T)
    {
        case PEARSONCC_SIM_M:
        case COS_SIM_M:
            return runMoviePredictor();
        case PEARSONCC_SIM_U:
        case COS_SIM_U:
            return runUserPredictor();
        default:
            cerr << "Type error in KNN" << endl;
            return - 1;
    }
}
