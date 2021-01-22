//Header for Player class (and computer class

//If Player is not defined then DEFINE IT!
#ifndef PLAYER_H_
#define PLAYER_H_
//Need to include the header for TTT so I can see which moves are open
#include "TTTBoard3.h"
#include <iostream>
#include <string>


//-- Player class. Swag
//summary: This class contains all of the elements dealing with the players and computer
//The player stuff mostly deals with their names and getting their moves.
//Computer stuff involves figuring out which moves to go to.

class player
{
	private:
		//The name of the player
		std::string name;
	public:
		// This is the constructor. We are going to have to assign a name in here.
		player(std::string nameIn);
		~player(); // Destrictor doesn't really need to do anything.


		// Ask for moves from player
		// If it was NOT a valid move, then ask the player to choose a different location.
		//OR gets moves from computer
		// after confirming validity, makes the moves
		void getMoves(int size, int playerNo, int &X, int &Y, int &Z, int &XLast, int &YLast, int &ZLast, TTTBoard3 *ttt);
		//Gets the users move, and rejects if it's out of range
		//Loops until they are all good
		int getMove(int size);
		// Return the players name
		void printName();
		

};


//Is this supposed to have its own ifndef stuff?
//Computer class inherits stuff from player class (name)
class computer : public player
{
	private:
		//Nada
	public:
		//Constructor doesn't do much
		computer::computer(std::string nameIn);
		//Neither does destructor
		computer::~computer();
		//void decideMove(int size, int &X, int &Y, int &Z, int XLast, int YLast, int ZLast, TTTBoard3 *ttt);
		// I thought about including this, but it was so much easier to just have a classess function
		//It goes through the hierarchy of moves to win
};

#endif