build: main.o othello.o game.o
	g++ -o othello othello.o main.o game.o

main.o: main.cc game.h colors.h othello.h
	g++ -c main.cc

othello.o: othello.cc game.h colors.h
	g++ -c othello.cc

game.o: game.cc game.h
	g++ -c game.cc