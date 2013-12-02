//
//  DataBase.h
//  CS5228Project
//
//  Created by OrangeR on 25/11/13.
//  Copyright (c) 2013 OrangeR. All rights reserved.
//

#ifndef CS5228Project_DataBase_h
#define CS5228Project_DataBase_h
#include <sys/mman.h>
#include <string>
#include <vector>


#include "MovieRatings.h"
#include "UserRatings.h"
#include "ProbeRatings.h"
#include "Helper.h"

using namespace std;


class Database
{
public:
    Database();
    ~Database();
    bool loadDatabase(const string database_movie, const string database_user, MovieRatings &movies, UserRatings &users);
    bool loadProbeDatabase(const string database_probe, ProbeRatings &probe);
private:
    bool genDatabase(const string path_src, const string path_dest, const string movieDatabase, const string userDatabase);
    bool genProbeDatabase(const string path_src, const string path_dest, const string probeDatabase);
};

#endif
