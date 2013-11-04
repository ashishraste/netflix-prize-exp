import os as os
import numpy as np
import random
import time
from ctypes import *

class UserID(Structure):
    _fields_ = [("uid", c_ushort), ("rating", c_ubyte)]

DATASET_SIZE = 17770
SAMPLE_SIZE = DATASET_SIZE / 10

DIR_PATH = "/media/01244D4977874BCC/training_set/"

# pick a random sample of 1/10th the size of the dataset
randomNumList = []
sampleFilesList = []
for i in range(SAMPLE_SIZE):
    randomNumList.append(random.randrange(1, DATASET_SIZE ,1))

os.chdir(DIR_PATH)    
past = time.time()

# collect all the file names within the dataset
files_array = []
for files in os.listdir("."):
    if files.endswith(".txt") and "mv_" in files:
      files_array.append(files)

past = time.time()

# open a movie file, store its uid (vs) rating map in struct form 
rByMIDDict = {}
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
            userid = UserID(c_ushort(uid), c_ubyte(rating))
            #print userid.uid, userid.rating 
            if mid in rByMIDDict:
                rByMIDDict[mid].append(userid)
            else:
                rByMIDDict[mid] = [userid]
    f.close()
    
#def main():
for movieFile in files_array:
    processMovieFiles(movieFile)
#
#if __name__ == "__main__":
#    main()

print "Time:%.3f" % (time.time() - past), "seconds"