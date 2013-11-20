CC = g++

SOURCE = main.cpp Helper.cpp Helper.h KNN.cpp KNN.h MovieRatings.cpp MovieRatings.h UserRatings.cpp UserRatings.h Ratings.h

OBJ = main.o Helper.o KNN.o MovieRatings.o UserRatings.o

all : main

main : $(OBJ)
	$(CC) -o FW $(OBJ) 

main.o : main.cpp MovieRatings.h UserRatings.h Helper.h
	$(CC) -c main.cpp -o main.o

Helper.o: Helper.cpp Helper.h
	$(CC) -c Helper.cpp

KNN.o: KNN.cpp KNN.h
	$(CC) -c KNN.cpp

MovieRatings.o: MovieRatings.cpp MovieRatings.h
	$(CC) -c MovieRatings.cpp

UserRatings.o: UserRatings.cpp UserRatings.h
	$(CC) -c UserRatings.cpp

clean :
	rm $(OBJ) FW

tgz : $(SOURCE)
	tar -cvvf FW.tar $(SOURCE) Makefile
	gzip FW.tar
