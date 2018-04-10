

#include <iostream>   // Provides cin, cout
#include <string>     // Provides string
#include <iomanip>
#include "game.h"     // Provides definition of game class
#include "othello.h"
#include <fstream>
#include <string>
#include "colors.h"
using namespace std;

namespace main_savitch_14{



	////////////////////////////////

	//Menu for converting user input to var with escape code
	string Othello::get_color(std::string c, bool tile){
		int i;
		if (c == "BLACK")
			i = 0;
		else if (c == "RED")
			i = 1;
		else if (c == "GREEN")
			i = 2;
		else if (c == "YELLOW")
			i = 3;
		else if (c == "BLUE")
			i = 4;
		else if (c == "MAGENTA")
			i = 5;
		else if (c == "CYAN")
			i = 6;
		else if (c == "BR_CYAN")
			i = 7;
		else if (c == "WHITE")
			i = 8;
		else if (c == "BR_BLACK")
			i = 9;
		else
			i = -1;

		if(tile == true){
			switch(i){
				case 0:
				return B_BLACK;
				break;
				case 1:
				return B_RED;
				break;
				case 2:
				return B_GREEN;
				break;
				case 3:
				return B_YELLOW;
				break;
				case 4:
				return B_BLUE;
				break;
				case 5:
				return B_MAGENTA;
				break;
				case 6:
				return B_CYAN;
				break;
				case 7:
				return B_CYAN;
				break;
				case 8:
				return B_WHITE;
				break;
				case 9:
				return B_BR_BLACK;
				default:
				return "FAIL";
				break;
			}
		}
		else{
			switch(i){
				case 0:
				return BLACK;
				break;
				case 1:
				return RED;
				break;
				case 2:
				return GREEN;
				break;
				case 3:
				return YELLOW;
				break;
				case 4:
				return BLUE;
				break;
				case 5:
				return MAGENTA;
				break;
				case 6:
				return CYAN;
				break;
				case 7:
				return BR_CYAN;
				break;
				case 8:
				return WHITE;
				break;
				case 9:
				return B_BR_BLACK;
				default:
				return "FAIL";
				break;
			}
		}

	}

    ////////////////////////////////

    Othello::Othello(){
    	pass = 0;
    	for(int i = 0; i < 8; i++){
			for (int j = 0; j < 8; j++){
				board[i][j].is_occupied = false;
				board[i][j].is_white = false;
				board[i][j].is_black = false;
			}
		}
		board[3][3].is_occupied = true;
		board[3][3].is_white = true;
		board[3][4].is_occupied = true;
		board[3][4].is_black = true;
		board[4][3].is_occupied = true;
		board[4][3].is_black = true;
		board[4][4].is_occupied = true;
		board[4][4].is_white = true;
    }

    ////////////////////////////////

    Othello::Othello(int r, int c, std::string c1, std::string c2, std::string ctext){
    	pass = 0;
    	rows = r;
    	columns = c;
    	bool tile = false;
    	char answer;
    	ifstream ins;
    	ofstream outs;

    	cltext = get_color(ctext, tile);
    	tile = true;
    	cl1 = get_color(c1, tile);
    	cl2 = get_color(c2, tile);

    	ins.open("cb.txt");
    	if (ins.fail()){
    		cout << cl1 << cltext << "These are your color settings." << RESET << endl;
    		cout << cl2 << cltext << "These are your color settings." << RESET << endl;
    		display_status();
	    	cout << "This is your current color setting. Would you like to save this?\n";
	    	cout << "You can always undo this by deleting the file called 'cb' in the game's folder) y/n: ";
	    	cin >> answer;
	    	if (answer == 'Y' || answer == 'y'){
	    		outs.open("cb.txt");
	    		outs << c1 << endl;
	    		outs << c2 << endl;
	    		outs << ctext << endl;
	    		outs.close();
	    	}
	    	cin.ignore();
	    }
	    ins.close();

    	int rmidf, cmidf, rmidc, cmidc;
    	rmidf = r/2 - 1;	//row middle floor
    	cmidf = c/2 - 1;	//column middle floor
    	rmidc = r/2;		//row middle ceiling
    	cmidc = c/2;		//column middle ceiling

    	for(int i = 0; i < r; i++){
			for (int j = 0; j < c; j++){
				board[i][j].is_occupied = false;
				board[i][j].is_white = false;
				board[i][j].is_black = false;
			}
		}
		board[rmidf][cmidf].is_occupied = true;
		board[rmidf][cmidf].is_white = true;
		board[rmidf][cmidc].is_occupied = true;
		board[rmidf][cmidc].is_black = true;
		board[rmidc][cmidf].is_occupied = true;
		board[rmidc][cmidf].is_black = true;
		board[rmidc][cmidc].is_occupied = true;
		board[rmidc][cmidc].is_white = true;
    }

