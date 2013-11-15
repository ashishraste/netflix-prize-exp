import time
#import scipy.sparse as SP
from scipy.sparse import csr_matrix

DIR_PATH = "/media/01244D4977874BCC/DataSet/"
PROJECT_PATH = "/home/freax/netflix-prize-exp/"
DATA_PATH = PROJECT_PATH + "data/"

allRatingsMean = 3.6043
movieEffectTuningParam = 20

movieEffectDict = {}

probeDict = {}
def createProbeDict(filepath):
    global probeDict
    with open(filepath) as pfile:
        lines = pfile.readlines()
        for userID in lines:
            if ":" in userID:
                movieIDSplit = userID.split(':')
                movieID = int(movieIDSplit[0])
            else:
                if movieID in probeDict:                    
                    probeDict[movieID].append(int(userID))
                else:
                    probeDict[movieID] = [int(userID)]
                                            
        pfile.close()
    return probeDict


def calculateDeviation(ratingsMatrix):   
    nonZeroIndices = ratingsMatrix.nonzero()[1]
    deviationSum = 0.0 
    numOfRatings = 0
    for index in nonZeroIndices:
        deviationSum += (ratingsMatrix[0, index] - allRatingsMean)
        numOfRatings += 1   
    return (deviationSum, len(nonZeroIndices))


probeSetRatingsDict = {}
def removeGlobalEffects(lm):        
    # calculating the movie-effects 
    for key in probeDict.iterkeys():
        ratingsForMovie = csr_matrix(lm.getrow(key-1))
        deviationSum, numOfRatings = calculateDeviation(ratingsForMovie)
        movieEffect = deviationSum / (movieEffectTuningParam + numOfRatings)
        movieEffectDict[key] = movieEffect        

    with open(DATA_PATH + "movieEffectRatings.txt") as mfile:
        for key in movieEffectDict.iterkeys():
            mfile.write(str(movieEffectDict.get(key)))
        mfile.close()


def main():
    global probeDict
    probeFilePath = DATA_PATH + "probe_converted.txt"
    probeDict = createProbeDict(probeFilePath)    
    removeGlobalEffects(lm)
    
if __name__ == "__main__":
    past = time.time()    
    main()
    print "Time:%.3f" % (time.time() - past), "seconds"