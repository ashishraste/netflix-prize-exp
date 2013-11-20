//
//  Helper.cpp


#include "Helper.h"
int loadData(const std::string dir_path, MovieRatings &mRs, UserRatings &uRs)
{
    DIR *dp;
    struct dirent *fp;
    vector<string> fnames;
    if ((dp = opendir(dir_path.c_str())) != NULL) {
        while ((fp = readdir(dp)) != NULL) {
            if(string(fp->d_name).find(".txt") != string::npos)
            {
                fnames.push_back(string(fp->d_name));
            }
        }
        closedir(dp);
    }
    
    for(vector<string>::iterator it = fnames.begin(); it != fnames.end(); ++ it)
        cout << *it << endl;
    cout << fnames.size() << std::endl;
    
    for(vector<string>::iterator it = fnames.begin(); it != fnames.end(); ++ it)
    {
        ifstream myFile((dir_path + *it).c_str());
        string line;
        int movieId;
        if(myFile.is_open())
        {
            getline(myFile, line);
            movieId = strToInt(line.substr(0, line.find(':') - 0));
            cout << "MovieID " << movieId << endl;
            while(getline(myFile, line))
            {
                //cout << line.substr(start, line.find(',') - start) << " " << line.substr(line.find(',') + 1, line.find_last_of(',') - line.find(',') - 1) << endl;
                uInt uId = strToInt(line.substr(0, line.find(',') - 0));
                uByte rating = uByte(strToInt(line.substr(line.find(',') + 1, line.find_last_of(',') - line.find(',') - 1)));
                //mRs.addRating(movieId, mRatings(uId, rating));
                //uRs.addRating(uId, uRatings(movieId, rating));
                mRs.addRatingWithAscending(movieId, mRatings(uId, rating));
                //uRs.addRatingWithAscending(uId,uRatings(movieId, rating));
            }
            mRs.computeMean(movieId);
            mRs.computeStd_dev(movieId);
            //mRs.dumpRatings(movieId);
            myFile.close();
        }
    }
    //uRs.computeMean();
    //uRs.computeStd_dev();
    //uRs.dumpStd_dev();
    //cout << "std" << endl;
    //mRs.dumpStd_dev();
    
    return 0;
}

int strToInt(string str)
{
    int num = 0;
    for(int i = 0; i < str.length(); i ++)
        num = num * 10 + (str.at(i) - '0');
    
    return num;
}


double calUUPearsonCorrelation(UserRatings &uRs, uInt uId1, uInt uId2)
{
    return 0;
}
double calMMPearsonCorrelation(MovieRatings &mRs, uInt mId1, uInt mId2)
{
    //std::vector<mRatings> pTemp;
    //mRs.getSupport(mId1) > mRs.getSupport(mId2);
    double upNum = 0;
    double downLeft = 0;
    double downRight = 0;
    if(mRs.getSupport(mId1) > mRs.getSupport(mId2))
    {
        mRatings mRating1;
        mRatings mRating2;
        for(int i = 0; i < mRs.getSupport(mId2); i ++)
        {
            mRs.getRating(mId2, i, mRating2);
            mRating1.setUerId(mRating2.getUserId());
            mRs.isMovieRatedByUser(mId1, mRating1);
            if(mRating2.value != 0 && mRating1.value != 0)
            {
                upNum += (mRating2.value - mRs.getMean(mId2)) * (mRating1.value - mRs.getMean(mId1));
                downLeft += pow((mRating2.value - mRs.getMean(mId2)), 2);
                downRight += pow((mRating1.value - mRs.getMean(mId1)), 2);
            }
        }
        
    }
    else
    {
        mRatings mRating1;
        mRatings mRating2;
        for(int i = 0; i < mRs.getSupport(mId1); i ++)
        {
            mRs.getRating(mId1, i, mRating1);
            mRating2.setUerId(mRating1.getUserId());
            mRs.isMovieRatedByUser(mId1, mRating2);
            if(mRating2.value != 0 && mRating1.value != 0)
            {
                upNum += (mRating2.value - mRs.getMean(mId2)) * (mRating1.value - mRs.getMean(mId1));
                downLeft += pow((mRating1.value - mRs.getMean(mId1)), 2);
                downRight += pow((mRating2.value - mRs.getMean(mId2)), 2);
            }
        }
    }
    return upNum / sqrt(downLeft) * sqrt(downRight);
}

double calculatePearsonCorrelation(MovieRatings &mRs, UserRatings &uRs, int Id1, int Id2)
{
    
    return 0;
}
