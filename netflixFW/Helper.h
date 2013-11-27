//
//  Helper.h
//  CS5228Project
//
//  Created by OrangeR on 15/11/13.
//  Copyright (c) 2013 OrangeR. All rights reserved.
//

#ifndef CS5228Project_Helper_h
#define CS5228Project_Helper_h
#include <string>
#include <vector>
#include <typeinfo>
#include "Config.h"
#include "ProbeRatings.h"

using namespace::std;

template<typename T>
inline int binarySearch(vector<T>& containers, T& item)
{
    
    if(containers.size() == 0)
        return 0;
    
    int start = 0;
    int end = int(containers.size() - 1);
    int mid = 0;
    
    uInt newId = item.getId();
    while(start <= end)
    {
        mid = (start + end) / 2;
        uInt currentId = containers.at(mid).getId();
        if(newId == currentId)
            break;
        else if(newId < currentId)
            end = mid - 1;
        else
            start = mid + 1;
    }
    
    return mid;
}

template<typename T>
inline void insert(vector<T> & containers, T& item, int index)
{
    if(containers.size() == 0 || containers.at(index).getId() > item.getId())
        containers.insert(containers.begin() + index, item);
    else if(containers.at(index).getId() < item.getId())
    {
        if(index == containers.size() - 1)
            containers.push_back(item);
        else
            containers.insert(containers.begin() + index + 1, item);
    }
}

int strToInt(string str);
double RMSE(ProbeRatings &predictedRatings, ProbeRatings &realRatings);
#endif
