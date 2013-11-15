import time
#import scipy.sparse as SP
from scipy.sparse import csr_matrix

DIR_PATH = "/media/01244D4977874BCC/DataSet/"
PROJECT_PATH = "/home/freax/netflix-prize-exp/"
DATA_PATH = PROJECT_PATH + "data/"

allRatingsMean = 3.6043
userEffectTuningParam = 20

userEffectDict = {}

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
    for index in nonZeroIndices:
        deviationSum += (ratingsMatrix[0, index] - allRatingsMean)        
    return (deviationSum, len(nonZeroIndices))


probeSetRatingsDict = {}
def removeGlobalEffects(lm):
    # calculating the user-effects 
    for user in probeDict.itervalues():
        if user not in userEffectDict:
            ratingsForUser = csr_matrix(lm.getrow(user-1))
            deviationSum, numOfRatings = calculateDeviation(ratingsForUser)
            userEffect = deviationSum / (userEffectTuningParam + numOfRatings)
            userEffectDict[user] = userEffect

    with open(DATA_PATH + "userEffectRatings.txt") as ufile:
        for key in userEffectDict.iterkeys():
            ufile.write(str(key) + ":" + str(userEffectDict.get(key)))
        ufile.close()

def main():
    probeFilePath = DATA_PATH + "probe_converted.txt"
    probeDict = createProbeDict(probeFilePath)    
    lmT = lm.transpose()
    removeGlobalEffects(lmT)
    
if __name__ == "__main__":
    past = time.time()    
    main()
    print "Time:%.3f" % (time.time() - past), "seconds"