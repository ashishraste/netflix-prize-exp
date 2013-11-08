import os as os
import numpy as np
import time

DATASET_SIZE = 17770
SAMPLE_SIZE = DATASET_SIZE / 10

DIR_PATH = "/media/01244D4977874BCC/"
os.chdir(DIR_PATH + "training_set/")

# collect all the file names within the dataset
def getFileNames():
    files_array = []
    for files in os.listdir("."):
        files_array.append(files)
    return files_array


# create a dictionary to store all the filenames in the dataset indexed on their movieIDs
def createFileNamesDict(files_array):
    movieIDNamesDict = {}
    #movieIDNameDict = {}
    for fileName in files_array:    
        if "mv_" in fileName:
            fileNum = fileName.split('mv_')
            fileNumList = fileNum[1].split('.')        
            fileNum = int(fileNumList[0])
            movieIDNamesDict[fileNum] = fileName


def createUserMovieDict():
    userIDDict = {}
    with open(DIR_PATH + "probe.txt") as probeFile:
        lines = probeFile.readlines()
        for userID in lines:
            if ":" in userID:
                movieIDSplit = userID.split(':')
                movieID = int(movieIDSplit[0])
            else:
                if movieID in userIDDict:
                    userIDDict[movieID].append(int(userID))
                else:
                    userIDDict[movieID] = [int(userID)]            
        probeFile.close() 
    return userIDDict


def processProbeFile(filepath, uidDict):
    midUidDict = {}
    with open(filepath) as pfile:
        lines = pfile.readlines()
        for userID in lines:
            if ":" in userID:
                movieIDSplit = userID.split(':')
                movieID = int(movieIDSplit[0])
            else:
                if movieID in midUidDict:                    
                    midUidDict[movieID].append(uidDict.get(int(userID)))
                else:
                    midUidDict[movieID] = [uidDict.get(int(userID))]
                                            
        pfile.close()
    return midUidDict
        

def getActualUserIDMap(userIDFile):
    uidDict = {}
    counter = 1
    with open(userIDFile) as ufile:
        lines = ufile.readlines()
        for line in lines:
            uidDict[int(line)] = counter
            counter += 1
        ufile.close()
    return uidDict
    
midUidDict = {}
def main():
    global midUidDict
    #files_array = getFileNames()
    userIdFile = DIR_PATH + "netflix/userIdsByAscendingOrder.txt"
    uidDict = getActualUserIDMap(userIdFile)
    probeFilePath = DIR_PATH + "netflix/probe.txt"
    midUidDict = processProbeFile(probeFilePath, uidDict)
    print len(midUidDict)
        

if __name__ == "__main__":
    past = time.time()    
    main()
    print "Time:%.3f" % (time.time() - past), "seconds"


