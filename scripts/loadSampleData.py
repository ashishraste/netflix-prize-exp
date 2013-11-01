# -*- coding: utf-8 -*-
import os as os
import numpy as np
import random
import time

DATASET_SIZE = 17770
SAMPLE_SIZE = DATASET_SIZE / 10

DIR_PATH = "/media/01244D4977874BCC/training_set/"
#get the files name in the directory DIR


# pick a random sample of 1/10th the size of the dataset
randomNumList=[]
sampleFilesList = []
for i in range(SAMPLE_SIZE):
    randomNumList.append(random.randrange(1, DATASET_SIZE ,1))
    
past = time.time()

# collect all the file names within the dataset
files_array = []
os.chdir(DIR_PATH)
for files in os.listdir("."):
    if files.endswith(".txt") :
      files_array.append(files)
      #print files

# create a dictionary to store all the filenames in the dataset indexed on their movieIDs
movieIdDict = {}
for fileName in files_array:    
    if "mv_" in fileName:
        fileNum = fileName.split('mv_')
        fileNumList = fileNum[1].split('.')        
        fileNum = int(fileNumList[0])
        movieIdDict[fileNum] = fileName


# open a movie file, calculate its average ratings 
# store the average ratings in a outputfile, do this for all the files in the dataset
averageRatingDict = {}
numOfAllRatings = 0
allRatingsAverage = 0
def processMovieFiles(sampleFileName):
    #sampleFileNumList = sampleFileName.split('.')
    #sampleFileNum = int(sampleFileNumList[0])
    #sampleFileName = movieIdDict[sampleFileNum]            
    global allRatingsAverage
    global numOfAllRatings
    with open(sampleFileName) as f: 
        avgRating = 0       
        rows = f.readlines()
        del rows[0]
        lineContentList = []
        for lines in rows:                      
            lineContentList = lines.split(',')                
            avgRating += float(lineContentList[1])
            allRatingsAverage += float(lineContentList[1])
            numOfAllRatings += 1
            del lineContentList[:]
        avgRating = float(avgRating / len(rows))
        #print f.name, avgRating    
        averageRatingDict[f.name] = avgRating
    f.close()    
    return (f.name, avgRating)    
    
# writes average rating of each movie into avgRatingsOut.txt, calculates average of averages
globalMeanRating = 0  # represents the mean of the mean ratings
with open(DIR_PATH + "avgRatingsOut.txt", "a") as outfile:
    for files in files_array:        
        filename, avgRating = processMovieFiles(files)
        #print filename, avgRating
        globalMeanRating = globalMeanRating + avgRating
        outfile.write(str(avgRating))
    globalMeanRating /= DATASET_SIZE
    print "GlobalMeanRating: ", globalMeanRating
    # prints the average of all the ratings that were rated in the dataset
    allRatingsAverage /= numOfAllRatings
    print "allRatingsAverage: ", allRatingsAverage
    print "total number of ratings: ", numOfAllRatings
    outfile.write(str(globalMeanRating))
    outfile.close()    
        
print "Time:%.3f" % (time.time() - past), "seconds"

# create the filenames under the sample set using randomNumList
# and calculate their averageRatings
#fileType = '.txt'
#for randomNum in randomNumList:
#    sampleFileName = '{0}{1}'.format(randomNum, fileType) 
#    #print sampleFileName   
#    processMovieFiles(sampleFileName)





           
           
           
