import os
import sys
import time
import resource
#import scipy.sparse as SP
import numpy as np
from scipy.sparse import lil_matrix

DIR_PATH = "/media/01244D4977874BCC/DataSet/"
ROW = 17770
COL = 2649429
fIdx = int(0)

past = time.time()
#create a lil_matrix
lm = lil_matrix((ROW, COL), dtype=np.int8)
#movieRatings = []
#get the files name in the directory DIR
files_array = []
os.chdir(DIR_PATH)
for files in os.listdir("."):
    if files.endswith(".txt"):
        files_array.append(files)

for filename in files_array:
    with open(DIR_PATH + filename) as f:
        #movieRatings.append([int(m) for m in f.readline().split(':') if m.isdigit()])
        mID = [int(m) for m in f.readline().split(':') if m.isdigit()]
        for line in f:
            if line:
                #movieRatings.append([int(n) for n in line.split(',') if n.isdigit()])
                movieRating = [int(n) for n in line.split(',') if n.isdigit()]
                lm[mID[0] - 1, movieRating[0] - 1] = movieRating[1] 
    f.close()
    
    print "\rMemory:",(resource.getrusage(resource.RUSAGE_SELF).ru_maxrss/1000000), "MB", "Files:", mID[0], "/", ROW, "(%f" % (float(mID[0])/float(ROW) * 100),"%)", "Time:%.3f" % (time.time() - past), "seconds",
    sys.stdout.flush() 