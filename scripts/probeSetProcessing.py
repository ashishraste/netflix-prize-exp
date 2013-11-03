import os as os
import numpy as np
import time

DATASET_SIZE = 17770
SAMPLE_SIZE = DATASET_SIZE / 10

DIR_PATH = "/media/01244D4977874BCC/training_set/"
past = time.time()

# collect all the file names within the dataset
files_array = []
for files in os.listdir("."):
    if files.endswith(".txt"):
      files_array.append(files)

# create a dictionary to store all the filenames in the dataset indexed on their movieIDs
movieIDNamesDict = {}
#movieIDNameDict = {}
for fileName in files_array:    
    if "mv_" in fileName:
        fileNum = fileName.split('mv_')
        fileNumList = fileNum[1].split('.')        
        fileNum = int(fileNumList[0])
        movieIDNamesDict[fileNum] = fileName

userIDDict = {}
cntr = 0
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
print userIDDict.get(int(1))
