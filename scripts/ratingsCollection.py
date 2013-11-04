import os as os
import numpy as np
import random
import time
from ctypes import *

class UserID(Structure):
    _fields_ = [("uid", np.int16), ("rating", np.int8)]

class MovieID(Structure):
    __fields__ = [("mid", np.int16), ("rating", np.int8)]

DATASET_SIZE = 17770
SAMPLE_SIZE = DATASET_SIZE / 10

DIR_PATH = "/media/01244D4977874BCC/training_set/"
os.chdir(DIR_PATH)

# pick a random sample of 1/10th the size of the dataset
randomNumList = []
sampleFilesList = []
def generateRandomNumbers():
    for i in range(SAMPLE_SIZE):
        randomNumList.append(random.randrange(1, DATASET_SIZE ,1))

        
# collect all the file names within the dataset
files_array = []
def collectFileNames():
    for files in os.listdir("."):
        if files.endswith(".txt") and "mv_" in files:
            files_array.append(files)


# open a movie file, store its uid (vs) rating map in struct form 
rByMIDDict = {}
rByUIDDict = {}
def processMovieFiles(sampleFileName):
    with open(sampleFileName) as f:
        rows = f.readlines()
        midSplit = rows[0].split(":")
        mid = int(midSplit[0])
        del rows[0]
        lineContentSplit = []
        for lines in rows:
            lineContentSplit = lines.split(',') 
            uid = int(lineContentSplit[0])
            rating = int(lineContentSplit[1])
            userid = UserID(np.int16(uid), np.int8(rating))
            movieid = MovieID(np.int16(mid), np.int8(rating))
            
            if mid in rByMIDDict:
                rByMIDDict[mid].append(userid)
            else:
                rByMIDDict[mid] = [userid]
                
            if uid in rByUIDDict:
                rByUIDDict[uid].append(movieid)
            else:
                rByUIDDict[uid] = [movieid]
            
    f.close()


def main():
    for movieFile in files_array:
        processMovieFiles(movieFile)


if __name__ == "__main__":
    past = time.time()    
    main()
    print "Time:%.3f" % (time.time() - past), "seconds"