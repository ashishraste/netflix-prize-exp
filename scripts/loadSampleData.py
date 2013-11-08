import os as os
import random
import time

DATASET_SIZE = 17770
SAMPLE_SIZE = DATASET_SIZE / 10

DIR_PATH = "/media/01244D4977874BCC/training_set/"
PROJECT_PATH = "/home/freax/netflix-prize-exp/"
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
      print files

# create a dictionary to store all the filenames in the dataset indexed on their movieIDs
movieIdDict = {}
for fileName in files_array:    
        fileNum = fileName.split('mv_')
        fileNumList = fileNum[1].split('.')        
        fileNum = int(fileNumList[0])
        movieIdDict[fileNum] = fileName


# open a movie file, calculate its average ratings 
# store the average ratings in a outputfile, do this for all the files in the dataset
averageRatingDict = {}
def processMovieFiles(sampleFileName):
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
    

with open(PROJECT_PATH + "data/avgRatingsOut.txt", "a") as outfile:
    for files in files_array:        
        filename, avgRating = processMovieFiles(files)
        print filename, avgRating
        outfile.write(str(avgRating))
    outfile.close()
    
print "Time:%.3f" % (time.time() - past), "seconds"




           
           
           
