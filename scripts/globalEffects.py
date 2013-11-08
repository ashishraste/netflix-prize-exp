import os
import sys
import time
import resource
from array import array
#import scipy.sparse as SP
import numpy as np
from scipy.sparse import lil_matrix, csr_matrix

DIR_PATH = "/media/01244D4977874BCC/DataSet/"
PROJECT_PATH = "/home/freax/netflix-prize-exp/"
DATA_PATH = PROJECT_PATH + "data/"
ROW = 17770
COL = 480189
#COL = 2649429
LIMIT = 17770
fIdx = int(0)
INFINITY_MINUS = 0
INFINITY_PLUS = 3000000

allRatingsMean = 3.6043
movieEffectTuningParam = 20
userEffectTuningParam = 10

past = time.time()
# create a lil_matrix
lm = lil_matrix((LIMIT, COL), dtype=np.int8)


movieRatings = []
movieEffectDict = {}
userEffectDict = {}
# get the files name in the directory DIR
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


probeDict = {}
def createProbeDict(filepath):
    global probeDict
    with open(filepath) as pfile:
        lines = pfile.readlines()
        for userID in lines:
            if ":" in userID:
                movieIDSplit = userID.split(':')
                movieID = int(movieIDSplit[0])
            else:
                if movieID in probeDict:                    
                    probeDict[movieID].append(int(userID))
                else:
                    probeDict[movieID] = [int(userID)]
                                            
        pfile.close()
    return probeDict



def calculateDeviation(ratingsMatrix):   
    global movieEffectDict
    global userEffectDict
    deviationSum = 0.0 
    numOfRatings = 0
    for index in range(ratingsMatrix.shape[1]):
        if ratingsMatrix[0, index-1]:
            deviationSum += ratingsMatrix[0, index-1] - allRatingsMean
            numOfRatings += 1    
    return deviationSum, numOfRatings


#def calculateMovieEffects(lm, probeDict):
#    # calculating movieEffect bi      
#    for key in probeDict.iterkeys():
#        ratingsForMovie = csr_matrix(lm.getrow(key))
#        deviationSum, numOfRatings = calculateDeviation(ratingsForMovie, 1)
#        movieEffect = deviationSum / (movieEffectTuningParam + numOfRatings)
#        movieEffectDict[key] = movieEffect
#    
#
#def calculateUserEffects(lmT, probeDict):
#    for userIDList in probeDict.itervalues():
#        for userIDIndex in range(len(userIDList)):
#            ratingsByUser = csr_matrix(lmT.getrow(userIDList[userIDIndex]))
#            deviationSum, numOfRatings = calculateDeviation(ratingsByUser)
#            userEffect = deviationSum / (userEffectTuningParam + numOfRatings)
#            userEffectDict[userIDList[userIDIndex]] = userEffect

probeSetRatingsDict = {}
userBaseline = {}
def removeGlobalEffects(lm):
    global movieEffectDict
    global userEffectDict
    global probeDict
    global probeSetRatingsDict
    global userBaseline
    #calculateMovieEffects(lm, probeDict)
    lmT = lm.transpose()  
    #calculateUserEffects(lmT, probeDict)
        
    for key in probeDict.iterkeys():
        ratingsForMovie = csr_matrix(lm.getrow(key))
        deviationSum, numOfRatings = calculateDeviation(ratingsForMovie, 1)
        movieEffect = deviationSum / (movieEffectTuningParam + numOfRatings)
        movieEffectDict[key] = movieEffect
        
        for userIDList in probeDict[key]:
            for userIDIndex in range(len(userIDList)):
                ratingsByUser = csr_matrix(lmT.getrow(userIDList[userIDIndex]))
                deviationSum, numOfRatings = calculateDeviation(ratingsByUser)
                userEffect = deviationSum / (userEffectTuningParam + numOfRatings)
                userEffectDict[userIDList[userIDIndex]] = userEffect
                
                baselineRating = allRatingsMean + movieEffect + userEffect
                userBaseline[userIDList[userIDIndex]] = baselineRating
        
        probeSetRatingsDict[key] = [userBaseline]

            
    
def main():
    global probeDict
    for filename in files_array:
        global fIdx
        global lm
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
            
    probeFilePath = DATA_PATH + "probe_converted.txt"
    probeDict = createProbeDict(probeFilePath)    
    removeGlobalEffects(lm, probeDict)
