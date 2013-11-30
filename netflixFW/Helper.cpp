//
//  Helper.cpp
//  CS5228Project
//
//  Created by OrangeR on 15/11/13.
//  Copyright (c) 2013 OrangeR. All rights reserved.
//

#include "Helper.h"
int strToInt(string str)
{
    int num = 0;
    for(int i = 0; i < str.length(); i ++)
        num = num * 10 + (str.at(i) - '0');
    
    return num;
}

string genTimeStamp()
{
    time_t rawtime;
    struct tm *timeinfo;
    time(&rawtime);
    timeinfo = localtime(&rawtime);
    
    //cout << asctime(timeinfo) << endl;
    string str = string(asctime(timeinfo));
    for(int i = 0; i < str.length() ; i ++)
    {
        string tmp = "_";
        if(str.at(i) == ' ')
            str = str.replace(i, 1, tmp);
    }
    str = str.substr(0, str.find_last_of('_'));
    return str;
}