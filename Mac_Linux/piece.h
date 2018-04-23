
class piece
{
public:
    piece(){red = false; yellow = false;} // constructor because I think c++ doesnt set bools to false by default
    bool is_red(){if (red){return true;} else{return false;}};
    bool is_yellow(){if (yellow){return true;} else{return false;}};
    bool is_nothing(){if(red == false && yellow == false){return true;}else{return false;}};
    bool is_piece(){if (red == true || yellow == true){return true;}}


    void change_yellow(){yellow = true; red= false;};
    void change_red(){red = true; yellow = false;};
    void change_empty(){red = false; yellow = false;};

    //void colorChanger()

    //void display(); // im not even sure a display function is needed but we will see
    //void flip(){if(white == true ){white = false; black = true;} else {white = true; black = false;}}

private:
    bool red;
    bool yellow;
    //bool empty; // a empty is not needed
};

