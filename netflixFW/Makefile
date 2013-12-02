CC = g++

CFLAGS = -Wall -g

SOURCE = main.cpp Algorithm.cpp Algorithm.h Database.cpp Database.h Config.h Helper.cpp Helper.h MovieRatings.cpp MovieRatings.h UserRatings.cpp UserRatings.h ProbeRatings.cpp ProbeRatings.h Ratings.h BaselinePredictor.cpp BaselinePredictor.h SVD.cpp SVD.h KNN.cpp KNN.h Similarity.cpp Similarity.h

OBJ = main.o Algorithm.o Database.o Helper.o MovieRatings.o UserRatings.o ProbeRatings.o BaselinePredictor.o SVD.o KNN.o Similarity.o

all : main

main : $(OBJ)
	$(CC) $(CFLAGS) -o fw $(OBJ) 

main.o : main.cpp Algorithm.h Database.h MovieRatings.h UserRatings.h Helper.h Config.h
	$(CC) -c main.cpp -o main.o

Helper.o : Helper.cpp Helper.h
	$(CC) -c Helper.cpp

Algorithm.o : Algorithm.cpp Algorithm.h
	$(CC) -c Algorithm.cpp

Database.o : Database.cpp Database.h
	$(CC) -c Database.cpp

ProbeRatings.o : ProbeRatings.cpp ProbeRatings.h
	$(CC) -c ProbeRatings.cpp

MovieRatings.o : MovieRatings.cpp MovieRatings.h
	$(CC) -c MovieRatings.cpp

UserRatings.o : UserRatings.cpp UserRatings.h
	$(CC) -c UserRatings.cpp

BaselinePredictor.o : BaselinePredictor.cpp BaselinePredictor.h
	$(CC) -c BaselinePredictor.cpp

KNN.o : KNN.cpp KNN.h
	$(CC) -c KNN.cpp

SVD.o : SVD.cpp SVD.h
	$(CC) -c SVD.cpp

Similarity.o : Similarity.cpp Similarity.h
	$(CC) -c Similarity.cpp

tgz : $(SOURCE)
	tar -cvvf fw.tar $(SOURCE) Makefile
	gzip fw.tar

clean :	
	rm $(OBJ) fw	


