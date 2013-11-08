import os as os
import numpy as np
import time

DATASET_SIZE = 17770
SAMPLE_SIZE = DATASET_SIZE / 10

DIR_PATH = "/media/01244D4977874BCC/training_set/"
os.chdir(DIR_PATH)
        
# collect all the file names within the dataset
files_array = []
def getFileNames():
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
    getFileNames()
    for movieFile in files_array:
        createMIDDict(movieFile)


if __name__ == "__main__":
    past = time.time()    
    main()
    print "Time:%.3f" % (time.time() - past), "seconds"