#include "colors.h"
#include "connect4.h"
#include <iostream>
#include <ctype.h>
#include <stdio.h>

namespace main_savitch_14
{
int connectFour :: evaluate() const
{
int redCounter = 0;
int yellowCounter = 0;
 
for(int i = 0; i < 6; ++i)
    {
        for(int j = 0; j < 7; ++j)
        {

	}
    }
}

/* COMPUTE MOVES */
/*void connectFour::compute_moves(std::queue<std::string>& moves)
{
    char tmp;
    
    for(char j = 'a' ;j <= 'g' ;j++)
    {
 
            tmp = j;
            if(is_legal(tmp))
            {
                moves.push(tmp);}
             }
    }
    
    
}
*/
void connectFour :: restart()
{


    for(int i = 0; i < 6; ++i)
    {
        for(int j = 0; j < 7; ++j)
        {
            theBoard[i][j].change_empty();
        }
    }

    std::cout<<" ------------ "<<std::endl;


    std::cout<<"  CONNECT ";

       std::cout<<RED<<"4   "<<WHITE<<std::endl;


    std::cout<<" ------------ "<<std::endl;
}
void connectFour :: display_status()
{

    if(catcher  == false ) // if someone wins i made a bool expression that wouldnt show the string below
    {
        std::cout <<RED<< "  A   B   C   D   E   F   G "<<WHITE; // got this one from the Internet because it looks nice
    }

    std::cout<<std::endl;
    std::cout<<"  +-----------------------+ "<<std::endl;
    for(int i = 0; i < 6; ++i)
    {
 
        std::cout<<" ";
        for(int j = 0; j < 7; ++j)
        {
            if(theBoard[i][j].is_red())
            {
               
                std::cout<<RED<<" O  "<<WHITE;
            }
            else if(theBoard[i][j].is_yellow())
            {
                
                std::cout<<YELLOW<<" O  "<<WHITE;
            }
            else
            {
          
                std::cout<<BLUE<<" |  "<<WHITE;
            }

        }

        std::cout<<std::endl;
    }

	std::cout<<"  +-----------------------+ "<<std::endl;
    if(catcher == false) // this is for better display
    {
        // better for user friendly work
        std::cout<<"Move Number : ";
        std::cout<<total_moves + 1  <<std::endl;
    }

}
bool connectFour :: is_legal(const std::string &move)
{
    int column = toupper(move[0]- 'A');// d is equal to 100 and capital A is 65 and the result is 35
    //int row = toupper(move[1]-'1'); //is equal to 52 and 1 is equal to 49 so 52-49 so the result is
    column = column - 32;

    if(move[0] < 'A' || move[0] > 'g')
    {
        return false;
    }
    if(move[0] > 'G' && move[0] < 'a')
    {
        return false;
    }
    if(isdigit(move[0]) || move == "" || move[0] == ' ' || move[1] ==' ' )
    {
        return false;
    }
    if(checkDown(column)==true)
    {
        return true;
    }
    return false;
}
void connectFour::make_move(const std::string &move)
{
    int column = toupper(move[0]- 'A');// d is equal to 100 and capital A is 65 and the result is 35
    column = column - 32;
    int captureRow = 0;
    if(isupper(move[0]))
    {
        column = tolower(move[0])- 'A';
        column = column - 32;
    }
    if(total_moves % 2 == 0)
    {
        while(theBoard[captureRow+1][column].is_nothing() && captureRow < 5)
        {
            captureRow++;
        }

        theBoard[captureRow][column].change_yellow();
    }
    if(total_moves % 2 == 1)
    {
        while(theBoard[captureRow+1][column].is_nothing() && captureRow < 5)
        {
            captureRow++;
        }
        theBoard[captureRow][column].change_red();
    }
    move_counter();

}
bool connectFour :: checkDown(int column)
{
    int row = 0;
    if(theBoard[row][column].is_nothing() && row < 5)
    {
        return true;
    }
    return false;
}

bool connectFour :: connectFourleft(int tmpRow, int tmpCol )
{

    int counter = 0;
    int counterForRed = 0;

    int tmpColForRed = tmpCol;

    while(theBoard[tmpRow][tmpCol].is_yellow() && tmpCol >= 0)
    {

        counter ++;
        tmpCol--;
    }
    if(counter >= 4)
    {

        std::cout<<std::endl;
        std::cout<<"   ***** YELLOW WINS *****      ";
        return true;
    }

    while(theBoard[tmpRow][tmpColForRed].is_red()&& tmpColForRed >= 0)
    {
        counterForRed ++;
        tmpColForRed--;
    }
    if(counterForRed >= 4)
    {

        std::cout<<std::endl;
        std::cout<<"   ***** RED WINS *****      ";
        return true;
    }
    return false;
}
bool connectFour :: connectFourDown(int tmpRow, int tmpCol)
{

    int counter = 0;
    int counterForRed = 0;

    int tmpRowForRed = tmpRow;

    while(theBoard[tmpRow][tmpCol].is_yellow() && tmpRow < 6)
    {
        counter ++;
        tmpRow++;
    }
    if(counter >= 4)
    {

        std::cout<<std::endl;
        std::cout<<"   ***** YELLOW WINS *****      ";
        return true;
    }

    while(theBoard[tmpRowForRed][tmpCol].is_red() && tmpRowForRed < 6)
    {
        counterForRed ++;
        tmpRowForRed++;
    }
    if(counterForRed >= 4)
    {

        std::cout<<std::endl;
        std::cout<<"    ***** RED WINS *****      ";
        return true;
    }
    return false;
}
bool connectFour :: connectFourUp(int tmpRow, int tmpCol)
{

    int counter = 0;
    int counterForRed = 0;

    int tmpRowForRed = tmpRow;

    while(theBoard[tmpRow][tmpCol].is_yellow() && tmpRow >= 0)
    {
        counter ++;
        tmpRow--;
    }
    if(counter >= 4)
    {
 
        std::cout<<std::endl;
        std::cout<<"   ***** YELLOW WINS *****      ";
        return true;
    }

    while(theBoard[tmpRowForRed][tmpCol].is_red() && tmpRowForRed >= 0)
    {
        counterForRed ++;
        tmpRowForRed--;
    }
    if(counterForRed >= 4)
    {

        std::cout<<std::endl;
        std::cout<<"    ***** RED WINS *****      ";
        return true;
    }
    return false;
}
bool connectFour :: connectFourUpRight(int tmpRow, int tmpCol)
{

    int counter = 0;
    int counterForRed = 0;

    int tmpRowForRed = tmpRow;
    int tmpColForRed = tmpCol;

    while(theBoard[tmpRow][tmpCol].is_yellow() && (tmpRow >= 0 && tmpCol < 7))
    {
        counter ++;
        tmpRow--;
        tmpCol++;
    }
    if(counter >= 4)
    {
        std::cout<<std::endl;
        std::cout<<"HI";
        std::cout<<"   ***** YELLOW WINS *****      ";
        return true;
    }

    while(theBoard[tmpRowForRed][tmpColForRed].is_red() && (tmpRowForRed >= 0 && tmpColForRed < 7 ))
    {
        counterForRed ++;
        tmpRowForRed--;
        tmpColForRed++;
    }
    if(counterForRed >= 4)
    {
        std::cout<<std::endl;
        std::cout<<"    ***** RED WINS *****      ";
        return true;
    }
    return false;
}

bool connectFour:: connectFourUpLeft(int tmpRow, int tmpCol)
{
    int counter = 0;
    int counterForRed = 0;

    int tmpRowForRed = tmpRow;
    int tmpColForRed = tmpCol;

    while(theBoard[tmpRow][tmpCol].is_yellow() && (tmpRow >= 0 && tmpCol >= 0))
    {
        counter ++;
        tmpRow--;
        tmpCol--;
    }
    if(counter >= 4)
    {
        std::cout<<std::endl;
        std::cout<<"   ***** YELLOW WINS *****      ";
        return true;
    }

    while(theBoard[tmpRowForRed][tmpColForRed].is_red() && (tmpRowForRed >= 0 && tmpColForRed >= 0))
    {
        counterForRed ++;
        tmpRowForRed--;
        tmpColForRed--;
    }
    if(counterForRed >= 4)
    {
        std::cout<<std::endl;
        std::cout<<"    ***** RED WINS *****      ";
        return true;
    }
    return false;
}

bool connectFour :: connectFourDownRight(int tmpRow, int tmpCol)
{
    int counter = 0;
    int counterForRed = 0;

    int tmpRowForRed = tmpRow;
    int tmpColForRed = tmpCol;

    while(theBoard[tmpRow][tmpCol].is_yellow() && (tmpRow < 6  && tmpCol < 7))
    {
        counter ++;
        tmpRow++;
        tmpCol++;
    }
    if(counter >= 4)
    {

        std::cout<<std::endl;
        std::cout<<"   ***** YELLOW WINS *****      ";
        return true;
    }

    while(theBoard[tmpRowForRed][tmpColForRed].is_red() && (tmpRowForRed < 6 && tmpColForRed < 7))
    {
        counterForRed ++;
        tmpRowForRed++;
        tmpColForRed++;
    }
    if(counterForRed >= 4)
    {

        std::cout<<std::endl;
        std::cout<<"    ***** RED WINS *****      ";
        return true;
    }
    return false;
}
bool connectFour :: connectFourDownLeft(int tmpRow, int tmpCol)
{
    int counter = 0;
    int counterForRed = 0;

    int tmpRowForRed = tmpRow;
    int tmpColForRed = tmpCol;

    while(theBoard[tmpRow][tmpCol].is_yellow() && (tmpRow < 6 && tmpCol >=0))
    {
        counter ++;
        tmpRow++;
        tmpCol--;
    }
    if(counter >= 4)
    {

        std::cout<<std::endl;
        std::cout<<"   ***** YELLOW WINS *****      ";
        return true;
    }

    while(theBoard[tmpRowForRed][tmpColForRed].is_red() && (tmpRowForRed < 6 && tmpColForRed >=0 ))
    {
        counterForRed ++;
        tmpRowForRed++;
        tmpColForRed--;
    }
    if(counterForRed >= 4)
    {

        std::cout<<std::endl;
        std::cout<<"    ***** RED WINS *****      ";
        return true;
    }
    return false;
}
bool connectFour :: connectFourRight(int tmpRow, int tmpCol)
{
    int counter = 0;
    int counterForRed = 0;

    int tmpColForRed = tmpCol;

    while(theBoard[tmpRow][tmpCol].is_yellow() && tmpCol < 7)
    {

        counter ++;
        tmpCol++;
    }
    if(counter >= 4)
    {
        std::cout<<std::endl;
        std::cout<<"   ***** YELLOW WINS *****      ";
        return true;
    }

    while(theBoard[tmpRow][tmpColForRed].is_red() && tmpColForRed < 7)
    {
        counterForRed ++;
        tmpColForRed++;
    }
    if(counterForRed >= 4)
    {

        std::cout<<std::endl;
        std::cout<<"    ***** RED WINS *****      ";
        return true;
    }
    return false;

}

void connectFour :: scoreBoard()
{


}
bool connectFour :: is_game_over()
{
    int tmpRow;
    int tmpCol;

    for(int i = 0; i < 6; ++i)
    {
        for(int j = 0; j < 7; ++j)
        {
            if(theBoard[i][j].is_yellow())
            {
                tmpRow = i;
                tmpCol = j;
                if(connectFourleft(tmpRow,tmpCol)== true)
                {
                    catcher  = true;
                    return true;
                }
                if(connectFourRight(tmpRow,tmpCol)== true)
                {
                    catcher  = true;
                    return true;
                }
                if(connectFourDown(tmpRow,tmpCol)== true)
                {
                    catcher  = true;
                    return true;
                }
                if(connectFourUp(tmpRow, tmpCol)== true)
                {
                    catcher  = true;
                    return true;
                }
                if(connectFourUpRight(tmpRow, tmpCol)== true)
                {
                    catcher  = true;
                    return true;
                }
                if(connectFourDownLeft(tmpRow, tmpCol)== true)
                {
                    catcher  = true;
                    return true;
                }
                if(connectFourUpLeft(tmpRow, tmpCol) == true)
                {
                    catcher  = true;
                    return true;
                }
                if(connectFourDownRight(tmpRow, tmpCol) == true)
                {
                    catcher  = true;
                    return true;
                }

            }
        }
    }
    int tmpRowForRed;
    int tmpColForRed;
    for(int i = 0; i < 6; ++i)
    {
        for(int j = 0; j < 7; ++j)
        {
            if(theBoard[i][j].is_red())
            {
                tmpRowForRed = i;
                tmpColForRed = j;
                if(connectFourleft(tmpRowForRed,tmpColForRed) == true)
                {
                    catcher  = true;
                    return true;
                }
                if(connectFourRight(tmpRowForRed,tmpColForRed) == true)
                {
                    catcher  = true;
                    return true;
                }
                if(connectFourDown(tmpRowForRed,tmpColForRed) == true)
                {
                    catcher  = true;
                    return true;
                }
                if(connectFourUp(tmpRowForRed,tmpColForRed) == true)
                {
                    catcher  = true;
                    return true;
                }
                if(connectFourUpRight(tmpRowForRed,tmpColForRed) == true)
                {
                    catcher  = true;
                    return true;
                }
                if(connectFourDownLeft(tmpRowForRed, tmpColForRed) == true)
                {
                    catcher  = true;
                    return true;
                }
                if(connectFourUpLeft(tmpRowForRed, tmpColForRed) == true)
                {
                    catcher  = true;
                    return true;
                }
                if(connectFourDownRight(tmpRowForRed, tmpColForRed) == true)
                {
                    catcher  = true;
                    return true;
                }
            }
        }
    }
    int redCounter = 0;
    int yellowCounter = 0;

    for(int b = 0; b < 6; ++b)
    {
        for(int k = 0; k < 7; ++k)
        {
            if(theBoard[b][k].is_red())
            {
                redCounter++;
            }
            if(theBoard[b][k].is_yellow())
            {
                yellowCounter++;
            }
        }
    }
 
    if((redCounter + yellowCounter) == 42)
    {


        std::cout<<"    ***** A DRAW  *****      ";
        catcher = true;
        return true;

    }

    return false;
}

}