    ////////////////////////////////


    void Space::flip(){
    	if (is_white == true){is_white = false; is_black = true;}
    	else if (is_black == true){is_white = true; is_black = false;}
    	else {is_occupied = false;}
    }

    ////////////////////////////////

    game* Othello::clone()const{
		return new Othello(*this);
	}

    ////////////////////////////////

    void Othello::compute_moves(std::queue<std::string>& moves) const{
    	//cout << "Valid moves: "; 
    	for (int j = 0; j < columns; j++){
    		for (int i = 0; i < rows; i++){
    			char a, b, c;
    			string move;
    			a = char(j + 'A');
    			move = a;
    			if (i == 9){
    				b = char(int(i+1)/10 + 48);
    				c = char(int(i+1)%10 + 48);
    				move += b;
    				move += c;
    			}
    			else if (i > 9){
    				b = char(int(i)/10 + 48);
    				c = char(int(i+1)%10 + 48);
    				move += b;
    				move += c;
    			}
    			else{
    				b = char(int(i) + 49);
    				move += b;
    			}

    			if (is_legal(move)){
    				//cout << move << "  ";
    				moves.push(move);
    			}
    		}
    	}

    	//cout << endl;
    };

    ////////////////////////////////

    void Othello::display_status( ) const{
	    cout << endl;
		cout << "     ";
		for (int z = 0; z < columns; z++){
			cout << "  " << char(z + 'A') << " ";
		}
		cout << endl;
		cout << "      ";
		for (int z = 0; z < columns; z++){
			cout << "___ ";
		}
		cout << endl;
		for (int i = 0; i < rows; ++i){
			cout << setw(3) << i + 1 << "  ";
			for (int j = 0; j < columns; ++j){
				if (i % 2 == 0){
					if (j % 2 == 0)
						cout << cl1;		//default is red
					else
						cout << cl2;

				}
				else{
					if (j % 2 == 0)
							cout << cl2;
					else
							cout << cl1;
				}
				if (board[i][j].is_occupied == true){
					if (board[i][j].is_white == true)
						cout << cltext << "| 0 " << RESET;	//Modified white in colors.h to actually be bright white (1;37) for clarity's sake
					else
						cout << cltext << "| X " << RESET;
				}
				else
					cout << cltext << "|   " << RESET;
				cout << RESET;
			}
			cout << cltext << "| " << RESET << i + 1 << endl;
		}
		cout << "      ";
		for (int z = 0; z < columns; z++){
			cout << "--- ";
		}
		cout << endl << "     ";
		for (int z = 0; z < columns; z++){
			cout << "  " << char(z + 'A') << " ";
		}
		cout << endl << "......";
		for (int i = 0; i < columns; i++){
			cout << "....";
		}
		cout << "..." << endl;
		//cout << "\n.......................................\n";



}
   
    ////////////////////////////////

    int Othello::evaluate( ) const{
    	int total = 0;
    	for (int i = 0; i < rows; ++i){
	    		for (int j = 0; j < columns; ++j){
	    			if (board[i][j].is_white)
	    				total++;
	    			if (board[i][j].is_black)
	    				total--;
	    		}
	    	}

    	return total;
    }

    ////////////////////////////////

    bool Othello::is_game_over( ) const{
    	if (pass == 2){
    		cout << "Game is over.\n";
    		return true;
    	}
    	else return false;
    }

    ////////////////////////////////

    bool Othello::is_legal(const std::string& move) const{
    	int charval;
    	int row;
    	//const Space* valid[64];
    	//int validcount = 0;

    	if (move == "pass")
    		return true;
    	//Converts values to array-friendly ints
    	charval = (int(toupper(move[0])) - 'A');
    	if(move.length()>2){
    		row = int(move[1]-'0')*10 + int(move[2]-'0');
    		row--;
    	}
    	else
    		row = int(move[1])-'1';

    	//First round of checks, guarantees a place on the board
    	if (charval < 0 || charval > columns - 1)
    		return false;
    	else if (row < 0 || row > rows - 1){
    		return false;
    	}


    	//Checks if space is occupied
    	if (board[row][charval].is_occupied == true){
    		return false;
    	}

    	if(is_consecutive(move, charval, row))
    		return true;

    	//only returns if the is_consecutive checks fail
    	return false;

    }

