/******************************************************************
    This is the header file for the checkers class, derived from the game class.
		Eric Hahn			April 12, 2016
********************************************************************/
#ifndef CHECKERS_H
#define CHECKERS_H
#include "game.h"
#include "space.h"

namespace main_savitch_14{
class Checkers:public game{
	public:
		Checkers();//constructor
		void display_status()const;//displays checker board
		void restart();//resets game
		void make_move(const std::string& move);//makes move given by "move"
		bool is_legal(const std::string& move) const;//checks if "move" is a legal move
		bool is_game_over()const;//returns true if either players pieces are 0
		std::string get_user_move()const;
		game* clone( ) const;
		void compute_moves(std::queue<std::string>& moves) const;
		int evaluate()const;
	private:
		bool jump_available(int i, int j)const;//returns true if a jump is available from board[i][j]
		bool multi_jump(std::string move)const;//returns true if another jump is available from users move
		bool isjump(std::string move)const;//returns true if the users move is a jump
		Space board[8][8];
		int p1_pieces;
		int p2_pieces;
};
}
#endif
