from tempfile import mkdtemp
import os.path as path
import os as os
import numpy as np
import random

DATASET_SIZE = 17770
SAMPLE_SIZE = DATASET_SIZE / 10

DIR_PATH = "/media/01244D4977874BCC/training_set/"
#get the files name in the directory DIR

# write into the memmap array (which creates a virtual file through mkdtemp)
# the values of movieID and their average rating
#virtualFilename = path.join(mkdtemp(), 'ratingsfile.dat')
#fp = np.memmap(virtualFilename, dtype='int32', mode='w+', shape=(SAMPLE_SIZE,1))

# pick a random sample of 1/10th the size of the dataset
randomNumList=[]
sampleFilesList = []
for i in range(SAMPLE_SIZE):
    randomNumList.append(random.randrange(1, DATASET_SIZE ,1))

# collect all the file names within the dataset
files_array = []
os.chdir(DIR_PATH)
for files in os.listdir("."):
    if files.endswith(".txt") :
      files_array.append(files)
      print files

# create a dictionary to store the filenames in the dataset indexed on their movieIDs
movieIdDict = {}
for fileName in files_array:    
        fileNum = fileName.split('mv_')
        fileNumList = fileNum[1].split('.')        
        fileNum = int(fileNumList[0])
        movieIdDict[fileNum] = fileName

# open a movie file, calculate its average ratings 
# store the average ratings in a outputfile
averageRatingDict = {}
def processMovieFiles(sampleFileName):
    #sampleFileNumList = sampleFileName.split('.')
    #sampleFileNum = int(sampleFileNumList[0])
    #sampleFileName = movieIdDict[sampleFileNum]            
    with open(sampleFileName) as f: 
        avgRating = 0       
        rows = f.readlines()
        del rows[0]
        for lines in rows:          
            lineContentList = []
            lineContentList = lines.split(',')                
            avgRating = avgRating + float(lineContentList[1])
        avgRating = float(avgRating / len(rows))
        lineContentList[:] = []
        #print f.name, avgRating    
        averageRatingDict[f.name] = avgRating
    f.close()    
    return (f.name, avgRating)    
    
# create the filenames under the sample set using randomNumList
# and calculate their averageRatings
#fileType = '.txt'
#for randomNum in randomNumList:
#    sampleFileName = '{0}{1}'.format(randomNum, fileType) 
#    #print sampleFileName   
#    processMovieFiles(sampleFileName)
    

with open(DIR_PATH + "avgRatingsOut.txt", "a") as outfile:
    for files in files_array:        
        filename, avgRating = processMovieFiles(files)
        print filename, avgRating
        outfile.write(str(avgRating))
    outfile.close()

    

           
           
           