    ////////////////////////////////

    bool Othello::is_consecutive(const std::string& move, int charval, int row)const{

    	int max;	//diagonal max value
    	if (rows < columns)
    		max = rows;
    	else
    		max = columns;	//IMPLEMENT

    	if (last_mover() == COMPUTER){
	    	//Guarantees an adjacent spot is occupied
	    	if(!(charval + 1 > columns - 1) && board[row][charval+1].is_white == true){}	//right
	    	else if(!(charval - 1 < 0) &&board[row][charval-1].is_white == true){}	//left
	    	else if(!(row + 1 > rows - 1) &&board[row+1][charval].is_white == true){}	//down
	    	else if(!(row - 1 < 0) &&board[row-1][charval].is_white == true){}	//up
	    	else
	    		return false;
    	}
    	else{
    		if(!(charval + 1 > columns - 1) &&board[row][charval+1].is_black == true){}	//right
	    	else if(!(charval - 1 < 0) &&board[row][charval-1].is_black == true){}	//left
	    	else if(!(row + 1 > rows - 1) &&board[row+1][charval].is_black == true){}	//down
	    	else if(!(row - 1 < 0) &&board[row-1][charval].is_black == true){}	//up
	    	else
	    		return false;
    	}


    	//Makes sure a flip occurs
    	if (last_mover() == COMPUTER){
    		if (!(charval + 1 > columns -1)){
    		if (board[row][charval+1].is_white){
	    		for (int i = 2; i < columns; i++){
	    			if (!(charval + i > columns -1)){
	    			if (board[row][charval+i].is_black == true)
	    				return true;
	    			if (board[row][charval+i].is_occupied == false)
	    				break;
	    		}
	    		}
	    	}
	    	}
	    	if (!(row + 1 > rows -1)){
	    	if (board[row+1][charval].is_white){
	    		for (int i = 2; i < rows; i++){
	    			if (!(row + i > rows -1)){
	    			if (board[row+i][charval].is_black == true)
	    				return true;
	    			if (board[row+i][charval].is_occupied == false)
	    				break;
	    		}
	    		}
	    	}
	    	}
	    	if (!(charval -1 < 0)){
	    	if (board[row][charval-1].is_white){
	    		for (int i = 2; i < columns; i++){
	    			if (!(charval -i < 0)){
	    			if (board[row][charval-i].is_black == true)
	    				return true;
	    			if (board[row][charval-i].is_occupied == false)
	    				break;
	    		}
	    		}
	    	}
	    	}
	    	if (!(row-1 < 0)){
	    	if (board[row-1][charval].is_white){
	    		for (int i = 2; i < rows; i++){
	    			if (!(row-i < 0)){
	    			if (board[row-i][charval].is_black == true)
	    				return true;
	    			if (board[row-i][charval].is_occupied == false)
	    				break;
	    		}
	    		}
	    	}
	    	}
	    	if (!(row - 1 < 0 || charval - 1 < 0)){
	    	if (board[row-1][charval-1].is_white){
	    		for (int i = 2; i < rows; i++){
	    			if (!(row - i < 0 || charval - i < 0)){
	    			if (board[row-i][charval-i].is_black == true)
	    				return true;
	    			if (board[row-i][charval-i].is_occupied == false)
	    				break;
	    		}
	    		}
	    	}
	    	}
	    	if (!(row-1<0 || charval+1 > columns -1)){
	    	if (board[row-1][charval+1].is_white){
	    		for (int i = 2; i < rows; i++){
	    			if (!(row-i<0 || charval+i > columns -1)){
	    			if (board[row-i][charval+i].is_black == true)
	    				return true;
	    			if (board[row-i][charval+i].is_occupied == false)
	    				break;
	    		}
	    		}
	    	}
	    	}
	    	if (!(row+1>rows -1 || charval+1>columns -1)){
	    	if (board[row+1][charval+1].is_white){
	    		for (int i = 2; i < rows; i++){
	    			if (!(row+i>rows -1 || charval+i>columns -1)){
	    			if (board[row+i][charval+i].is_black == true)
	    				return true;
	    			if (board[row+i][charval+i].is_occupied == false)
	    				break;
	    		}
	    		}
	    	}
	    	}
	    	if (!(row + 1 > rows - 1 || charval - 1 < 0)){
	    	if (board[row+1][charval-1].is_white){
	    		for (int i = 2; i < rows; i++){
	    			if (!(row + i > rows - 1 || charval - i < 0)){
	    			if (board[row+i][charval-i].is_black == true)
	    				return true;
	    			if (board[row+i][charval-i].is_occupied == false)
	    				break;
	    		}
	    		}
	    	}
	    	}

	    }
	    else{
	    	if (!(charval + 1 > columns - 1)){
	    	if (board[row][charval+1].is_black){
	    		for (int i = 2; i < columns; i++){
	    			if (!(charval + i > columns - 1)){
	    			if (board[row][charval+i].is_white == true)
	    				return true;
	    			if (board[row][charval+i].is_occupied == false)
	    				break;
	    		}
	    		}
	    	}
	    	}
	    	if (!((row + 1) > rows - 1)){
	    	if (board[row+1][charval].is_black){
	    		for (int i = 2; i < rows; i++){
	    			if (!((row + i) > rows - 1)){
	    			if (board[row+i][charval].is_white == true)
	    				return true;
	    			if (board[row+i][charval].is_occupied == false)
	    				break;
	    		}
	    		}
	    	}
	    	}
	    	if (!((charval - 1) < 0)){
	    	if (board[row][charval-1].is_black){
	    		for (int i = 2; i < columns; i++){
	    			if (!((charval - i) < 0)){
	    			if (board[row][charval-i].is_white == true)
	    				return true;
	    			if (board[row][charval-i].is_occupied == false)
	    				break;
	    		}
	    		}
	    	}
	    	}
	    	if (!((row - 1) < 0)){
	    	if (board[row-1][charval].is_black){
	    		for (int i = 2; i < rows; i++){
	    			if (!((row - i) < 0)){
	    			if (board[row-i][charval].is_white == true)
	    				return true;
	    			if (board[row-i][charval].is_occupied == false)
	    				break;
	    		}
	    		}
	    	}
	    	}
	    	if (!((row - 1) < 0 || (charval - 1) < 0)){
	    	if (board[row-1][charval-1].is_black){
	    		for (int i = 2; i < max; i++){
	    			if (!((row - i) < 0 || (charval - i) < 0)){
	    			if (board[row-i][charval-i].is_white == true)
	    				return true;
	    			if (board[row-i][charval-i].is_occupied == false)
	    				break;
	    		}
	    		}
	    	}
	   		}
	   		if (!((row - 1) < 0 || (charval + 1) > columns - 1)){
	    	if (board[row-1][charval+1].is_black){
	    		for (int i = 2; i < max; i++){
	    			if (!((row - i) < 0 || (charval + i) > columns - 1)){
	    			if (board[row-i][charval+i].is_white == true)
	    				return true;
	    			if (board[row-i][charval+i].is_occupied == false)
	    				break;
	    		}
	    		}
	    	}
	   		}
	   		if (!(row + 1 > rows - 1) || charval + 1 > columns - 1){
	    	if (board[row+1][charval+1].is_black){
	    		for (int i = 2; i < max; i++){
	    			if (!(row + i > rows - 1) || charval + i > columns - 1){
	    			if (board[row+i][charval+i].is_white == true)
	    				return true;
	    			if (board[row+i][charval+i].is_occupied == false)
	    				break;
	    		}
	    		}
	    	}
	    	}
	    	if (!(row + 1 > rows - 1 || charval - 1 < 0)){
	    	if (board[row+1][charval-1].is_black){
	    		for (int i = 2; i < max; i++){
	    			if (!(row + i > rows - 1 || charval - i < 0)){
	    			if (board[row+i][charval-i].is_white == true)
	    				return true;
	    			if (board[row+i][charval-i].is_occupied == false)
	    				break;
	    		}
	    		}
	    	}
	    	}
	    }

    	//If the set of if/elses didn't return false but by now true hasn't been returned, it's a no-go
    	return false;


    }

