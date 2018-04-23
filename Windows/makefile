all: build

build: main.o othello.o game.o checkers.o connect4.o game2.o makefile
	g++ othello.o main.o game.o checkers.o connect4.o game2.o

main.o: main.cc game.h colors.h othello.h checkers.cc checkers.h game.cc othello.cc connect4.h connect4.cc
	g++ -c main.cc

othello.o: othello.cc game.h colors.h 
	g++ -c othello.cc

game.o: game.cc game.h
	g++ -c game.cc

game2.0: game2.cc game2.h
	g++ -c game2.cc

checkers.o: checkers.cc game.h game.cc colors.h
	g++ -c checkers.cc

connect4.o: connect4.cc connect4.h
	g++ -c connect4.cc

clean: 
	rm *.o a.out
