#include<iostream>
#include<iomanip>
#include<fstream>
#include"game.h"
#include"othello.h"
#include"colors.h"
using namespace std;
using namespace main_savitch_14;

void colormenu(string &c1, string &c2, string &ctext);

int main(){
	game::who winner;
	int rowsize, columnsize;
	string c1, c2, ctext;
	char colorcheck;
	ifstream ins;
	//Othello mygame;

	cout << "\nWelcome to Othello/Reversi!\n";
	cout << "X (you) plays first. You can only place pieces adjacent (not diagonally) to an opponent's piece.\n";
	cout << "Pieces can only be positioned such that they cause at least one opponent's piece to be enclosed on two sides by yours.\n";

	ins.open("savedgame.txt");
	if (!(ins.fail())){
		char loadgame;
		cout << "Would you like to load your saved game? (y/n): ";
		cin >> loadgame;
		while (loadgame != 'Y' && loadgame != 'y' && loadgame != 'N' && loadgame != 'n'){
			cout << "Invalid answer. Would you like to load your saved game? (y/n): ";
			cin >> loadgame;
		}
		if (loadgame == 'Y' || loadgame == 'y'){
			cout << "Success\n";
		}
		else if (loadgame == 'N' || loadgame == 'n'){
			cout << "Won't do it.\n";
		}

	}

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

	if(winner == game::HUMAN)
	cout << "\n\nThe winner is P1!\n";
	else if(winner == game::NEUTRAL)
		cout << "\n\nThe game is a tie!\n";
	else if (winner == game::COMPUTER)
		cout << "\n\nThe winner is P2!\n";
	else cout << "\n\nI have no idea what happened.\n";

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