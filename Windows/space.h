/******************************************************************
    This is the header file for the space class, which is used in the checkers class.
		Eric Hahn			April 12, 2016
********************************************************************/
#ifndef SPACE_H
#define SPACE_H
#include <string>
class Space{
	public:
		Space(){occupied = 0; piece_color = 0; king = 0;}//constructor
		void set_occupied(bool tmp){occupied = tmp;}//sets if occupied
		void set_piece_color(int tmp){piece_color = tmp;}//sets piece color
		void set_king(bool tmp){king = tmp;}//sets if king
		bool isoccupied()const{return occupied;}//returns true if occupied
		bool isred()const{return (piece_color == 1);}//returns 1 if red
		bool isblack()const{return (piece_color == 0);}//returns 0 if black
		bool isking()const{return king;}//return true if king

	private:
		bool occupied;
		int piece_color;//0 for black, 1 for red
		bool king;
};
#endif
