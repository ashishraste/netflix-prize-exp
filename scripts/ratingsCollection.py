import os as os
import numpy as np
import random
import time
from ctypes import *

#class UserID(Structure):
#    _fields_ = [("uid", c_ushort), ("rating", c_ubyte)]
#
#class MovieID(Structure):
#    __fields__ = [("mid", c_ushort), ("rating", c_ubyte)]

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



rByMIDDict = {}
uidRatingDict = {}
# creating rByMIDDict, indexed on MIDs
def createMIDDict(sampleFileName):
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
            
            uidRatingDict[uid] = [rating]                
            if mid in rByMIDDict:
                rByMIDDict[mid].append(uidRatingDict)
            else:
                rByMIDDict[mid] = [uidRatingDict]                            
        f.close()


rByUIDDict = {}    
midRatingDict = {}
# creating rByUIDDict, indexed on UIDs
def createUIDDict(sampleFileName):
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
            
            # creating rByUIDDict, indexed on UIDs
            if mid in midRatingDict:
                midRatingDict[mid].append(rating)
            else:
                midRatingDict[mid] = [rating]                
            if uid in rByUIDDict:
                rByUIDDict[uid].append(midRatingDict)
            else:
                rByUIDDict[uid] = [midRatingDict]            
        f.close()
            

def main():
    collectFileNames()
    for movieFile in files_array:
        createMIDDict(movieFile)


if __name__ == "__main__":
    past = time.time()    
    main()
    print "Time:%.3f" % (time.time() - past), "seconds"