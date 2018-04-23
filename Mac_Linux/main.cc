#include<iostream>
#include<iomanip>
#include <cstdlib>
#include<fstream>
#include"game.h"
#include"game2.h"
#include"othello.h"
#include"colors.h"
#include"checkers.h"
#include"connect4.h"

int MENU1 = 0;
using namespace std;
using namespace main_savitch_14;

void colormenu(string &c1, string &c2, string &ctext);///color menu for othello

int main(){
	bool quit = 1;///used for playing again
	char quit_choice;
	while(quit){
	char choice1;
	cout << "Would you like to Play a game of "<<endl;
	cout <<"Checkers (c) , Othello (o), or Connect4(4) ?"<<endl;
	cout << "Choice : ";
	cin >> choice1;
	cout << endl;
	
	if((choice1 == 'o') || (choice1 == 'O')){///if they choose othello
	game::who winner;
	int rowsize, columnsize;
	string c1, c2, ctext;
	char colorcheck;
	ifstream ins;
	//Othello mygame;

	cout << "\nWelcome to Othello/Reversi!\n";
	cout << "X (you) plays first. You can only place pieces adjacent (not diagonally) to an opponent's piece.\n";
	cout << "Pieces can only be positioned such that they cause at least one opponent's piece to be enclosed on two sides by yours.\n";

	

	cout << "\nChoose an even row size between 4 and 18 (8 is normal): ";
	cin >> rowsize;
	while (rowsize % 2 != 0 || rowsize < 4 || rowsize > 18){
		cout << "Invalid size.\n";
		cout << "Choose an even row size from 4-18: ";
		cin >> rowsize;
	}
	cout << "Choose an even column size between 4 and 18 (8 is normal): ";
	cin >> columnsize;
	while (columnsize % 2 != 0 || columnsize < 4 || columnsize > 18){
		cout << "Invalid size.\n";
		cout << "Choose an even row size from 4-18: ";
		cin >> columnsize;
	}

	cin.ignore();

	cout << "Would you like to use colorblindness settings? (y/n): ";
	cin >> colorcheck;
	if (colorcheck == 'Y' || colorcheck == 'y'){
		ins.open("cb.txt");
		if (ins.fail()){
			colormenu(c1, c2, ctext);
		}
		else{
			if (ins.peek()== '\n' || ins.peek() == '\r')
				ins.ignore();
			getline(ins, c1);
			getline(ins, c2);
			getline(ins, ctext);
			cin.ignore();
		}
	}
	else{
		c1 = "RED";
		c2 = "CYAN";
		ctext = "WHITE";
		cin.ignore();
	}


	Othello mygame(rowsize, columnsize, c1, c2, ctext);


	winner = mygame.play();
	if(MENU1 == 0){
	if(winner == game::HUMAN)
	cout << "\n\nThe winner is P1!\n";
	else if(winner == game::NEUTRAL)
		cout << "\n\nThe game is a tie!\n";
	else if (winner == game::COMPUTER)
		cout << "\n\nThe winner is P2!\n";
	else cout << "\n\nI have no idea what happened.\n";
	}
	else{
		MENU1 = 0;
	}
	}
	
	else if((choice1 == 'c') || (choice1 == 'C')){///if they choose checkers
		Checkers game1;
		int winner;
		cout << "Player 1 is blue, player 2 is white" << endl;
		cin.ignore();
		winner = game1.play();
		if(MENU1 == 0){
		if(winner == main_savitch_14::game::HUMAN){
			cout << "Game over. Player 1 wins" << endl;
		}
		else{
			cout << "Game over. Player 2 wins" << endl;
		}
		}
		else{
			MENU1 = 0;
		}
	}
	else if((choice1 == '4')){///if they choose connect 4
		int choice;

    string restart;
    string colorSwap;

    ifstream fin;


        connectFour obj;
	cin.ignore();
        obj.play();
		if(MENU1 == 1){
			MENU1 = 0;
		}
	}
		
	
	else{///invalid choice
		cout << "Invalid Choice" << endl;
	}
	cout << "Would you like to keep playing? (y or n): ";
	cin >> quit_choice;
	cout << endl;
	if((quit_choice == 'n') || (quit_choice == 'N')){
		quit = 0;
	}
	else{///quit
		quit = 1;
	}


}
	return 0;
}
void colormenu(string &c1, string &c2, string &ctext){
	cout << "The following are your tile color options:\n\n";
	cout << WHITE << B_BLACK << "  BLACK  " << B_BR_BLACK << "  BR_BLACK  " << B_RED << "  RED  " << 
	B_GREEN << "  GREEN  " << RESET << endl << B_YELLOW << "  YELLOW  " << B_BLUE << "  BLUE  " << B_MAGENTA << "  MAGENTA  " <<
	B_CYAN << "  CYAN  " << BLACK << B_WHITE << "  WHITE  " << RESET << endl;
	cout << "\n\nPlease enter the first tile color you'd like (in capital letters, ex. 'BLUE'): ";
	if (cin.peek() == '\n'||cin.peek()=='\r')
		cin.ignore();
	getline(cin, c1);
	while (c1 != "BLACK" && c1 != "BR_BLACK" && c1 != "RED" && c1 != "GREEN" && 
		c1 != "YELLOW" && c1 != "BLUE" && c1 != "MAGENTA" && c1 != "CYAN" && c1 != "WHITE"){
		cout << "Invalid option. Please re-enter: ";
		if (cin.peek() == '\n' || cin.peek() == '\r')
			cin.ignore();
		getline(cin, c1);
	}
	cout << "Please enter the second tile color you'd like: ";
	if (cin.peek() == '\n' || cin.peek() == '\r')
		cin.ignore();
	getline(cin, c2);
	while ((c2 != "BLACK" && c2 != "BR_BLACK" && c2 != "RED" && c2 != "GREEN" && 
		c2 != "YELLOW" && c2 != "BLUE" && c2 != "MAGENTA" && c2 != "CYAN" && c2 != "WHITE") || (c2 == c1)){
		cout << "Invalid option. Please re-enter: ";
		if (cin.peek() == '\n' || cin.peek() == '\r')
			cin.ignore();
		getline(cin, c2);
	}

	cout << "Now choose a text color:\n";
	cout << B_WHITE << BLACK << "  BLACK  " << RED << "  RED  " << GREEN << "  GREEN  " << YELLOW << "YELLOW" << BLUE << "  BLUE  " <<
	MAGENTA << "  MAGENTA  " << CYAN << "  CYAN  " << BR_CYAN << "  BR_CYAN  " << B_BLACK << WHITE << "  WHITE  " << RESET << endl;
	cout << "Your text color choice: ";
	if (cin.peek() == '\n' || cin.peek() == '\r')
		cin.ignore();
	getline(cin, ctext);
	while ((ctext != "BLACK" && ctext != "RED" && ctext != "GREEN" && 
		ctext != "YELLOW" && ctext != "BLUE" && ctext != "MAGENTA" && ctext != "CYAN" && ctext != "BR_CYAN" && ctext != "WHITE") || (ctext == c1) || (ctext == c2)){
		cout << "Invalid option. Please re-enter: ";
		if (cin.peek() == '\n' || cin.peek() == '\r')
			cin.ignore();
		getline(cin, ctext);
	}

	cout << "Okay. A board will be created with " << c1 << " and " << c2 << " tiles using " << ctext << " text.\n";
}
