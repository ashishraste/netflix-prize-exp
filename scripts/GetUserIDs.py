import os
import sys
import time
import resource
from array import array
#import scipy.sparse as SP
import numpy as np

LIMIT = 17770
fIdx = int(0)
ROW = 17770
COL = 480189
INFINITY_MINUS = 0
INFINITY_PLUS = 3000000
#UID_FILE_PATH = "/Users/OrangeR/Dropbox/CS5228/scripts/userIdsByAscendingOrder.txt"
DIR_PATH = "/Users/OrangeR/Documents/study/AY2013_14/CS5228/group project/Dataset of Netflix/training_set/"

past = time.time()
#create a lil_matrix
#lm = lil_matrix((LIMIT, COL), dtype=np.int8)
movieRatings = []
#get the files name in the directory DIR
files_array = []

uIdArray = []
#os.chdir(UID_FILE_PATH)
#with open(UID_FILE_PATH) as uidFile:
#    movieRatings.append([int(m) for m in f.readline().split(':') if m.isdigit()])

os.chdir(DIR_PATH)
for files in os.listdir("."):
    if files.endswith(".txt"):
        files_array.append(files)
        #print files

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

userIdArray = array('I', [INFINITY_MINUS, INFINITY_PLUS])

for filename in files_array:
    if fIdx < LIMIT:
        with open(DIR_PATH + filename) as f:
            #movieRatings.append([int(m) for m in f.readline().split(':') if m.isdigit()])
            mID = [int(m) for m in f.readline().split(':') if m.isdigit()]
            for line in f:
                if line:
                    movieRating = [int(n) for n in line.split(',') if n.isdigit()]
                    binarySearchInsert(userIdArray, movieRating[0])
                    #lm[mID[0] - 1, movieRating[0] - 1] = movieRating[1] 
                
        f.close()
        fIdx += 1
        print "\rMemory:",(resource.getrusage(resource.RUSAGE_SELF).ru_maxrss/1000000), "MB", "Files:", mID[0], "/", ROW, "(%f" % (float(mID[0])/float(ROW) * 100),"%)", "Time:%.3f" % (time.time() - past), "seconds",
        sys.stdout.flush() 

with open("/Users/OrangeR/Documents/cs5228/" + "userIdsByAscendingOrder.txt", "a") as outfile:
    for i in userIdArray:
        outfile.write(str(i) + '\n')
    outfile.close()