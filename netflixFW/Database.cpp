#include "Database.h"
#include <sys/stat.h>
//#include <sys/types.h>
Database::Database()
{}

Database::~Database()
{}

bool Database::loadDatabase(const std::string database_movie_path,const std::string database_user_path, MovieRatings &movies, UserRatings &users)
{
    ifstream movieFile(database_movie_path.c_str(), ios::in|ios::binary);
    ifstream userFile(database_user_path.c_str(), ios::in|ios::binary);
    if(!movieFile.good() || !userFile.good())
    {
        cerr << "File not exists!" << endl;
        //return false;
        if(genDatabase(DATASET_PATH, DATABASE_PATH, MOVIEDATABASE, USERDATABASE))
            loadDatabase(database_movie_path, database_user_path, movies, users);
    }
    else
    {
      //load movie database
        if(movieFile.is_open())
        {
            cout << "Loading movie Database" << endl;
            uInt num = 0;
            uInt index = 1;
            unsigned short uIdHi = 0;
            uByte rating = 0;
            while(!movieFile.eof())
            {
                num = 0;
                uIdHi = 0;
                rating = 0;
                movieFile.read((char *)&num, sizeof(int));
                //cout << index << endl;
                //cout << "Num " << num << endl;
                for(int i = 0; i < num; i ++)
                {
                    movieFile.read((char *)&uIdHi, sizeof(unsigned short));
                    movieFile.read((char *)&rating, sizeof(uByte));
                    movies.addRating(index, mRatings(uIdHi, rating));
                }
                index ++;
            }
            movieFile.close();
        }
        else
        {
            cerr << "File not open!" << endl;
            return false;
        }
        
        //load user database
        if(userFile.is_open())
        {
            cout << "Loading user Database" << endl;
            uInt num = 0;
            uInt index = 1;
            unsigned short mId = 0;
            uByte rating = 0;
            while(!userFile.eof())
            {
                num = 0;
                mId = 0;
                rating = 0;
                userFile.read((char *)&num , sizeof(int));
                //cout << index << endl;
                //cout << "Num " << num << endl;
                for(int i = 0; i < num; i ++)
                {
                    userFile.read((char *)(&mId), sizeof(unsigned short));
                    userFile.read((char *)(&rating), sizeof(uByte));
                    users.addRating(index, uRatings(mId, rating));
                }
                index ++;
            }
        }
        else
        {
            cerr << "File not open!" << endl;
            return false;
        }
    }
    movies.computeAllMeans();
    //movies.dumpAllMeans();
    movies.computeAllStdDevs();
    //movies.dumpAllStdDevs();
    users.computeAllMeans();
    //users.dumpAllMeans();
    users.computeAllStdDevs();
    //users.dumpAllStdDevs();
    return true;
}

bool Database::genDatabase(const std::string path_src, const std::string path_dest, const string movieDatabase, const string userDatabase)
{
    
    DIR *dp;
    struct dirent *fp;
    std::vector<std::string> fnames;
    if ((dp = opendir(path_src.c_str())) != NULL) {
        while ((fp = readdir(dp)) != NULL) {
            if(string(fp->d_name).find(".txt") != std::string::npos)
            {
                fnames.push_back(string(fp->d_name));
            }
        }
        closedir(dp);
    }
    
    if((dp = opendir(path_dest.c_str())) == NULL){
        if(mkdir(path_dest.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH) != 0)
            cout << "mkdir failed!" << endl;
            return false;
    }
    
    
    //for(vector<string>::iterator it = fnames.begin(); it != fnames.end(); ++ it)
    //    cout << *it << endl;
    //cout << fnames.size() << std::endl;
    //cout << "In Database" << endl;
    
    //remove files
    if(remove((path_dest + movieDatabase).c_str()) == 0)
        cout << "Remove " << movieDatabase << endl;
    if(remove((path_dest + userDatabase).c_str()) == 0)
        cout << "Remove " << userDatabase << endl;
    
    vector<mRatings> mRs;
    UserRatings *users = new UserRatings();
    
    //generate movie dataset
    for(vector<string>::iterator it = fnames.begin(); it != fnames.end(); ++ it)
    {
        ifstream myFile((path_src + *it).c_str());
        string line;
        int movieId;
        if(myFile.is_open())
        {
            getline(myFile, line);
            movieId = strToInt(line.substr(0, line.find(':') - 0));
            cout << "MovieID " << movieId << endl;
            while(getline(myFile, line))
            {
                //int start = 0;
                //cout << line.substr(start, line.find(',') - start) << " " << line.substr(line.find(',') + 1, line.find_last_of(',') - line.find(',') - 1) << endl;
                uInt uId = strToInt(line.substr(0, line.find(',') - 0));
                uByte rating = uByte(strToInt(line.substr(line.find(',') + 1, line.find_last_of(',') - line.find(',') - 1)));
                mRatings mRat = mRatings(uId, rating);
                int index = binarySearch<mRatings>(mRs, mRat);
                insert<mRatings>(mRs, mRat, index);
                //initilize user vectors
                users->addRating(mRs.back().getId(), uRatings(movieId, mRs.back().getValue()));
            }
            myFile.close();
            
            //generate user database
            ofstream movieWFile((path_dest + movieDatabase).c_str(), ios::out|ios::binary|ios::app);
            if(movieWFile.good())
            {
                if(movieWFile.is_open())
                {
                    unsigned short uIdHi = 0;
                    uByte rating = 0;
                    uInt size = int(mRs.size());
                    movieWFile.write((char *)&size, sizeof(uInt));
                    cout << size << endl;
                    for(vector<mRatings>::iterator it = mRs.begin(); it != mRs.end(); ++ it)
                    {
                        uIdHi = it->userIdHi;
                        rating = ((it->userIdLo) << 4) + uByte(it->value);
                        movieWFile.write((char *)&uIdHi, sizeof(unsigned short));
                        movieWFile.write((char *)&rating, sizeof(uByte));
                    }
                }
                mRs.clear();
                movieWFile.close();
            }
            else
            {
                cout << "Failed!" << endl;
            }
        }
    }
    
    //generate user dataset
    ofstream userFile((path_dest + userDatabase).c_str(), ios::out|ios::binary|ios::ate);
    vector<uRatings> uRs;
    for(uInt i = 1; i <= users->getUserNum(); i ++)
    {
        uRs.clear();
        users->getRatings(i, uRs);
        if(userFile.good())
        {
            if(userFile.is_open())
            {
                unsigned short mId = 0;
                uByte rating = 0;
                uInt num = uInt(uRs.size());
                userFile.write((char* )&num, sizeof(unsigned int));
                for(vector<uRatings>::iterator it = uRs.begin(); it != uRs.end(); ++ it)
                {
                    mId = it->movieId;
                    rating = it->value;
                    userFile.write((char *)&mId, sizeof(unsigned short));
                    userFile.write((char *)&rating, sizeof(uByte));
                }
            }
        }
    }
    userFile.close();
    return true;
}
