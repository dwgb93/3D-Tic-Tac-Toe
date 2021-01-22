#ifndef TTTBOARD3_H_
#define TTTBOARD3_H_

#include <iostream>

//-- tttBclass
//summary: tHis class is for a tic tac toe board
//It contains everything you need to keep the game going. Probably.

//Look at all the comments!!!



class TTTBoard3
{
	private:
		//int N;
		//Didn't need it

		// 3D array containing a -1 if a spot on the tic-tac-toe board is empty;
		// a 0 if "X" controls a spot and a 1 if "O" conrtols a spot.
		int ***currentState;

	public:
		// This will set the size (N = 3)  and allocate space for currentState
		// (if you want to, you can pass in a size I did. BOOM!)
		TTTBoard3(int N);
		// Destructor will delete currentState (free allocated space)
		~TTTBoard3();
		// isWinner: Determine if there is a winner.
		// Return an integer. -1 if no winner, 0 if X wins and 1 if O wins
		int isWinner (int size);
		// checkMove: Check to see if the slot i,j,k is full. If it is,
		// pass back an error (1), if not, pass back 0. Yeah, it's backwards. Deal with it.
		bool checkMove (int i, int j, int k);
		//Updates currentState to reflec the most recent move made by playerNumber
		void makeMove (int i, int j, int k, int playerNumber);
		// displayBoard: display the board. And the pieces on it.
		void drawBoard(int size);
		// resetBoard: change each part of currentState back to -1 so 
		// that someone can play without rerunning the code
		void reset(int N);
		//Allows someone to access currentState from outside of the code.
		//Is probably not necessary
		int getCurrent(int X, int Y, int Z);
};

#endif

