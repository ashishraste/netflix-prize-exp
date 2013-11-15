import os as os
import time
import math as math

DATASET_SIZE = 17770

DATA_PATH = "/home/freax/netflix-prize-exp/data/"
DIR_PATH = "/media/01244D4977874BCC/training_set/"
os.chdir(DIR_PATH)
        
# collect all the file names within the dataset
files_array = []
def getFileNames():
    for files in os.listdir("."):
        files_array.append(files)

     
ratingsDict = {1:0, 2:0, 3:0, 4:0, 5:0}    # contains the frequency of a given rating (integer 1-5)
def collectRatingsFrequency(sampleFileName):
    with open(sampleFileName) as f:
        rows = f.readlines()
        del rows[0]
        for lines in rows:
            lineSplit = lines.split(",")
            rating = int(lineSplit[1])
            ratingsDict[rating] += 1
            #lineSplit[:] = []
        f.close()    


# contains the frequency of movies by the ratings distributed on 0.5 resolution
avgRatingFreq = {1.0:0, 1.5:0, 2.0:0, 2.5:0, 3.0:0, 3.5:0, 4.0:0, 4.5:0, 5.0:0}
def collectAvgRatingByMovieFreq(avgRatingsFile):
    with open(avgRatingsFile) as f:
        rows = f.readlines()
        for line in rows:
            r = float(line)
            rCeil = math.ceil(r)
            rFloor = math.floor(r)
            rHalfInt = rFloor + 0.5
            floorDif = r - rFloor
            ceilDif = rCeil - r
            if floorDif > ceilDif:
                if (r - rHalfInt) < ceilDif:
                    roundedVal = rHalfInt
                else:
                    roundedVal = rCeil
            else:
                if (rHalfInt - r) < floorDif:
                    roundedVal = rHalfInt
                else:
                    roundedVal = rFloor
            avgRatingFreq[roundedVal] += 1
        f.close()


userAvgRatingsList = []
def collectUserAvgRating(avgRatingsFile):
    with open(avgRatingsFile) as f: 
        rows = f.readlines()
        for lines in rows:                      
            lineContentList = lines.split(',')                
            avgRating = float(lineContentList[1])            
            userAvgRatingsList.append(avgRating)
        f.close()    


def collectAvgRatingByUserFreq():    
    for key in avgRatingFreq.iterkeys():
        avgRatingFreq[key] = 0
        
    for r in userAvgRatingsList:
        rCeil = math.ceil(r)
        rFloor = math.floor(r)
        rHalfInt = rFloor + 0.5
        floorDif = r - rFloor
        ceilDif = rCeil - r
        if floorDif > ceilDif:
            if (r - rHalfInt) < ceilDif:
                roundedVal = rHalfInt
            else:
                roundedVal = rCeil
        else:
            if (rHalfInt - r) < floorDif:
                roundedVal = rHalfInt
            else:
                roundedVal = rFloor
        avgRatingFreq[roundedVal] += 1


rByMIDDict = {}
# creating rByMIDDict, indexed on MIDs
def createMIDDict():
    for filename in files_array:
        with open(filename) as f:
            rows = f.readlines()
            midSplit = rows[0].split(":")
            mid = int(midSplit[0])
            del rows[0]
            for lines in rows:
                lineContentSplit = lines.split(',') 
                rating = float(lineContentSplit[1])
                
                if mid in rByMIDDict:
                    rByMIDDict[mid].append(rating)
                else:
                    rByMIDDict[mid] = [rating]                            
            f.close()            

#
#def avgMovieRatingSD(avgRatingsFile):
#    mid = 0
#    with open(avgRatingsFile) as f:
#        mid += 1
#        rows = f.readLines()
#        for line in rows:
#            r = float(line)
#            ratingList = rByMIDdict[mid]
#            
#            
#         

movieAvgRatingsDict = {}
def collectMovieAvgRatings(avgRatingsFile):
    with open(avgRatingsFile) as f:
        rows = f.readlines()
        mid = 0
        for line in rows:
            mid += 1
            r = float(line)
            movieAvgRatingsDict[mid] = r
        f.close()

            
movieRatingsSD = {}
def collectMovieRatingsStdDev(ratingsSDFile):
    with open(ratingsSDFile) as f:
        rows = f.readlines()
        mid = 0
        for line in rows:
            mid += 1
            sd = float(line)            
            movieRatingsSD[mid] = sd
        f.close()

#clusteredMeanSD = {1.0:0, 1.5:0, 2.0:0, 2.5:0, 3.0:0, 3.5:0, 4.0:0, 4.5:0, 5.0:0}
#def clusterRatingsMeanStdDev():

                                                                       
def main():
    getFileNames()
    #for movieFile in files_array:
    #    collectRatingsFrequency(movieFile)
    #avgRatingsFile = DATA_PATH + "avgRatingsOut.txt"
    #collectMovieAvgRatings(avgRatingsFile)
    ratingsSDFile = DATA_PATH + "movie_std_dev.txt"
    collectMovieRatingsStdDev(ratingsSDFile)
    #collectAvgRatingByMovieFreq(avgRatingsFile)
    #avgRatingsFile = DATA_PATH + "userRatingsMean.txt"
    #collectUserAvgRating(avgRatingsFile)
    #collectAvgRatingByUserFreq()


    

if __name__ == "__main__":
    past = time.time()    
    main()
    print "Time:%.3f" % (time.time() - past), "seconds"