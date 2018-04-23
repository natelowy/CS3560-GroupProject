//***********************************************************
//
//  File:     colors.h
//
//  Author:   Matthew Beldyk
//  Email:    mb245002@ohiou.edu
//
//  Usage:    I created this file to house some names string
//            constants with escape codes for colors in them
//            this makes it much easier for me to do colors.
//            I can still use the codes if I want, but this
//            works too.  try the statement:
//            cout<<BLUE<<"I like cookies"<<endl;
//
//		  You may use this whereever you want, but if you
//		  make any large improvements or whatever, I am
//		  curious, so email 'em my way, please.
//
//***********************************************************
//
//  all credit given to Matthew Beldyk for writing this file
//  he gave me permission to try out in my programs
//  just wanted to use to make everything look nice
//
//***********************************************************

#ifndef COLORS_H
#define COLORS_H

#include <string>
using namespace std;

const string BLINK     = "\x1bSC[5m";          //don't use this your
					   //professor will probibly
					   //beat you to death if
					   //you do feel the need to
					   //use blink!!!
const string BOLD      = "\x1b[1m";

const string RESET     = "\x1b[0m";
const string MENU       = "\x1b[44;37m";

const string BLACK      = "\x1b[30m";
const string RED        = "\x1b[31m";
const string GREEN      = "\x1b[32m";
const string YELLOW     = "\x1b[33m";
const string BLUE       = "\x1b[34m";
const string MAGENTA    = "\x1b[35m";
const string CYAN       = "\x1b[36m";
const string BR_CYAN      = "\x1b[1;36m";
const string WHITE      = "\x1b[1;37m";
//I've actually modified this to be bright white, since it shows up more clearly
//const string WHITE      = "\x1b[1;37m";

const string B_BLACK    = "\x1b[40m";
const string B_BR_BLACK = "\x1b[100m";	//Added for colorblindness settings
const string B_RED      = "\x1b[41m";
const string B_GREEN   = "\x1b[42m";
const string B_YELLOW  = "\x1b[43m";
const string B_BLUE    = "\x1b[44m";
const string B_MAGENTA = "\x1b[45m";
const string B_CYAN    = "\x1b[46m";
const string B_WHITE   = "\x1b[47m";

#endif //COLORS_H

