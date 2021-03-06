//
//  Config.h
//  CS5228Project
//
//  Created by OrangeR on 25/11/13.
//  Copyright (c) 2013 OrangeR. All rights reserved.
//

#ifndef CS5228Project_Config_h
#define CS5228Project_Config_h
#include <string>
#include <dirent.h>
#include <iostream>
#include <fstream>
#include <sys/stat.h>

typedef unsigned char uByte;
typedef unsigned int uInt;
typedef unsigned short uShort;
const int MOVIE_NUM = 17770;
const int USER_NUM = 480189;
const int RATINGS_NUM = 100480508;

const std::string DATASET_PATH = "/media/01244D4977874BCC/DataSet/" ;
const std::string PROBE_PATH = "/media/01244D4977874BCC/";
const std::string DATABASE_PATH = "/media/01244D4977874BCC/Database/" ;
const std::string PROBE_FILE = "probe_ratings.txt";

const std::string MOVIEPCCSIMFILE = "MoviePCCSim.dat";
const std::string MOVIECOSSIMFILE = "MovieCOSSim.dat";
const std::string MOVIEDATABASE = "Movie.dat";
const std::string USERDATABASE = "User.dat";
const std::string PROBEDATABASE = "Probe.dat";
#endif
