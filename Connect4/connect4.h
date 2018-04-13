#include "game.h"
#include "piece.h"

namespace main_savitch_14{
class connectFour: public game
{
public:

    connectFour(){ total_moves = 0; catcher = false;}
    void restart();
    void display_status();
    void make_move(const std::string &move);
    bool is_legal(const std::string &move);
    bool is_game_over();
    int evaluate() const;

    bool checkDown(int column); //where you place a piece and checks down like when you are playing the game

    //These are the directions in which you can get connect four
    bool connectFourleft(int tmpRow, int tmpCol); //Left
    bool connectFourRight(int tmpRow, int tmpCol); //Right
    bool connectFourDown(int tmpRow, int tmpCol); //Down
    bool connectFourUp(int tmpRow, int tmpCol); // Up

    bool connectFourUpRight(int tmpRow, int tmpCol); // UpRight
    bool connectFourDownLeft(int tmpRow, int tmpCol); // DownLeft

    bool connectFourUpLeft(int tmpRow, int tmpCol); // UpLeft
    bool connectFourDownRight(int tmpRow, int tmpCol);// DownRight

	 
    
    void scoreBoard();
    //This is where is stops

    virtual game* clone()const{}
    virtual void compute_moves(std::queue<std::string>& moves) const{}
    //virtual bool is_legal(const std::string& move){}
    //virtual bool is_game_over() const{}
    //virtual void display_status() const{}
    //virtual int evaluate() const{}
    void move_counter(){total_moves++;}// for white and black

private:
    bool catcher;
    int total_moves;
    piece theBoard[6][7];
};
}