    ////////////////////////////////

    void Othello::make_move(const std::string& move){
    	int charval, row, toflip = 0;
    	int fliprows[64], flipcols[64];
    	int rnext = 0;
    	int max;	//diagonal max value
    	if (rows < columns)
    		max = rows;
    	else
    		max = columns;	//IMPLEMENT


    	if (move != "pass"){

    		pass = 0;
    	bool continueflip = false;
    	charval = (int(toupper(move[0])) - 'A');
    	if(move.length()>2)
    		row = int(move[1]-'0')*10 + int(move[2]-'0');
    	else
    		row = int(move[1])-'0'-1;

/*    	if (last_mover() == COMPUTER)
    		cout << "\nP2 turn: ";
    	else cout << "\nP1 turn: ";
*/
    	//Set chosen piece first
    	board[row][charval].is_occupied = true;
    	if (last_mover() == COMPUTER)
    		board[row][charval].is_black = true;
    	else
    		board[row][charval].is_white = true;

    	//**********************************************************************
		//This next section contains all the checking for and execution of flips
		//**********************************************************************

    	if (last_mover() == COMPUTER){
	    	//Check to the right for a flip
	    	if (!(charval + 1 > columns - 1)){
	    	if (board[row][charval+1].is_white == true){
				for (int i = 1; i < columns; i++){
					if (!(charval + i > columns - 1)){
					if(board[row][charval+i].is_occupied)
						toflip++;
					if (board[row][charval+i].is_black == true){
						continueflip = true;
						toflip--;
						break;
					}
				}
				}
				if (continueflip){
					for (int i = 1; i < toflip + 1; ++i)
					{
						fliprows[rnext] = row;
						flipcols[rnext] = charval + i;
						rnext++;
						

					}
				}
			}
			}
			toflip = 0;		//Reset value
			continueflip = false;

			//Check to the left for a flip
			if (!(charval - 1 < 0)){
			if (board[row][charval-1].is_white == true){
				for (int i = 1; i < columns; i++){
					if (!(charval - i < 0)){
					if(board[row][charval-i].is_occupied)
						toflip++;
					if (board[row][charval-i].is_black == true){
						continueflip = true;
						toflip--;
						break;
					}
				}
				}
				if (continueflip){
					for (int i = 1; i < toflip + 1; ++i)
					{
						fliprows[rnext] = row;
						flipcols[rnext] = charval - i;
						rnext++;
						
					}
				}
			}
			}
			toflip = 0;		//Reset value
			continueflip = false;

			//Check downwards for a flip
			if (!(row + 1 > rows - 1)){
			if (board[row+1][charval].is_white == true){
				for (int i = 1; i < rows; i++){
					if (!(row + i > rows - 1)){
					if(board[row+i][charval].is_occupied)
						toflip++;
					if (board[row+i][charval].is_black == true){
						continueflip = true;
						toflip--;
						break;
					}
				}
				}
				if (continueflip){
					for (int i = 1; i < toflip + 1; ++i)
					{
						fliprows[rnext] = row+ i;
						flipcols[rnext] = charval;
						rnext++;
						
					}
				}
			}
			}
			toflip = 0; 	//Reset value
			continueflip = false;

			//Check upwards for a flip
			if (!(row - 1 < 0)){
			if (board[row-1][charval].is_white == true){
				for (int i = 1; i < rows; i++){
					if (!(row - i < 0)){
					if(board[row-i][charval].is_occupied)
						toflip++;
					if (board[row-i][charval].is_black == true){
						continueflip = true;
						toflip--;
						break;
					}
				}
				}
				if (continueflip){
					for (int i = 1; i < toflip + 1; ++i)
					{
						fliprows[rnext] = row - i;
						flipcols[rnext] = charval;
						rnext++;
						
					}
				}
			}
			}
			toflip = 0; 	//Reset value
			continueflip = false;

			//Check up and to the left for a diagonal 
			if (!(row - 1 < 0 || charval - 1 < 0)){
			if (board[row-1][charval-1].is_white == true){
				for (int i = 1; i < rows; i++){
					if (!(row - i < 0 || charval - i < 0)){
					if(board[row-i][charval-i].is_occupied)
						toflip++;
					if (board[row-i][charval-i].is_black == true){
						continueflip = true;
						toflip--;
						break;
					}
				}
				}
				if (continueflip){
					for (int i = 1; i < toflip + 1; ++i)
					{
						fliprows[rnext] = row - i;
						flipcols[rnext] = charval - i;
						rnext++;
						
					}
				}
			}
			}
			toflip = 0; 	//Reset value
			continueflip = false;

			//Check up and to the right for a diagonal
			if (!(row -1 < 0 || charval + 1 > columns - 1)){ 
			if (board[row-1][charval+1].is_white == true){ 
				for (int i = 1; i < max; i++){
					if (!(row -i < 0 || charval + i > columns - 1)){
					if(board[row-i][charval+i].is_occupied)
						toflip++;
					if (board[row-i][charval+i].is_black == true){
						continueflip = true;
						toflip--;
						break;
					}
				}
				}
				if (continueflip){
					for (int i = 1; i < toflip + 1; ++i)
					{
						fliprows[rnext] = row - i;
						flipcols[rnext] = charval + i;
						rnext++;
						
					}
				}
			}
			}
			toflip = 0; 	//Reset value
			continueflip = false;

			//Check down and to the right for a diagonal 
			if (!(row + 1 > rows - 1 || charval + 1 > columns - 1)){
			if (board[row+1][charval+1].is_white == true){
				for (int i = 1; i < max; i++){
					if (!(row + i > rows - 1 || charval + i > columns - 1)){
					if(board[row+i][charval+i].is_occupied)
						toflip++;
					if (board[row+i][charval+i].is_black == true){
						continueflip = true;
						toflip--;
						break;
					}
				}
				}
				if (continueflip){
					for (int i = 1; i < toflip + 1; ++i)
					{
						fliprows[rnext] = row + i;
						flipcols[rnext] = charval + i;
						rnext++;
						
					}
				}
			}
			}
			toflip = 0; 	//Reset value
			continueflip = false;

			//Check down and to the left for a diagonal 
			if (!(row + 1 > rows - 1 || charval - 1 < 0)){
			if (board[row+1][charval-1].is_white == true){
				for (int i = 1; i < max; i++){
					if (!(row + i > rows - 1 || charval - i < 0)){
					if(board[row+i][charval-i].is_occupied)
						toflip++;
					if (board[row+i][charval-i].is_black == true){
						continueflip = true;
						toflip--;
						break;
					}
				}
				}
				if (continueflip){
					for (int i = 1; i < toflip + 1; ++i)
					{
						fliprows[rnext] = row + i;
						flipcols[rnext] = charval - i;
						rnext++;
						
					}
				}
			}
			}
			toflip = 0; 	//Reset value
			continueflip = false;
		}
		else{
			//Check to the right for a flip
			if (!(charval + 1 > columns - 1)){
	    	if (board[row][charval+1].is_black == true){
				for (int i = 1; i < columns; i++){
					if (!(charval + i > columns - 1)){
					if(board[row][charval+i].is_occupied)
						toflip++;
					if (board[row][charval+i].is_white == true){
						continueflip = true;
						toflip--;
						break;
					}
				}
				}
				if (continueflip){
					for (int i = 1; i < toflip + 1; ++i)
					{
						fliprows[rnext] = row;
						flipcols[rnext] = charval + i;
						rnext++;
						
					}
				}
			}
			}
			toflip = 0;		//Reset value
			continueflip = false;

			//Check to the left for a flip
			if (!(charval - 1 < 0)){
			if (board[row][charval-1].is_black == true){
				for (int i = 1; i < columns; i++){
					if (!(charval - i < 0)){
					if(board[row][charval-i].is_occupied)
						toflip++;
					if (board[row][charval-i].is_white == true){
						continueflip = true;
						toflip--;
						break;
					}
				}
				}
				if (continueflip){
					for (int i = 1; i < toflip + 1; ++i)
					{
						fliprows[rnext] = row;
						flipcols[rnext] = charval - i;
						rnext++;
						
					}
				}
			}
			}
			toflip = 0;		//Reset value
			continueflip = false;

			//Check downwards for a flip
			if (!(row + 1 > rows - 1)){
			if (board[row+1][charval].is_black == true){
				for (int i = 1; i < rows; i++){
					if (!(row + i > rows - 1)){
					if(board[row+i][charval].is_occupied)
						toflip++;
					if (board[row+i][charval].is_white == true){
						continueflip = true;
						toflip--;
						break;
					}
				}
				}
				if (continueflip){
					for (int i = 1; i < toflip + 1; ++i)
					{
						fliprows[rnext] = row + i;
						flipcols[rnext] = charval;
						rnext++;
						
					}
				}
			}
			}
			toflip = 0; 	//Reset value
			continueflip = false;

			//Check upwards for a flip
			if (!(row - 1 < 0)){
			if (board[row-1][charval].is_black == true){

				for (int i = 1; i < rows; i++){
					if (!(row - i < 0)){
					if(board[row-i][charval].is_occupied)
						toflip++;
					if (board[row-i][charval].is_white == true){
						continueflip = true;
						toflip--;
						break;
					}
				}
			}
				if (continueflip){
					for (int i = 1; i < toflip + 1; ++i)
					{
						fliprows[rnext] = row - i;
						flipcols[rnext] = charval;
						rnext++;
						
					}
				}
			}
			}
			toflip = 0; 	//Reset value
			continueflip = false;

			//Check up and to the left for a diagonal 
			if (!(row - 1 < 0 || charval - 1 < 0)){
			if (board[row-1][charval-1].is_black == true){
				for (int i = 1; i < max; i++){
					if (!(row - i < 0 || charval - i < 0)){
					if(board[row-i][charval-i].is_occupied)
						toflip++;
					if (board[row-i][charval-i].is_white == true){
						continueflip = true;
						toflip--;
						break;
					}
				}
				}
				if (continueflip){
					for (int i = 1; i < toflip + 1; ++i)
					{
						fliprows[rnext] = row - i;
						flipcols[rnext] = charval - i;
						rnext++;
											
					}
				}
			}
			}
			toflip = 0; 	//Reset value
			continueflip = false;

			//Check up and to the right for a diagonal 
			if (!(row - 1 < 0|| charval + 1 > columns - 1)){
			if (board[row-1][charval+1].is_black == true){
				for (int i = 1; i < max; i++){
					if (!(row - i < 0|| charval + i > columns - 1)){
					if(board[row-i][charval+i].is_occupied)
						toflip++;
					if (board[row-i][charval+i].is_white == true){
						continueflip = true;
						toflip--;
						break;
					}
				}
				}
				if (continueflip){
					for (int i = 1; i < toflip + 1; ++i)
					{
						fliprows[rnext] = row - i;
						flipcols[rnext] = charval + i;
						rnext++;
						
					}
				}
			}
			}
			toflip = 0; 	//Reset value
			continueflip = false;

			//Check down and to the right for a diagonal 
			if (!(row + 1 > rows - 1 || charval + 1 > columns - 1)){
			if (board[row+1][charval+1].is_black == true){
				for (int i = 1; i < max; i++){
					if (!(row + i > rows - 1 || charval + i > columns - 1)){
					if(board[row+i][charval+i].is_occupied)
						toflip++;
					if (board[row+i][charval+i].is_white == true){
						continueflip = true;
						toflip--;
						break;
					}
				}
				}
				if (continueflip){
					for (int i = 1; i < toflip + 1; ++i)
					{
						fliprows[rnext] = row + i;
						flipcols[rnext] = charval + i;
						rnext++;
						
					}
				}
			}
			}
			toflip = 0; 	//Reset value
			continueflip = false;

			//Check down and to the left for a diagonal 
			if (!(row + 1 > rows - 1 || charval - 1 < 0)){
			if (board[row+1][charval-1].is_black == true){
				for (int i = 1; i < max; i++){
					if (!(row + i > rows - 1 || charval - i < 0)){
					if(board[row+i][charval-i].is_occupied)
						toflip++;
					if (board[row+i][charval-i].is_white == true){
						continueflip = true;
						toflip--;
						break;
					}
				}
				}
				if (continueflip == true){
					for (int i = 1; i < toflip + 1; ++i)
					{
						fliprows[rnext] = row + i;
						flipcols[rnext] = charval - i;
						rnext++;
					}
				}
			}
			}
			toflip = 0; 	//Reset value
			continueflip = false;
		}

		for (int i = 0; i < rnext; i++){
			board[fliprows[i]][flipcols[i]].flip();
		}

	}else pass++;

		game::make_move(move);
    }

    ////////////////////////////////

    string Othello::get_user_move( ) const
    {
		string answer;
		queue<string> moves;
		compute_moves(moves);
		if(!moves.empty()){
			display_message("Your move, please: ");
			getline(cin, answer);
		}
		else{
			cout << "You have no valid moves left.\n";
			answer = "pass";
			if (last_mover() == COMPUTER){
				cout << "Passing to P2.\n";
			}
			else cout << "Passing to P1.\n";
		}
		return answer;
    }

    ////////////////////////////////

    game::who Othello::winning()const{
    	int score = evaluate();
    	if (score < 0) return HUMAN;
    	else if (score > 0) return COMPUTER;
    	else return NEUTRAL;

    }
}

