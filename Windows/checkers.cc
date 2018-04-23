/******************************************************************
    This is the implementation file for the checkers class, derived fromt he game class.
		Eric Hahn			April 12, 2016
********************************************************************/
#include "checkers.h"
#include "colors.h"
#include "space.h"
#include <string>
#include <iostream>
#include <queue>

using namespace std;

namespace main_savitch_14{
Checkers::Checkers(){
	int i = 0, j;
	while(i < 8){
		if(((i % 2) == 0) && (i < 4)){
			j = 1;
			while(j < 8){
				board[i][j].set_occupied(1);
				board[i][j].set_piece_color(0);
				board[i][j].set_king(0);
				j += 2;
			}
		}
		else if(((i % 2) == 0) && (i > 4)){
			j = 1;
			while(j < 8){
				board[i][j].set_occupied(1);
				board[i][j].set_piece_color(1);
				board[i][j].set_king(0);
				j += 2;
			}
		}
		else if(((i % 2) != 0) && (i < 3)){
			j = 0;
			while(j < 8){
				board[i][j].set_occupied(1);
				board[i][j].set_piece_color(0);
				board[i][j].set_king(0);
				j += 2;
			}
		}
		else if(((i % 2) != 0) && (i > 3)){
			j = 0;
			while(j < 8){
				board[i][j].set_occupied(1);
				board[i][j].set_piece_color(1);
				board[i][j].set_king(0);
				j += 2;
			}
		} 
		i++;
	}
	p1_pieces = 12;
	p2_pieces = 12;
}

string Checkers::get_user_move()const{
	string temp = "";
	if(next_mover() == HUMAN){
		display_message("Player 1: \n");
	}
	else{
		display_message("Player 2: \n");
	}
	temp = game::get_user_move();
	return temp;
}
void Checkers::restart(){
	int i = 0, j;
	while(i < 8){
		if(((i % 2) == 0) && (i < 4)){
			j = 1;
			while(j < 8){
				board[i][j].set_occupied(1);
				board[i][j].set_piece_color(0);
				board[i][j].set_king(0);
				j += 2;
			}
		}
		else if(((i % 2) == 0) && (i > 4)){
			j = 1;
			while(j < 8){
				board[i][j].set_occupied(1);
				board[i][j].set_piece_color(1);
				board[i][j].set_king(0);
				j += 2;
			}
		}
		else if(((i % 2) != 0) && (i < 3)){
			j = 0;
			while(j < 8){
				board[i][j].set_occupied(1);
				board[i][j].set_piece_color(0);
				board[i][j].set_king(0);
				j += 2;
			}
		}
		else if(((i % 2) != 0) && (i > 3)){
			j = 0;
			while(j < 8){
				board[i][j].set_occupied(1);
				board[i][j].set_piece_color(1);
				board[i][j].set_king(0);
				j += 2;
			}
		} 
		i++;
	}
	p1_pieces = 12;
	p2_pieces = 12;
	display_message("Enter moves in the form of 4 charactars with no spaces \n");
	display_message("first row and column of spot you want to move from, then row and column of spot you want to move to \n");
	game::restart();
}

bool Checkers::is_legal(const std::string& move) const{
	int prev_row, prev_column, next_row, next_column;
	prev_row = (int)(toupper(move[0]) - 'A');
	prev_column = (int)(move[1] - '1');
	next_row = (int)(toupper(move[2]) - 'A');
	next_column = (int)(move[3] - '1');
	int row_diff = next_row - prev_row, column_diff = next_column - prev_column;

	if((next_row > 7) || (next_row < 0) || (next_column > 7) || (next_column < 0) || (prev_row > 7) || (prev_row < 0) || (prev_column > 7) || (prev_column < 0)){
		return false;
	}
	if(board[next_row][next_column].isoccupied()){
		return false;
	}
	if(!board[prev_row][prev_column].isoccupied()){
		return false;
	}
	if(next_mover() == HUMAN){
		if(board[prev_row][prev_column].isred()){
			return false;
		}
	}

	else{
		if(!board[prev_row][prev_column].isred()){
			return false;
		}
	}

	if((row_diff == 0) || (column_diff == 0)){
		return false;
	}

	if(!board[prev_row][prev_column].isking()){
		if((next_mover() == HUMAN) && (row_diff < 0)){
			return false;
		}
		else if((next_mover() == COMPUTER) && (row_diff > 0)){
			return false;
		}
	}
	
	if((row_diff != column_diff) && ((-1 * row_diff) != column_diff)){
		return false;
	}

	if((row_diff > 2) || (row_diff < -2) || (column_diff > 2) || (column_diff < -2)){
		return false;
	}
	
	if(((row_diff == 2) || (row_diff == -2) || (column_diff == 2) || (column_diff == -2)) && (!isjump(move))){
		return false;
	}
	
	int i = 0, j = 0;
	bool jump = false;
	while(i < 8){
		j = 0;
		while(j < 8){
			if(jump_available(i, j)){
				jump = true;
			}
			j++;
		}
		i++;
	}
	if(jump && !isjump(move)){
		return false;
	}
	return true;
}

void Checkers::make_move(const std::string& move){
	int prev_row, prev_column, next_row, next_column;
	prev_row = (int)(toupper(move[0]) - 'A');
	prev_column = (int)(move[1] - '1');
	next_row = (int)(toupper(move[2]) - 'A');
	next_column = (int)(move[3] - '1');
	int column_diff = next_column - prev_column, row_diff = next_row - prev_row;
	bool jump = false;
	if(isjump(move)){
		if(row_diff > 0){
			if(column_diff > 0){
				board[prev_row + 1][prev_column + 1].set_occupied(0);
				board[prev_row + 1][prev_column + 1].set_king(0);
			}
			else{
				board[prev_row + 1][prev_column - 1].set_occupied(0);
				board[prev_row + 1][prev_column - 1].set_king(0);
			}
		}
		else{
			if(column_diff > 0){
				board[prev_row - 1][prev_column + 1].set_occupied(0);
				board[prev_row - 1][prev_column + 1].set_king(0);
			}
			else{
				board[prev_row - 1][prev_column - 1].set_occupied(0);
				board[prev_row - 1][prev_column - 1].set_king(0);
			}
		}
		jump = true;
		if(next_mover() == HUMAN){
			p2_pieces--;
		}
		else{
			p1_pieces--;
		}
	}
	board[next_row][next_column].set_occupied(1);
	if(board[prev_row][prev_column].isred()){
		board[next_row][next_column].set_piece_color(1);
	}
	else{
		board[next_row][next_column].set_piece_color(0);
	}
	if(board[prev_row][prev_column].isking()){
		board[next_row][next_column].set_king(1);
	}
	else{
		board[next_row][next_column].set_king(0);
	}
	board[prev_row][prev_column].set_occupied(0);
	board[prev_row][prev_column].set_king(0);
	if(multi_jump(move) && jump){
		return;
	}
	if(next_mover() == HUMAN){
		if(next_row == 7){
			board[next_row][next_column].set_king(1);
		}
	}
	else{
		if(next_row == 0){
			board[next_row][next_column].set_king(1);
		}
	}
	game::make_move(move);
}

void Checkers::display_status()const{
	int i = 0, j = 0, k = 0, row = 7, column = 7;
	char ch;
	cout << B_WHITE << "   8       7       6       5       4       3       2       1    " << endl;
	while(i < 8){
		if((i % 2) == 0){
			k = 0;
			while(k < 4){
				column = 7;
				j = 0;
				while(j < 4){
					cout << B_BLACK << "        ";
					column--;
					cout << B_RED;
					if(board[row][column].isoccupied() && (k == 2)){
						if(board[row][column].isred()){
							if(!board[row][column].isking()){
								cout << WHITE << "   @    ";
							}
							else{
								cout << WHITE << "   K    ";
							}	
						}
						else{
							if(!board[row][column].isking()){
								cout << BLUE << "   @    ";
							}
							else{
								cout << BLUE << "   K    ";
							}
						}
					}
					else{
						cout << "        ";
					}
					column--;
					j++;
				}
				if(k == 2){
					ch = 'A' + row;
					cout << B_WHITE << BLACK << ch;
				}
				cout << B_WHITE << endl;
				k++;
			}
		}
		else{
			k = 0;
			while(k < 4){
				column = 7;
				j = 0;
				while(j < 4){
					cout << B_RED;
					if(board[row][column].isoccupied() && (k == 2)){
						if(board[row][column].isred()){
							if(!board[row][column].isking()){
								cout << WHITE << "   @    ";
							}
							else{
								cout << WHITE << "   K    ";
							}	
						}
						else{
							if(!board[row][column].isking()){
								cout << BLUE << "   @    ";
							}
							else{
								cout << BLUE << "   K    ";
							}
						}
					}
					else{
						cout << "        ";
					}
					column--;
					cout << B_BLACK << "        ";
					column--;
					j++;
				}
				if(k == 2){
					ch = 'A' + row;
					cout << B_WHITE << BLACK << ch;
				}
				cout << B_WHITE << endl;
				k++;
			}
		}
		row--;
		i++;	
	}
	cout << BLACK;
	return;
}

bool Checkers::jump_available(int i, int j)const{
	if(!board[i][j].isoccupied()){
		return false;
	}
	if(next_mover() == HUMAN){
		if(board[i][j].isred()){
			return false;	
		}
		else{
			if(board[i][j].isking()){
				if((i + 1 < 8) && (j + 1 < 8) && (board[i + 1][j + 1].isoccupied()) && (board[i + 1][j + 1].isred())){
					if((i + 2 < 8) && (j + 2 < 8) && (!board[i + 2][j + 2].isoccupied())){
						return true;
					}
				}
				if((i + 1 < 8) && (j - 1 > -1) && (board[i + 1][j - 1].isoccupied()) && (board[i + 1][j - 1].isred())){
					if((i + 2 < 8) && (j - 2 > -1) && (!board[i + 2][j - 2].isoccupied())){
						return true;
					}
				}
				if((i - 1 > -1) && (j + 1 < 8) && (board[i - 1][j + 1].isoccupied()) && (board[i - 1][j + 1].isred())){
					if((i - 2 > -1) && (j + 2 < 8) && (!board[i - 2][j + 2].isoccupied())){
						return true;
					} 
				}
				if((i - 1 > -1) && (j - 1 > -1) && (board[i - 1][j - 1].isoccupied()) && (board[i - 1][j - 1].isred())){
					if((i - 2 > -1) && (j - 2 > -1) && (!board[i - 2][j - 2].isoccupied())){
						return true;
					} 
				}
			}
			else{
				if((i + 1 < 8) && (j + 1 < 8) && (board[i + 1][j + 1].isoccupied()) && (board[i + 1][j + 1].isred())){
					if((i + 2 < 8) && (j + 2 < 8) && (!board[i + 2][j + 2].isoccupied())){
						return true;
					}
				}
				if((i + 1 < 8) && (j - 1 > -1) && (board[i + 1][j - 1].isoccupied()) && (board[i + 1][j - 1].isred())){
					if((i + 2 < 8) && (j - 2 > -1) && (!board[i + 2][j - 2].isoccupied())){
						return true;
					}
				}
			}
		}
	}
	else{
		if(!board[i][j].isred()){
			return false;
		}
		else{
			if(board[i][j].isking()){
					if((i + 1 < 8) && (j + 1 < 8) && (board[i + 1][j + 1].isoccupied()) && (!board[i + 1][j + 1].isred())){
						if((i + 2 < 8) && (j + 2 < 8) && (!board[i + 2][j + 2].isoccupied())){
							return true;
						}
					}
					if((i + 1 < 8) && (j - 1 > -1) && (board[i + 1][j - 1].isoccupied()) && (!board[i + 1][j - 1].isred())){
						if((i + 2 < 8) && (j - 2 > -1) && (!board[i + 2][j - 2].isoccupied())){
							return true;
						}
					}
					if((i - 1 > -1) && (j + 1 < 8) && (board[i - 1][j + 1].isoccupied()) && (!board[i - 1][j + 1].isred())){
						if((i - 2 > -1) && (j + 2 < 8) && (!board[i - 2][j + 2].isoccupied())){
							return true;
						} 
					}
					if((i - 1 > -1) && (j - 1 > -1) && (board[i - 1][j - 1].isoccupied()) && (!board[i - 1][j - 1].isred())){
						if((i - 2 > -1) && (j - 2 > -1) && (!board[i - 2][j - 2].isoccupied())){
							return true;
						} 
					}
			}		
			else{
				if((i - 1 > -1) && (j + 1 < 8) && (board[i - 1][j + 1].isoccupied()) && (!board[i - 1][j + 1].isred())){
					if((i - 2 > -1) && (j + 2 < 8) && (!board[i - 2][j + 2].isoccupied())){
						return true;
					}
				}
				if((i - 1 > -1) && (j - 1 > -1) && (board[i - 1][j - 1].isoccupied()) && (!board[i - 1][j - 1].isred())){
					if((i - 2 > -1) && (j - 2 > -1) && (!board[i - 2][j - 2].isoccupied())){
						return true;
					}
				}
			}
		}
	}
	return false;
}

bool Checkers::isjump(string move)const{
	int prev_row, prev_column, next_row, next_column;
	prev_row = (int)(toupper(move[0]) - 'A');
	prev_column = (int)(move[1] - '1');
	next_row = (int)(toupper(move[2]) - 'A');
	next_column = (int)(move[3] - '1');
	int column_diff = next_column - prev_column, row_diff = next_row - prev_row;
	if(!board[prev_row][prev_column].isoccupied()){
		return false;
	}
	if((row_diff != 2) && (row_diff != -2)){
		return false;
	}
	else if((column_diff != 2) && (column_diff != -2)){
			return false;
	}
	
	if(row_diff > 0){
		if(column_diff > 0){
			if(!board[prev_row + 1][prev_column + 1].isoccupied()){
				return false;
			}
			if(board[prev_row][prev_column].isred()){
				if(board[prev_row + 1][prev_column + 1].isred()){
					return false;
				}
			}
			else{
				if(!board[prev_row + 1][prev_column + 1].isred()){
					return false;
				}
			}
		}
		else{
			if(!board[prev_row + 1][prev_column - 1].isoccupied()){
				return false;
			}
			if(board[prev_row][prev_column].isred()){
				if(board[prev_row + 1][prev_column - 1].isred()){
					return false;
				}
			}
			else{
				if(!board[prev_row + 1][prev_column - 1].isred()){
					return false;
				}
			}
		}
	}
	else{
		if(column_diff > 0){
			if(!board[prev_row - 1][prev_column + 1].isoccupied()){
				return false;
			}
			if(board[prev_row][prev_column].isred()){
				if(board[prev_row - 1][prev_column + 1].isred()){
					return false;
				}
			}
			else{
				if(!board[prev_row - 1][prev_column + 1].isred()){
					return false;
				}
			}
		}
		else{
			if(!board[prev_row - 1][prev_column - 1].isoccupied()){
				return false;
			}
			if(board[prev_row][prev_column].isred()){
				if(board[prev_row - 1][prev_column - 1].isred()){
					return false;
				}
			}
			else{
				if(!board[prev_row - 1][prev_column - 1].isred()){
					return false;
				}
			}
		}
	}
	return true;
}

bool Checkers::multi_jump(string move)const{
	int prev_row, prev_column, next_row, next_column;
	prev_row = (int)(toupper(move[0]) - 'A');
	prev_column = (int)(move[1] - '1');
	next_row = (int)(toupper(move[2]) - 'A');
	next_column = (int)(move[3] - '1');
	return jump_available(next_row, next_column);
}

bool Checkers::is_game_over()const{
	if((p1_pieces == 0) || (p2_pieces == 0)){
		return true;
	}
	else{
		string tmp = "aaaa";
		int i = 0, j = 0;
		while(i < 8){
			j = 0;
			while(j < 8){
				tmp[0] = i + 'A';
				tmp[1] = j + '1';
				tmp[2] = (i + 1) + 'A';
				tmp[3] = (j + 1) + '1';
				if(is_legal(tmp)){
					return false;
				}
				tmp[2] = (i + 1) + 'A';
				tmp[3] = (j - 1) + '1';
				if(is_legal(tmp)){
					return false;
				}
				tmp[2] = (i - 1) + 'A';
				tmp[3] = (j + 1) + '1';
				if(is_legal(tmp)){
					return false;
				}
				tmp[2] = (i - 1) + 'A';
				tmp[3] = (j - 1) + '1';
				if(is_legal(tmp)){
					return false;
				}
				tmp[2] = (i + 2) + 'A';
				tmp[3] = (j + 2) + '1';
				if(is_legal(tmp)){
					return false;
				}
				tmp[2] = (i + 2) + 'A';
				tmp[3] = (j - 2) + '1';
				if(is_legal(tmp)){
					return false;
				}
				tmp[2] = (i - 2) + 'A';
				tmp[3] = (j + 2) + '1';
				if(is_legal(tmp)){
					return false;
				}
				tmp[2] = (i - 2) + 'A';
				tmp[3] = (j - 2) + '1';
				if(is_legal(tmp)){
					return false;
				}
				j++;
			}
			i++;
		}
	}
	return true;
}

game* Checkers::clone( ) const{
	return new Checkers(*this);
}

void Checkers::compute_moves(queue<string>& moves) const{
	int i = 0, j = 0;
	string tmp = "aaaa";
	char ch1, ch2, ch3, ch4;
	while(i < 8){
		j = 0;
		while(j < 8){
			tmp[0] = i + 'A';
			tmp[1] = j + '1';
			tmp[2] = (i + 1) + 'A';
			tmp[3] = (j + 1) + '1';
			if(is_legal(tmp)){
				moves.push(tmp);
			}
			tmp[2] = (i + 1) + 'A';
			tmp[3] = (j - 1) + '1';
			if(is_legal(tmp)){
				moves.push(tmp);
			}
			tmp[2] = (i - 1) + 'A';
			tmp[3] = (j + 1) + '1';
			if(is_legal(tmp)){
				moves.push(tmp);
			}
			tmp[2] = (i - 1) + 'A';
			tmp[3] = (j - 1) + '1';
			if(is_legal(tmp)){
				moves.push(tmp);
			}
			tmp[2] = (i + 2) + 'A';
			tmp[3] = (j + 2) + '1';
			if(is_legal(tmp)){
				moves.push(tmp);
			}
			tmp[2] = (i + 2) + 'A';
			tmp[3] = (j - 2) + '1';
			if(is_legal(tmp)){
				moves.push(tmp);
			}
			tmp[2] = (i - 2) + 'A';
			tmp[3] = (j + 2) + '1';
			if(is_legal(tmp)){
				moves.push(tmp);
			}
			tmp[2] = (i - 2) + 'A';
			tmp[3] = (j - 2) + '1';
			if(is_legal(tmp)){
				moves.push(tmp);
			}
			j++;	
		}
		i++;
	}
}

int Checkers::evaluate()const{
	int i = 0, j = 0;
	int value = 0;
	while(i < 8){
		j = 0;
		while(j < 8){
			if(board[i][j].isoccupied()){
				if(board[i][j].isred()){
					if(board[i][j].isking()){
						value += 2;
					}
					else{
						value++;
					}
				}
				else{
					if(board[i][j].isking()){
						value -= 2;
					}
					else{
						value--;
					}
				}
			}
			j++;
		}
		i++;
	}
}
}
