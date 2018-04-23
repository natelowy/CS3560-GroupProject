#include <iostream>
#include <string>
#include "game.h"

namespace main_savitch_14{

    class Space{
    public:
    	bool is_occupied;
		bool is_white;
		bool is_black;
		void flip();
    };

    class Othello:public game{
    public:
        int pass;
    	Othello();
    	Othello(int r, int c, std::string c1, std::string c2, std::string ctext);
    	std::string get_color(std::string color, bool tile);
    	bool is_consecutive(const std::string& move, int charval, int row)const;
    	virtual game* clone( ) const;
        // Compute all the moves that the next player can make:
    	virtual void compute_moves(std::queue<std::string>& moves) const;
    	// Display the status of the current game:
    	virtual void display_status( ) const;
    	// Evaluate a board position:
	// NOTE: positive values are good for the computer.
    	virtual int evaluate( ) const;
    	// Return true if the current game is finished:
    	virtual bool is_game_over( ) const;
    	// Return true if the given move is legal for the next player:
    	virtual bool is_legal(const std::string& move) const;
    	virtual void make_move(const std::string& move);
        virtual std::string get_user_move( ) const;
        virtual game::who winning( ) const;

	private:
		int rows, columns;		//So that custom sizes may be used
		std::string cl1, cl2, cltext;
		Space board[18][18];	//Allocating 18x18 as max size option
	};
}