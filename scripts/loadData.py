# -*- coding: utf-8 -*-
import os
import sys
import time
import resource
from array import array
import numpy as np
from scipy.sparse import lil_matrix

DIR_PATH = "/media/01244D4977874BCC/DataSet/"
DATA_PATH = "/home/freax/netflix-prize-exp/data/"
ROW = 17770
COL = 480189
#COL = 2649429
LIMIT = 17770
fIdx = int(0)
INFINITY_MINUS = 0
INFINITY_PLUS = 3000000

past = time.time()
#create a lil_matrix
lm = lil_matrix((LIMIT, COL), dtype=np.int8)
movieRatings = []
#get the files name in the directory DIR
files_array = []
os.chdir(DIR_PATH)
for files in os.listdir("."):
    if files.endswith(".txt"):
        files_array.append(files)
        print files


uIdArray = []
os.chdir(DATA_PATH)
with open(DATA_PATH + "userIdsByAscendingOrder.txt") as uidFile:
    for line in uidFile:
        uIdArray.append([int(m) for m in line.split('\n') if m.isdigit()][0])        
                        
def binarySearchInsert(userIdArray, uId_Real):
    start = int(0)
    end = len(userIdArray) - 1
    mid = 0
    while start <= end:
        mid = (start + end) / 2       
        if userIdArray[mid] == uId_Real:
            return mid
        if userIdArray[mid] > uId_Real:
            end = mid - 1
        else:
            start = mid + 1

    if userIdArray[mid] > uId_Real:
        userIdArray.insert(mid, uId_Real)
        return mid
    else:
        userIdArray.insert(mid + 1, uId_Real)
        return mid + 1

#userIdArray = array('I', [INFINITY_MINUS, INFINITY_PLUS])

for filename in files_array:
    if fIdx < LIMIT:
        with open(DIR_PATH + filename) as f:
            #movieRatings.append([int(m) for m in f.readline().split(':') if m.isdigit()])
            mID = [int(m) for m in f.readline().split(':') if m.isdigit()]
            for line in f:
                if line:
                    movieRating = [int(n) for n in line.split(',') if n.isdigit()]
                    #binarySearchInsert(userIdArray, movieRating[0])
                    lm[mID[0] - 1, movieRating[0] - 1] = movieRating[1] 
                
        f.close()
        fIdx += 1
        print "\rMemory:",(resource.getrusage(resource.RUSAGE_SELF).ru_maxrss/1000000), "MB", "Files:", mID[0], "/", ROW, "(%f" % (float(mID[0])/float(ROW) * 100),"%)", "Time:%.3f" % (time.time() - past), "seconds",
        sys.stdout.flush() 