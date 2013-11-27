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