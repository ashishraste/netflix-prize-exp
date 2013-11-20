//
//  main.cpp

//  CS5228Project


#include <iostream>
#include <fstream>
#include <string>
#include <dirent.h>
#include <vector>
//#include "Ratings.h"
#include "UserRatings.h"
#include "MovieRatings.h"
#include "Helper.h"

using namespace std;

const string DATASET_PATH = "/media/01244D4977874BCC/DataSet/";
const string PROBESET_PATH = "/home/freax/netflix-prize-exp/data/";
//const string uIdsFile = "/home/freax/netflix-prize-exp/data/userIdsByAscendingOrder.txt";

int main(int argc, const char * argv[])
{
    // insert code here...
    //cout << count << endl;
    
    //Ratings um;
    //mRatings mR;
    /*
    mR.userIdLo = 16;
    cout << int(mR.userIdLo) << endl;
    mR.userIdLo = 15;
    cout << int(mR.userIdLo) << endl;
    cout << sizeof(uRatings) << endl;
    cout << sizeof(mRatings) << endl;
     */
    MovieRatings mRs;
    UserRatings uRs;
    //std::cout << sqrt(2) << std::endl;
    loadData(DATASET_PATH, mRs, uRs);
    //int i = 0;
    //cout << ('9' - '0') << endl;
    //cout << calMMPearsonCorrelation(mRs, uRs, 1, 2) << endl;
    
    return 0;
}

