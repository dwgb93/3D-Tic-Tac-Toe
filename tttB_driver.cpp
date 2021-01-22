///////////////////////////////////////////////////////////////////////////////////////////////////
// Name: Dylan Bates
// Date: March 18, 2013
// 3D Tic Tac Toe
// Summary: Plays a 3D tic tac toe game between two players or a player and the computer.
////////////////////////////////////////////////////////////////////////////////////////////////////





#include <string>
#include "TTTBoard3.h"
#include "player.h"
//include two other header files containing information about board and players

// Almost identical to 2D play a game. Prompt player for moves, check to see if they are a valid move.
// Lather, rinse and repeat.



//Play a game function plays a game with the specified parameters
bool playAGame(player *P[], int size, bool twoPlayer, bool compFirst)
{
	//X, Y, Z are player's chosen coordinates
	//playerNo is player's number
	int X = -1, Y = -1, Z = -1, playerNo;
	//These keep track of the last move for the computer
	int XLast = 0, YLast = 0, ZLast = 0;
	
	bool stillPlay;
	//Y or N to keep playing. Who goes first, player or computer?
	char keepPlaying;
	
	//Variable for the board. This is used everywhere
	TTTBoard3 ttt (size); //3D TicTacToe
	//Draws the board and all the current pieces
	ttt.drawBoard(size);


	//Here we go!!!
	//Game play, up to N^3 moves
	for (int i = 0; i < size * size * size; i++)
	{
		//Convoulted algorithm to make sure it displays the correct name for all cases
		//But it WORKS!
		//Two players is east
		if (twoPlayer == true)
		{
			playerNo = i % 2;
		}
		else if (compFirst == true)
		{	
			//With one player, if the computer went first, then the first player's name should be computer (duh)
			if (i % 2 == 0)
			{
				playerNo = 2; // OR 2
			}
			else
			{
				//Every other move is the player, though
				playerNo = 0;
			}
		}
		//Final case means 1 player but computer went 2nd
		else if (i % 2 == 0)
		{
				playerNo = 0;
		}
		else
		{
			//Comp still has every other move
			playerNo = 2;
		}

		//Prints players name
		std::cout << "Player ";
		P[playerNo]->printName();
		std::cout << ":" << std::endl << std::endl; //Player1 or 2
		//Gets moves (of either player or copmuter)
		P[playerNo]->getMoves(size, playerNo, X, Y, Z, XLast, YLast, ZLast, &ttt);
			
		//Refreshes the board.			
		ttt.drawBoard(size); //Draws the board
		//If there's a winner
		if (ttt.isWinner(size) != -1)
			//Then exit the loop
			break;
	}

	//Play again
	std::cout << "Would you like to play again?" << std::endl;
	do
	{
		std::cin >> keepPlaying;
		switch (keepPlaying)
		{	
			case 'y':
				stillPlay = true;
				break;
			case 'Y':
				stillPlay = true;
				break;
			case 'n':
				stillPlay = false;
				break;
			case 'N':
				stillPlay = false;
				break;
			default:
				std::cout << "Please type Y or N." << std::endl;
		}
	} while (keepPlaying != 'y' && keepPlaying != 'Y' && keepPlaying != 'n' && keepPlaying != 'N');
	//Keeps asking them until they give me a good answer
	return stillPlay;
	//Returns whether or not to keep playing
}



void main()
{
	//Variables for gameplay
	//Name of two players
	std::string name1, name2;
	//Size (usually 3) is size of board. NumPlayer indicates whether it'll be a 1 player (computer) game or two player (versus) game
	int numPlayers, size;
	//Who goes first, computer or player?
	char firstAnswer;
	//Booleans to keep track of how many players and who goes first. (and whether or not to play another game)
	bool twoPlayer = false,  compFirst = false, keepPlaying = false;

	//Declaration of player class variables. One for each possible player + one for computer.
	player* P[3];

	//If they want to play again, it loops
	do
	{
		//Greeting; gets size
		std::cout << "Hello and Welcome to my Text Tic Tac Toe game!" << std::endl << std::endl;

		do
		{
			std::cout << "Please type the size of the board (3, 4, 5): ";
			std::cin >> size;

			if (size > 5 || size < 3)
			{
				std::cout << "That is not an appropriate size!" << std::endl;
			}
		} while (size > 5 || size < 3);
		//We don't want any 2x2x2 or 6x6x6 boards.

		
	

		//How many players?
		std::cout << "Do you want 1 or 2 player?" << std::endl;
		do
		{
			std::cin >> numPlayers;
			if (numPlayers < 1 || numPlayers > 2)
			{
				std::cout << "That is an invalid number of players." << std::endl;
				std::cout << "Please enter 1 or 2." << std::endl;
			}
		} while (numPlayers < 1 || numPlayers > 2);
		//If NO computer
		if (numPlayers == 2)
			twoPlayer = true;

		//Gets P1 name
		std::cout << "Please enter the name of Player 1: ";
		std::cin >> name1;
		P[0] = new player (name1);

		if (twoPlayer == true)
		{
			//Gets P2 name
			std::cout << std::endl << "Please enter the name of Player 2: ";
			std::cin >> name2;
			P[1] = new player (name2);
		}
		else
		{
			//Creates computer player of computer class
			computer* C = new computer ("Computer");
			P[2] = C;
			//Makes computer 2nd player

			//Only asks this for 1 player games. For 2 player games, P1 obviously goes first.
			std::cout << "Who should go first?" << std::endl;
			std::cout << "Enter a P (for Player) or C (for Computer): ";
			do
			{
				std::cin >> firstAnswer;
				switch (firstAnswer)
				{	
					case 'p':
						compFirst = false;
						break;
					case 'P':
						compFirst = false;
						break;
					case 'c':
						compFirst = true;
						break;
					case 'C':
						compFirst = true;
						break;
					default:
						std::cout << "Please type P or C." << std::endl;
				}
			} while (firstAnswer != 'P' && firstAnswer != 'p' && firstAnswer != 'c' && firstAnswer != 'C');
		}

		//Plays a game AND after it's done returns whether to keep playing or not.
		keepPlaying = playAGame(P, size, twoPlayer, compFirst);

	} while (keepPlaying == true);
	//Keeps looping while they want to play again.
	//Because of where the loop starts, they have to specify what type of game again
}
