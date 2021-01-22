#include "player.h"

// This function checks to see if the computer can win on the next move
bool CanWin (int N, int &X, int &Y, int &Z, TTTBoard3 *ttt);

// This function checks to see if the computer can block on the next move
bool CanBlock (int N, int &X, int &Y, int &Z, TTTBoard3 *ttt);

// This function contains the heierarchy of moves to try to win (Win, block, centre, fork, corner, etc)
void decideMove(int size, int &X, int &Y, int &Z, int XLast, int YLast, int ZLast, TTTBoard3 *ttt);

// The function that takes the centre piece
bool TakeCentre(int size, TTTBoard3 *ttt);

// Takes an open corner
int TakeCorner(int size, TTTBoard3 *ttt);

// Checks if the computer can fork, or continues a previous fork
bool CanComputerFork(int size, int &X, int &Y, int &Z, int XLast, int YLast, int ZLast, TTTBoard3 *ttt);

// Takes any open square if the previous doesn't turn up anything. Should almost never be used.
void TakeRandom(int size, int &X, int &Y, int &Z, TTTBoard3 *ttt);

// Take a guess...
void player::printName()
{
	std::cout << name; //Prints players name
}

// Gets players name
player::player(std::string nameIn)
{
	name = nameIn;
}

// Takes any open square if all other strategies fail
void TakeRandom(int size, int &X, int &Y, int &Z, TTTBoard3 *ttt)
{
	// Loops through all possible coordinates
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			for (int k = 0; k < size; k++)
			{
				//Checks to see if abailable
				if (!ttt->checkMove(i, j, k))
				{
					//Assigns values
					X = i;
					Y = j;
					Z = k;
				}
			}
		}
	}
	
};

//This function goes through the list of possible moves, making (hopefully) ideal decisions.
void decideMove(int size, int &X, int &Y, int &Z, int XLast, int YLast, int ZLast, TTTBoard3 *ttt)
{
	//if Computer can win, takes the win
	if (CanWin(size, X, Y, Z, ttt))
	{
		//Nothing here because X, Y, and Z are changed in the function.
	}
	// If it can block, it takes that
	else if (CanBlock(size, X, Y, Z, ttt))
	{
		//Nothing here because X, Y, and Z are changed in the function.
	}
	// If the centre is open, take it (most powerful position in the game
	else if (TakeCentre(size, ttt))
	{
		X = size/2;
		Y = size/2;
		Z = size/2;
		//I did this one first and didn't bother changing it. 
	}
	// If it's the first time through, it places a piece that will not allow the opponent to get two in a row
	// 2nd time through, it puts a piece that will create a fork
	else if (CanComputerFork(size, X, Y, Z, XLast, YLast,  ZLast, ttt))
	{
		//Nothing here because X, Y, and Z are changed in the function.
	}
	// If nothing else, take a corner
	else if (TakeCorner(size, ttt) == 1)
	{
		X = 0;
		Y = 0;
		Z = 0;
	}

	// Or this corner
	else if (TakeCorner(size, ttt) == 2)
	{
		X = 0;
		Y = size - 1;
		Z = 0;
	}
	// Or this corner
	else if (TakeCorner(size, ttt) == 3)
	{
		X = 0;
		Y = 0;
		Z = size - 1;
	}
	// Or this corner
	else if (TakeCorner(size, ttt) == 4)
	{
		X = size - 1;
		Y = 0;
		Z = 0;
	}
	// Or this corner
	else if (TakeCorner(size, ttt) == 5)
	{
		X = size - 1;
		Y = size - 1;
		Z = 0;
	}
	// Or this corner
	else if (TakeCorner(size, ttt) == 6)
	{
		X = size - 1;
		Y = 0;
		Z = size - 1;
	}
	// Or this corner
	else if (TakeCorner(size, ttt) == 7)
	{
		X = 0;
		Y = size - 1;
		Z = size - 1;
	}
	// Or this corner
	else if (TakeCorner(size, ttt) == 8)
	{
		X = size - 1;
		Y = size - 1;
		Z = size - 1;
	}
	// If all the corners are taken, someone should have won. But they didn't, so take the next open space.
	else
	{
		TakeRandom (size, X, Y, Z, ttt);
	}
};

// This function (called from main) gets the computers move (by using decideMove) or the players move by inputting X, Y, and Z individually
void player::getMoves(int size, int playerNo, int &X, int &Y, int &Z, int &XLast, int &YLast, int &ZLast, TTTBoard3 *ttt)
{
	//PlayerNo = 2 for the computer
	if (playerNo == 2)
	{
		//Call functions
		decideMove(size, X, Y, Z, XLast, YLast, ZLast, ttt);
		system("pause");
		//Lets the user wait until they are ready. Otherwise the computer would move at (what appears to be) the exact same time as the user

	}
	//For the player
	else
	{
		//Loop until they get it right
		do
		{
			//Self explanitory
			std::cout << std::endl << "Please type the X coordinate of the square you would like to make a move in: ";
			X = getMove(size); // Just makes sure it's in the appropriate range
			std::cout << std::endl << "Please type the Y coordinate of the square you would like to make a move in: ";
			Y = getMove(size);
			std::cout << std::endl << "Please type the Z coordinate of the square you would like to make a move in: ";
			Z = getMove(size);
			//Checks to see if valid
			if (ttt->checkMove(X, Y, Z))
			{
				std::cout << "That is an invalid move." << std::endl;
			}
		} while (ttt->checkMove(X, Y, Z));
		//Assigns coordinates for computer function
		XLast = X;
		YLast = Y;
		ZLast = Z;
	}
	// Changes the game board to reflect new moves
	ttt->makeMove(X, Y, Z, playerNo);
	
}

// Function that ensures values of coordinates are in the appropriate range.
int player::getMove (int size)
{
	int coor;
	//Loops until they get it right
	do
	{
		std::cin >> coor;
		//In the right range
		if (coor < 0 || coor >= size)
		{
			std::cout << "That is not a valid move!" << std::endl;
			std::cout << std::endl << "Please type the coordinate of the square you would like to make a move in: ";
		}
	} while (coor < 0 || coor >= size);
	return coor;
}

//Destructor
player::~player()
{
};

//Computer constructor.
computer::computer(std::string nameIn) : player(nameIn)
{
};

//Computer destructor
computer::~computer()
{
};


//Function that checks if the computer can win
bool CanWin (int N, int &X, int &Y, int &Z, TTTBoard3 *ttt)
{
	//Used to count the number of Xs and Os in a single row, column or diagonal
	int Os, Xs;
	
	//This code is very similar to the code to check for winning (I'm just checking if it CAN win now)
	// I'm only going to comment how it works for the first one, so yeah.
	//---Traditional 2D win (k is 3rd)-----------------------------------

	// Check "2D" wins when the height (k) is fixed.
	for(int k = 0; k < N; k++)
	{ // Loop over each height
		// Your 2D "isWinner" code

		// This has row as "fast" index and column as "slow" index
		for(int j = 0; j < N; j++)
		{ //Column number
			//Resets O and X
			Os = 0;
			Xs = 0;
			for(int i = 0; i < N; i++)
			{
				//Loops through possibilities
				if(ttt->getCurrent(i, j, k) == 1)
				{
					//If it's an O, Os is incremented
					Os++;
				}
				else if (ttt->getCurrent(i, j, k) == 0)
				{
					//If it's an X, Xs is incremented
					Xs++;
				}
				//It's empty
				else
				{
					//Set coordinates equal to empty space
					X = i;
					Y = j;
					Z = k;
				}
			}
			//If the row is full of Os and there are 0 Xs, then there is one  empty space.
			if(Os == N - 1 && Xs == 0)
			{
				//Returns that space. (Okay, it returns saying it's true, but X, Y, and Z, are passed by reference, and already changed)
				return 1;
			}
		}

		//Exact same thing except for rows instead of columns (or vice versa)
		// This has column as "fast" index and row as "slow" index
		for(int j = 0; j < N; j++)
		{ //Row number
			//Same as above
			Os = 0;
			Xs = 0;
			for(int i = 0; i < N; i++)
			{
				if(ttt->getCurrent(j, i, k) == 1)
				{
					Os++;
				}
				else if (ttt->getCurrent(j, i, k) == 0)
				{
					Xs++;
				}
				else
				{
					X = j;
					Y = i;
					Z = k;
				}
			}
			if(Os == N - 1 && Xs == 0)
			{
				return 1;
			}
		}
		// Same except for diagonals. You know the deal
		// Diagonals (first (0,0) -> (1,1) -> (2,2) )
		Os = 0;
		Xs = 0;
		for(int i = 0; i < N; i++)
		{
			if(ttt->getCurrent(i, i, k) == 1)
			{
				Os++;
			}
			else if (ttt->getCurrent(i, i, k) == 0)
			{
				Xs++;
			}
			else
			{
				X = i;
				Y = i;
				Z = k;
			}
		}
		if(Os == N - 1 && Xs == 0)
		{
			return 1;
		}
	

		
		// Diagonals (first (0,2) -> (1,1) -> (2,0) )
		Os = 0;
		Xs = 0;
		for(int i = 0; i < N; i++)
		{
			if(ttt->getCurrent(i, N-(i+1), k) == 1)
			{
				Os++;
			}
			else if (ttt->getCurrent(i, N-(i+1), k) == 0)
			{
				Xs++;
			}
			else
			{
				X = i;
				Y = N-(i+1);
				Z = k;
			}
		}
		if(Os == N - 1 && Xs == 0)
		{
			return 1;
		}
	}
	//----END Traditional 2D win-------------------------------

	//The same stuff goes on. I'm going to stop commenting now.

	//---Traditional 2D win (k is 2nd)-----------------------------------
	// Check "2D" wins when the height (k) is fixed.
	for(int k = 0; k < N; k++)
	{ // Loop over each height
		// Your 2D "isWinner" code

		// This has row as "fast" index and column as "slow" index
		for(int j = 0; j < N; j++)
		{ //Column number
			Os = 0;
			Xs = 0;
			for(int i = 0; i < N; i++)
			{
				if(ttt->getCurrent(i, k, j) == 1)
				{
					Os++;
				}
				else if (ttt->getCurrent(i, k, j) == 0)
				{
					Xs++;
				}
				else
				{
					X = i;
					Y = k;
					Z = j;
				}
			}
			if(Os == N - 1 && Xs == 0)
			{
				return 1;
			}
		}

	
		// This has column as "fast" index and row as "slow" index
		for(int j = 0; j < N; j++)
		{ //Row number
			Os = 0;
			Xs = 0;
			for(int i = 0; i < N; i++)
			{
				if(ttt->getCurrent(j, k, i) == 1)
				{
					Os++;
				}
				else if (ttt->getCurrent(j, k, i) == 0)
				{
					Xs++;
				}
				else
				{
					X = j;
					Y = k;
					Z = i;
				}
			}
			if(Os == N - 1 && Xs == 0)
			{
				return 1;
			}
		}

		// Diagonals (first (0,0) -> (1,1) -> (2,2) )
		Os = 0;
		Xs = 0;
		for(int i = 0; i < N; i++)
		{
			if(ttt->getCurrent(i, k, i) == 1)
			{
				Os++;
			}
			else if (ttt->getCurrent(i, k, i) == 0)
			{
				Xs++;
			}
			else
			{
				X = i;
				Y = k;
				Z = i;
			}
		}
		if(Os == N - 1 && Xs == 0)
		{
			return 1;
		}

		
		// Diagonals (first (0,2) -> (1,1) -> (2,0) )
		Os = 0;
		Xs = 0;
		for(int i = 0; i < N; i++)
		{
			if(ttt->getCurrent(i, k, N-(i+1)) == 1)
			{
				Os++;
			}
			else if (ttt->getCurrent(i, k, N-(i+1)) == 0)
			{
				Xs++;
			}
			else
			{
				X = i;
				Y = k;
				Z = N-(i+1);
			}
		}
		if(Os == N - 1 && Xs == 0)
		{
			return 1;
		}
	}
	//----END Traditional 2D win-------------------------------


	//---Traditional 2D win (k is 1st)-----------------------------------
	// Check "2D" wins when the height (k) is fixed.
	for(int k = 0; k < N; k++)
	{ // Loop over each height
		// Your 2D "isWinner" code

		// This has row as "fast" index and column as "slow" index
		for(int j = 0; j < N; j++)
		{ //Column number
			Os = 0;
			Xs = 0;
			for(int i = 0; i < N; i++)
			{
				if(ttt->getCurrent(k, i, j) == 1)
				{
					Os++;
				}
				else if (ttt->getCurrent(k, i, j) == 0)
				{
					Xs++;
				}
				else
				{
					X = k;
					Y = i;
					Z = j;
				}
			}
			if(Os == N - 1 && Xs == 0)
			{
				return 1;
			}
		}

	
		// This has column as "fast" index and row as "slow" index
		for(int j = 0; j < N; j++)
		{ //Row number
			Os = 0;
			Xs = 0;
			for(int i = 0; i < N; i++)
			{
				if(ttt->getCurrent(k, j, i) == 1)
				{
					Os++;
				}
				else if (ttt->getCurrent(k, j, i) == 0)
				{
					Xs++;
				}
				else
				{
					X = k;
					Y = j;
					Z = i;
				}
			}
			if(Os == N - 1 && Xs == 0)
			{
				return 1;
			}
		}

		// Diagonals (first (0,0) -> (1,1) -> (2,2) )
		Os = 0;
		Xs = 0;
		for(int i = 0; i < N; i++)
		{
			if(ttt->getCurrent(k, i, i) == 1)
			{
				Os++;
			}
			else if (ttt->getCurrent(k, i, i) == 0)
			{
				Xs++;
			}
			else
			{
				X = k;
				Y = i;
				Z = i;
			}
		}
		if(Os == N - 1 && Xs == 0)
		{
			return 1;
		}

		
		// Diagonals (first (0,2) -> (1,1) -> (2,0) )
		Os = 0;
		Xs = 0;
		for(int i = 0; i < N; i++)
		{
			if(ttt->getCurrent(k, i, N-(i+1)) == 1)
			{
				Os++;
			}
			else if (ttt->getCurrent(k, i, N-(i+1)) == 0)
			{
				Xs++;
			}
			else
			{
				X = k;
				Y = i;
				Z = N-(i+1);
			}
		}
		if(Os == N - 1 && Xs == 0)
		{
			return 1;
		}

	}
	//----END Traditional 2D win-------------------------------

	//Okay I lied. It does the exact same stuff for specific 3D diagonals, though
	// Check 3D diagonals
	// (0,0,0) (1,1,1) (2,2,2)
	Os = 0;
	Xs = 0;
	for(int i = 0; i < N; i++)
	{
		if(ttt->getCurrent(i, i, i) == 1)
		{
			Os++;
		}
		else if (ttt->getCurrent(i, i, i) == 0)
		{
			Xs++;
		}
		else
		{
			X = i;
			Y = i;
			Z = i;
		}
	}
	if(Os == N - 1 && Xs == 0)
	{
		return 1;
	}

	// (2,0,0) (1,1,1) (0,2,2)
	Os = 0;
	Xs = 0;
	for(int i = 0; i < N; i++)
	{
		if(ttt->getCurrent(N-(i+1), i, i) == 1)
		{
			Os++;
		}
		else if (ttt->getCurrent(N-(i+1), i, i) == 0)
		{
			Xs++;
		}
		else
		{
			X = N-(i+1);
			Y = i;
			Z = i;
		}
	}
	if(Os == N - 1 && Xs == 0)
	{
		return 1;
	}

	// (0,2,0) (1,1,1) (2,0,2)
	Os = 0;
	Xs = 0;
	for(int i = 0; i < N; i++)
	{
		if(ttt->getCurrent(i, N-(i+1), i) == 1)
		{
			Os++;
		}
		else if (ttt->getCurrent(i, N-(i+1), i) == 0)
		{
			Xs++;
		}
		else
		{
			X = i;
			Y = N-(i+1);
			Z = i;
		}
	}
	if(Os == N - 1 && Xs == 0)
	{
		return 1;
	}

	// (2,2,0) (1,1,1) (0,0,2)
	Os = 0;
	Xs = 0;
	for(int i = 0; i < N; i++)
	{
		if(ttt->getCurrent(i, i, N-(i+1)) == 1)
		{
			Os++;
		}
		else if (ttt->getCurrent(i, i, N-(i+1)) == 0)
		{
			Xs++;
		}
		else
		{
			X = i;
			Y = i;
			Z = N-(i+1);
		}
	}
	if(Os == N - 1 && Xs == 0)
	{
		return 1;
	}

	// End checking
	// Return 0 (no win) if NONE of the above are winners
	return(0);
}

//This function is nearly IDENTICAL to CanWin, exept for a few things.
//It checks to see if the computer can BLOCK the players potential win.
// If there is any confusion in code, see comments for CanWin. The code is essentially the same.
bool CanBlock (int N, int &X, int &Y, int &Z, TTTBoard3 *ttt)
{
	int Os, Xs;


	//---Traditional 2D win (k is 3rd)-----------------------------------

	// Check "2D" wins when the height (k) is fixed.
	for(int k = 0; k < N; k++)
	{ // Loop over each height
		// Your 2D "isWinner" code

		// This has row as "fast" index and column as "slow" index
		for(int j = 0; j < N; j++)
		{ //Column number
			Os = 0;
			Xs = 0;
			for(int i = 0; i < N; i++)
			{
				if(ttt->getCurrent(i, j, k) == 1)
				{
					Os++;
				}
				else if (ttt->getCurrent(i, j, k) == 0)
				{
					Xs++;
				}
				else
				{
					X = i;
					Y = j;
					Z = k;
				}
			}
			// This is the ONLY difference. It returns positive if the row is full of Xs (player's letter) and devoid of Os (computer's letter)
			if(Xs == N - 1 && Os == 0)
			{
				return 1;
			}
		}

	
		// This has column as "fast" index and row as "slow" index
		for(int j = 0; j < N; j++)
		{ //Row number
			Os = 0;
			Xs = 0;
			for(int i = 0; i < N; i++)
			{
				if(ttt->getCurrent(j, i, k) == 1)
				{
					Os++;
				}
				else if (ttt->getCurrent(j, i, k) == 0)
				{
					Xs++;
				}
				else
				{
					X = j;
					Y = i;
					Z = k;
				}
			}
			if(Xs == N - 1 && Os == 0)
			{
				return 1;
			}
		}

		// Diagonals (first (0,0) -> (1,1) -> (2,2) )
		Os = 0;
		Xs = 0;
		for(int i = 0; i < N; i++)
		{
			if(ttt->getCurrent(i, i, k) == 1)
			{
				Os++;
			}
			else if (ttt->getCurrent(i, i, k) == 0)
			{
				Xs++;
			}
			else
			{
				X = i;
				Y = i;
				Z = k;
			}
		}
		if(Xs == N - 1 && Os == 0)
		{
			return 1;
		}
	

		
		// Diagonals (first (0,2) -> (1,1) -> (2,0) )
		Os = 0;
		Xs = 0;
		for(int i = 0; i < N; i++)
		{
			if(ttt->getCurrent(i, N-(i+1), k) == 1)
			{
				Os++;
			}
			else if (ttt->getCurrent(i, N-(i+1), k) == 0)
			{
				Xs++;
			}
			else
			{
				X = i;
				Y = N-(i+1);
				Z = k;
			}
		}
		if(Xs == N - 1 && Os == 0)
		{
			return 1;
		}
	}
	//----END Traditional 2D win-------------------------------


	//---Traditional 2D win (k is 2nd)-----------------------------------
	// Check "2D" wins when the height (k) is fixed.
	for(int k = 0; k < N; k++)
	{ // Loop over each height
		// Your 2D "isWinner" code

		// This has row as "fast" index and column as "slow" index
		for(int j = 0; j < N; j++)
		{ //Column number
			Os = 0;
			Xs = 0;
			for(int i = 0; i < N; i++)
			{
				if(ttt->getCurrent(i, k, j) == 1)
				{
					Os++;
				}
				else if (ttt->getCurrent(i, k, j) == 0)
				{
					Xs++;
				}
				else
				{
					X = i;
					Y = k;
					Z = j;
				}
			}
			if(Xs == N - 1 && Os == 0)
			{
				return 1;
			}
		}

	
		// This has column as "fast" index and row as "slow" index
		for(int j = 0; j < N; j++)
		{ //Row number
			Os = 0;
			Xs = 0;
			for(int i = 0; i < N; i++)
			{
				if(ttt->getCurrent(j, k, i) == 1)
				{
					Os++;
				}
				else if (ttt->getCurrent(j, k, i) == 0)
				{
					Xs++;
				}
				else
				{
					X = j;
					Y = k;
					Z = i;
				}
			}
			if(Xs == N - 1 && Os == 0)
			{
				return 1;
			}
		}

		// Diagonals (first (0,0) -> (1,1) -> (2,2) )
		Os = 0;
		Xs = 0;
		for(int i = 0; i < N; i++)
		{
			if(ttt->getCurrent(i, k, i) == 1)
			{
				Os++;
			}
			else if (ttt->getCurrent(i, k, i) == 0)
			{
				Xs++;
			}
			else
			{
				X = i;
				Y = k;
				Z = i;
			}
		}
		if(Xs == N - 1 && Os == 0)
		{
			return 1;
		}

		
		// Diagonals (first (0,2) -> (1,1) -> (2,0) )
		Os = 0;
		Xs = 0;
		for(int i = 0; i < N; i++)
		{
			if(ttt->getCurrent(i, k, N-(i+1)) == 1)
			{
				Os++;
			}
			else if (ttt->getCurrent(i, k, N-(i+1)) == 0)
			{
				Xs++;
			}
			else
			{
				X = i;
				Y = k;
				Z = N-(i+1);
			}
		}
		if(Xs == N - 1 && Os == 0)
		{
			return 1;
		}
	}
	//----END Traditional 2D win-------------------------------


	//---Traditional 2D win (k is 1st)-----------------------------------
	// Check "2D" wins when the height (k) is fixed.
	for(int k = 0; k < N; k++)
	{ // Loop over each height
		// Your 2D "isWinner" code

		// This has row as "fast" index and column as "slow" index
		for(int j = 0; j < N; j++)
		{ //Column number
			Os = 0;
			Xs = 0;
			for(int i = 0; i < N; i++)
			{
				if(ttt->getCurrent(k, i, j) == 1)
				{
					Os++;
				}
				else if (ttt->getCurrent(k, i, j) == 0)
				{
					Xs++;
				}
				else
				{
					X = k;
					Y = i;
					Z = j;
				}
			}
			if(Xs == N - 1 && Os == 0)
			{
				return 1;
			}
		}

	
		// This has column as "fast" index and row as "slow" index
		for(int j = 0; j < N; j++)
		{ //Row number
			Os = 0;
			Xs = 0;
			for(int i = 0; i < N; i++)
			{
				if(ttt->getCurrent(k, j, i) == 1)
				{
					Os++;
				}
				else if (ttt->getCurrent(k, j, i) == 0)
				{
					Xs++;
				}
				else
				{
					X = k;
					Y = j;
					Z = i;
				}
			}
			if(Xs == N - 1 && Os == 0)
			{
				return 1;
			}
		}

		// Diagonals (first (0,0) -> (1,1) -> (2,2) )
		Os = 0;
		Xs = 0;
		for(int i = 0; i < N; i++)
		{
			if(ttt->getCurrent(k, i, i) == 1)
			{
				Os++;
			}
			else if (ttt->getCurrent(k, i, i) == 0)
			{
				Xs++;
			}
			else
			{
				X = k;
				Y = i;
				Z = i;
			}
		}
		if(Xs == N - 1 && Os == 0)
		{
			return 1;
		}

		
		// Diagonals (first (0,2) -> (1,1) -> (2,0) )
		Os = 0;
		Xs = 0;
		for(int i = 0; i < N; i++)
		{
			if(ttt->getCurrent(k, i, N-(i+1)) == 1)
			{
				Os++;
			}
			else if (ttt->getCurrent(k, i, N-(i+1)) == 0)
			{
				Xs++;
			}
			else
			{
				X = k;
				Y = i;
				Z = N-(i+1);
			}
		}
		if(Xs == N - 1 && Os == 0)
		{
			return 1;
		}

	}
	//----END Traditional 2D win-------------------------------

	// Check 3D diagonals
	// (0,0,0) (1,1,1) (2,2,2)
	Os = 0;
	Xs = 0;
	for(int i = 0; i < N; i++)
	{
		if(ttt->getCurrent(i, i, i) == 1)
		{
			Os++;
		}
		else if (ttt->getCurrent(i, i, i) == 0)
		{
			Xs++;
		}
		else
		{
			X = i;
			Y = i;
			Z = i;
		}
	}
	if(Xs == N - 1 && Os == 0)
	{
		return 1;
	}

	// (2,0,0) (1,1,1) (0,2,2)
	Os = 0;
	Xs = 0;
	for(int i = 0; i < N; i++)
	{
		if(ttt->getCurrent(N-(i+1), i, i) == 1)
		{
			Os++;
		}
		else if (ttt->getCurrent(N-(i+1), i, i) == 0)
		{
			Xs++;
		}
		else
		{
			X = N-(i+1);
			Y = i;
			Z = i;
		}
	}
	if(Xs == N - 1 && Os == 0)
	{
		return 1;
	}

	// (0,2,0) (1,1,1) (2,0,2)
	Os = 0;
	Xs = 0;
	for(int i = 0; i < N; i++)
	{
		if(ttt->getCurrent(i, N-(i+1), i) == 1)
		{
			Os++;
		}
		else if (ttt->getCurrent(i, N-(i+1), i) == 0)
		{
			Xs++;
		}
		else
		{
			X = i;
			Y = N-(i+1);
			Z = i;
		}
	}
	if(Xs == N - 1 && Os == 0)
	{
		return 1;
	}

	// (2,2,0) (1,1,1) (0,0,2)
	Os = 0;
	Xs = 0;
	for(int i = 0; i < N; i++)
	{
		if(ttt->getCurrent(i, i, N-(i+1)) == 1)
		{
			Os++;
		}
		else if (ttt->getCurrent(i, i, N-(i+1)) == 0)
		{
			Xs++;
		}
		else
		{
			X = i;
			Y = i;
			Z = N-(i+1);
		}
	}
	if(Xs == N - 1 && Os == 0)
	{
		return 1;
	}

	// End checking
	// Return 0 (no block) if NONE of the above can block
	return(0);

	//Phew, that was long!
}

//Checks to see if the computer can create a fork in order to force a win.

//The first time through, it places it's move so the players does NOT end up in the same row/column/diagonal
//The second time through, it places a piece that can "fork" and force a win on the next move
bool CanComputerFork(int size, int &X, int &Y, int &Z, int XLast, int YLast, int ZLast, TTTBoard3 *ttt)
{
	//Checks if it's a corner piece
	if ((XLast == size - 1 || XLast == 0) && (YLast == size - 1 || YLast == 0) && (ZLast == size - 1 || ZLast == 0))
	{
		// it's in a top back left corner
		// take an edge adjacent to it
		//This forces the player to go on the other side of the board to block.
		if (XLast == 0 && YLast == size - 1 && ZLast == size - 1)
		{
			//Checks to see if this spot is free.
			if (!ttt->checkMove(XLast, YLast-1, ZLast))
			{
				X = XLast;
				Y = YLast-1;
				Z = ZLast;
				//Takes the spot and returns.
				return 1;
			}
			else if (!ttt->checkMove(XLast+1, YLast, ZLast))
			{
				//How about this spot?
				X = XLast+1;
				Y = YLast;
				Z = ZLast;
				//Same thing
				return 1;
			}
			else if (!ttt->checkMove(XLast+1, YLast-1, ZLast))
			{
				// You know by now. I'm not going to comment any more of these.
				X = XLast+1;
				Y = YLast-1;
				Z = ZLast;
				return 1;
			}
			else if (!ttt->checkMove(XLast, YLast, ZLast-1))
			{
				X = XLast;
				Y = YLast;
				Z = ZLast-1;
				return 1;
			}
			else if (!ttt->checkMove(XLast, YLast-1, ZLast-1))
			{
				X = XLast;
				Y = YLast-1;
				Z = ZLast-1;
				return 1;
			}
			else if (!ttt->checkMove(XLast+1, YLast, ZLast-1))
			{
				X = XLast+1;
				Y = YLast;
				Z = ZLast-1;
				return 1;
			}
			else if (!ttt->checkMove(XLast, YLast-1, ZLast-2))
			{
				X = XLast;
				Y = YLast-1;
				Z = ZLast-2;
				return 1;
			}
			else if (!ttt->checkMove(XLast+1, YLast, ZLast-2))
			{
				X = XLast+1;
				Y = YLast;
				Z = ZLast-2;
				return 1;
			}
			//Those are all the spots I'm willing to take.
		}
		///top right back corner
		else if (XLast == size - 1 && YLast == size - 1 && ZLast == size - 1)
		{
			//Same stuff as above
			if (!ttt->checkMove(XLast-1, YLast, ZLast))
			{
				X = XLast-1;
				Y = YLast;
				Z = ZLast;
				return 1;
			}
			else if (!ttt->checkMove(XLast-1, YLast-1, ZLast))
			{
				X = XLast-1;
				Y = YLast-1;
				Z = ZLast;
				return 1;
			}
			else if (!ttt->checkMove(XLast, YLast-1, ZLast))
			{
				X = XLast;
				Y = YLast-1;
				Z = ZLast;
				return 1;
			}
			else if (!ttt->checkMove(XLast, YLast, ZLast-1))
			{
				X = XLast;
				Y = YLast;
				Z = ZLast-1;
				return 1;
			}
			else if (!ttt->checkMove(XLast, YLast-1, ZLast-1))
			{
				X = XLast;
				Y = YLast-1;
				Z = ZLast-1;
				return 1;
			}
			else if (!ttt->checkMove(XLast-1, YLast, ZLast-1))
			{
				X = XLast-1;
				Y = YLast;
				Z = ZLast-1;
				return 1;
			}
			else if (!ttt->checkMove(XLast, YLast-1, ZLast-2))
			{
				X = XLast;
				Y = YLast-1;
				Z = ZLast-2;
				return 1;
			}
			else if (!ttt->checkMove(XLast-1, YLast, ZLast-2))
			{
				X = XLast-1;
				Y = YLast;
				Z = ZLast-2;
				return 1;
			}
		}
		//front left top corner
		else if (XLast == 0 && YLast == 0 && ZLast == size - 1)
		{
			//Same stuff
			if (!ttt->checkMove(XLast, YLast+1, ZLast))
			{
				X = XLast;
				Y = YLast+1;
				Z = ZLast;
				return 1;
			}
			else if (!ttt->checkMove(XLast+1, YLast+1, ZLast))
			{
				X = XLast+1;
				Y = YLast+1;
				Z = ZLast;
				return 1;
			}
			else if (!ttt->checkMove(XLast+1, YLast, ZLast))
			{
				X = XLast+1;
				Y = YLast;
				Z = ZLast;
				return 1;
			}
			else if (!ttt->checkMove(XLast, YLast, ZLast-1))
			{
				X = XLast;
				Y = YLast;
				Z = ZLast-1;
				return 1;
			}
			else if (!ttt->checkMove(XLast, YLast+1, ZLast-1))
			{
				X = XLast;
				Y = YLast+1;
				Z = ZLast-1;
				return 1;
			}
			else if (!ttt->checkMove(XLast+1, YLast, ZLast-1))
			{
				X = XLast+1;
				Y = YLast;
				Z = ZLast-1;
				return 1;
			}
			else if (!ttt->checkMove(XLast, YLast+1, ZLast-2))
			{
				X = XLast;
				Y = YLast+1;
				Z = ZLast-2;
				return 1;
			}
			else if (!ttt->checkMove(XLast+1, YLast, ZLast-2))
			{
				X = XLast+1;
				Y = YLast;
				Z = ZLast-2;
				return 1;
			}
		}
		//Front right top corner
		else if (XLast == size - 1 && YLast == 0 && ZLast == size - 1)
		{
			//Same stuff
			if (!ttt->checkMove(XLast-1, YLast, ZLast))
			{
				X = XLast-1;
				Y = YLast;
				Z = ZLast;
				return 1;
			}
			else if (!ttt->checkMove(XLast-1, YLast+1, ZLast))
			{
				X = XLast-1;
				Y = YLast+1;
				Z = ZLast;
				return 1;
			}
			else if (!ttt->checkMove(XLast, YLast+1, ZLast))
			{
				X = XLast;
				Y = YLast+1;
				Z = ZLast;
				return 1;
			}
			else if (!ttt->checkMove(XLast, YLast, ZLast-1))
			{
				X = XLast;
				Y = YLast;
				Z = ZLast-1;
				return 1;
			}
			else if (!ttt->checkMove(XLast, YLast+1, ZLast-1))
			{
				X = XLast;
				Y = YLast+1;
				Z = ZLast-1;
				return 1;
			}
			else if (!ttt->checkMove(XLast-1, YLast, ZLast-1))
			{
				X = XLast-1;
				Y = YLast;
				Z = ZLast-1;
				return 1;
			}
			else if (!ttt->checkMove(XLast, YLast+1, ZLast-2))
			{
				X = XLast;
				Y = YLast+1;
				Z = ZLast-2;
				return 1;
			}
			else if (!ttt->checkMove(XLast-1, YLast, ZLast-2))
			{
				X = XLast-1;
				Y = YLast;
				Z = ZLast-2;
				return 1;
			}
		}
		// it's in a bottom back left corner
		else if (XLast == 0 && YLast == size - 1 && ZLast == 0)
		{
			//Same stuff
			if (!ttt->checkMove(XLast, YLast-1, ZLast))
			{
				X = XLast;
				Y = YLast-1;
				Z = ZLast;
				return 1;
			}
			else if (!ttt->checkMove(XLast+1, YLast, ZLast))
			{
				X = XLast+1;
				Y = YLast;
				Z = ZLast;
				return 1;
			}
			else if (!ttt->checkMove(XLast+1, YLast-1, ZLast))
			{
				X = XLast+1;
				Y = YLast-1;
				Z = ZLast;
				return 1;
			}
			else if (!ttt->checkMove(XLast, YLast, ZLast+1))
			{
				X = XLast;
				Y = YLast;
				Z = ZLast+1;
				return 1;
			}
			else if (!ttt->checkMove(XLast, YLast-1, ZLast+1))
			{
				X = XLast;
				Y = YLast-1;
				Z = ZLast+1;
				return 1;
			}
			else if (!ttt->checkMove(XLast+1, YLast, ZLast+1))
			{
				X = XLast+1;
				Y = YLast;
				Z = ZLast+1;
				return 1;
			}
			else if (!ttt->checkMove(XLast, YLast-1, ZLast+2))
			{
				X = XLast;
				Y = YLast-1;
				Z = ZLast+2;
				return 1;
			}
			else if (!ttt->checkMove(XLast+1, YLast, ZLast+2))
			{
				X = XLast+1;
				Y = YLast;
				Z = ZLast+2;
				return 1;
			}
		}
		///bottom right back corner
		else if (XLast == size - 1 && YLast == size - 1 && ZLast == 0)
		{
			//Are there MORE corner pieces?
			if (!ttt->checkMove(XLast-1, YLast, ZLast))
			{
				X = XLast-1;
				Y = YLast;
				Z = ZLast;
				return 1;
			}
			else if (!ttt->checkMove(XLast-1, YLast-1, ZLast))
			{
				X = XLast-1;
				Y = YLast-1;
				Z = ZLast;
				return 1;
			}
			else if (!ttt->checkMove(XLast, YLast-1, ZLast))
			{
				X = XLast;
				Y = YLast-1;
				Z = ZLast;
				return 1;
			}
			else if (!ttt->checkMove(XLast, YLast, ZLast+1))
			{
				X = XLast;
				Y = YLast;
				Z = ZLast+1;
				return 1;
			}
			else if (!ttt->checkMove(XLast, YLast-1, ZLast+1))
			{
				X = XLast;
				Y = YLast-1;
				Z = ZLast+1;
				return 1;
			}
			else if (!ttt->checkMove(XLast-1, YLast, ZLast+1))
			{
				X = XLast-1;
				Y = YLast;
				Z = ZLast+1;
				return 1;
			}
			else if (!ttt->checkMove(XLast, YLast-1, ZLast+2))
			{
				X = XLast;
				Y = YLast-1;
				Z = ZLast+2;
				return 1;
			}
			else if (!ttt->checkMove(XLast-1, YLast, ZLast+2))
			{
				X = XLast-1;
				Y = YLast;
				Z = ZLast+2;
				return 1;
			}
		}
		//front left bottom corner
		else if (XLast == 0 && YLast == 0 && ZLast == 0)
		{
			//Yep, there are
			if (!ttt->checkMove(XLast, YLast+1, ZLast))
			{
				X = XLast;
				Y = YLast+1;
				Z = ZLast;
				return 1;
			}
			else if (!ttt->checkMove(XLast+1, YLast+1, ZLast))
			{
				X = XLast+1;
				Y = YLast+1;
				Z = ZLast;
				return 1;
			}
			else if (!ttt->checkMove(XLast+1, YLast, ZLast))
			{
				X = XLast+1;
				Y = YLast;
				Z = ZLast;
				return 1;
			}
			else if (!ttt->checkMove(XLast, YLast, ZLast+1))
			{
				X = XLast;
				Y = YLast;
				Z = ZLast+1;
				return 1;
			}
			else if (!ttt->checkMove(XLast, YLast+1, ZLast+1))
			{
				X = XLast;
				Y = YLast+1;
				Z = ZLast+1;
				return 1;
			}
			else if (!ttt->checkMove(XLast+1, YLast, ZLast+1))
			{
				X = XLast+1;
				Y = YLast;
				Z = ZLast+1;
				return 1;
			}
			else if (!ttt->checkMove(XLast, YLast+1, ZLast+2))
			{
				X = XLast;
				Y = YLast+1;
				Z = ZLast+2;
				return 1;
			}
			else if (!ttt->checkMove(XLast+1, YLast, ZLast+2))
			{
				X = XLast+1;
				Y = YLast;
				Z = ZLast+2;
				return 1;
			}
		}
		//Front right bottom corner
		else if (XLast == size - 1 && YLast == 0 && ZLast == 0)
		{
			//I'm dying
			if (!ttt->checkMove(XLast-1, YLast, ZLast))
			{
				X = XLast-1;
				Y = YLast;
				Z = ZLast;
				return 1;
			}
			else if (!ttt->checkMove(XLast-1, YLast+1, ZLast))
			{
				X = XLast-1;
				Y = YLast+1;
				Z = ZLast;
				return 1;
			}
			else if (!ttt->checkMove(XLast, YLast+1, ZLast))
			{
				X = XLast;
				Y = YLast+1;
				Z = ZLast;
				return 1;
			}
			else if (!ttt->checkMove(XLast, YLast, ZLast+1))
			{
				X = XLast;
				Y = YLast;
				Z = ZLast+1;
				return 1;
			}
			else if (!ttt->checkMove(XLast, YLast+1, ZLast+1))
			{
				X = XLast;
				Y = YLast+1;
				Z = ZLast+1;
				return 1;
			}
			else if (!ttt->checkMove(XLast-1, YLast, ZLast+1))
			{
				X = XLast-1;
				Y = YLast;
				Z = ZLast+1;
				return 1;
			}
			else if (!ttt->checkMove(XLast, YLast+1, ZLast+2))
			{
				X = XLast;
				Y = YLast+1;
				Z = ZLast+2;
				return 1;
			}
			else if (!ttt->checkMove(XLast-1, YLast, ZLast+2))
			{
				X = XLast-1;
				Y = YLast;
				Z = ZLast+2;
				return 1;
			}
		}//end corners
		//Finally!
	}
	//It's a side piece. So not a corner. And not an edge. Side (as in very centre of one side)
	else if ((XLast == size/2 && YLast == size/2 && (ZLast == 0 || ZLast == size - 1)) || (XLast == size/2 && ZLast == size/2 && (YLast == 0 || YLast == size - 1)) || (YLast == size/2 && ZLast == size/2 && (XLast == 0 || XLast == size - 1)))
	{
		//take any piece in the middle layer (centre is already taken by this point)
		if (XLast == 0 || XLast == size - 1)
		{
			//If it's an extreme edge X piece
			for (int i = 0; i < size; i++)
			{
				for (int j = 0; j < size; j++)
				{
					//Take any spot where X is in the middle
					if (!ttt->checkMove(size/2, i, j))
					{
						X = size/2;
						Y = i;
						Z = j;
						return 1;
					}
				}
			}
		}
		else if (YLast == 0 || YLast == size - 1)
		{
			//If it's an extreme edge Y piece
			for (int i = 0; i < size; i++)
			{
				for (int j = 0; j < size; j++)
				{
					if (!ttt->checkMove(i, size/2, j))
					{
						//Take any spot where Y is in the middle
						X = i;
						Y = size/2;
						Z = j;
						return 1;
					}
				}
			}
		}
		else if (ZLast == 0 || ZLast == size - 1)
		{
			//If it's an extreme edge Z piece
			for (int i = 0; i < size; i++)
			{
				for (int j = 0; j < size; j++)
				{
					//Take any spot where Z is in the middle
					if (!ttt->checkMove(i, j, size/2))
					{
						X = i;
						Y = j;
						Z = size/2;
						return 1;
					}
				}
			}
		}
	}
	//end side piece
	else //so it must be a edge piece because the centre is already taken
	{
		//X edge piece
		if (XLast == size/2 && (YLast == 0 || YLast == size - 1) && (ZLast == 0 || ZLast == size - 1))
		{
			//When you come into class, you'll see a whole bunch of numbers on the board that are the basis for this code
			for (int i = 0; i < size; i+=2)
			{
				for (int j = 0; j < size; j++)
				{
					//Takes any pieces where Y = middle
					if (!ttt->checkMove(i, size/2, j))
					{
						X = i;
						Y = size/2;
						Z = j;
						return 1;
					}
					//Or where Z = middle
					else if (!ttt->checkMove(i, j, size/2))
					{
						X = i;
						Y = j;
						Z = size/2;
						return 1;
					}
				}
			}
		}
		//Y edge piece
		else if (YLast == size/2 && (XLast == 0 || XLast == size - 1) && (ZLast == 0 || ZLast == size - 1))
		{
			for (int i = 0; i < size; i+=2)
			{
				for (int j = 0; j < size; j++)
				{
					//Same stuff
					if (!ttt->checkMove(size/2, i, j))
					{
						X = size/2;
						Y = i;
						Z = j;
						return 1;
					}
					else if (!ttt->checkMove(j, i, size/2))
					{
						X = j;
						Y = i;
						Z = size/2;
						return 1;
					}
				}
			}
		}
		// Z edge piece
		else if (ZLast == size/2 && (XLast == 0 || XLast == size - 1) && (YLast == 0 || YLast == size - 1))
		{
			for (int i = 0; i < size; i+=2)
			{
				for (int j = 0; j < size; j++)
				{
					//Same stuff
					if (!ttt->checkMove(size/2, j, i))
					{
						X = size/2;
						Y = j;
						Z = i;
						return 1;
					}
					else if (!ttt->checkMove(j, size/2, i))
					{
						X = j;
						Y = size/2;
						Z = i;
						return 1;
					}
				}
			}
		}
	}
	//If none worked, call an ambulance
	return 0;
	//Lol JK, it failed. Try something else
	/*
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			for (int k = 0; k < size; k++)
			{
				if (getCurrent(i, j, k) == 1 && getCurrent(size/2, size/2, size/  == 1))
					{
						//It's a corner
						if ((i == size - 1 || i == 0) && (j == size - 1 || j == 0) && (k == size - 1 || k == 0))
						{
							// it's in a top back left corner
							// take an edge adjacent to it
							//This forces the player to go on the other side of the board to block.
							if (i == 0 && j == size - 1 && k == size - 1)
							{
								//Checks to see if this spot is free.
								if (!ttt->checkMove(i, j-1, k) && !ttt->checkMove(i, j-2, k))
								{
									if (!ttt->checkMove(2, 1, 0)
									{
										X = i;
										Y = j-1;
										Z = k;
										//Takes the spot and returns.
										return 1;
									}
									else if (!ttt->checkMove(2, 2, 0)
									{
										X = i;
										Y = j-2;
										Z = k;
										//Takes the spot and returns.
										return 1;
									}

								}
								else if (!ttt->checkMove(i+1, j, k) && !ttt->checkMove(i+2, j, k))
								{
									if (!ttt->checkMove(1, 0, 0)
									{
										X = i+1;
										Y = j;
										Z = k;
										//Takes the spot and returns.
										return 1;
									}
									else if (!ttt->checkMove(0, 0, 0)
									{
										X = i+2;
										Y = j;
										Z = k;
										//Takes the spot and returns.
										return 1;
									}
								}
								else if (!ttt->checkMove(i+1, j-1, k) && !ttt->checkMove(i+1, j-2, k))
								{
									if (!ttt->checkMove(1, 1, 0)
									{
										X = i+1;
										Y = j-1;
										Z = k;
										//Takes the spot and returns.
										return 1;
									}
									else if (!ttt->checkMove(0, 2, 0)
									{
										X = i+2;
										Y = j-2;
										Z = k;
										//Takes the spot and returns.
										return 1;
									}

								}
								else if (!ttt->checkMove(i, j, k-1) && !ttt->checkMove(i, j, k-2))
								{
									if (!ttt->checkMove(2, 0, 1)
									{
										X = i;
										Y = j;
										Z = k-1;
										//Takes the spot and returns.
										return 1;
									}
									else if (!ttt->checkMove(2, 0, 2)
									{
										X = i;
										Y = j;
										Z = k-2;
										//Takes the spot and returns.
										return 1;
									}

								}
								else if (!ttt->checkMove(i, j-1, k-1) && !ttt->checkMove(i, j-2, k-2))
								{
									if (!ttt->checkMove(2, 1, 0)
									{
										X = i;
										Y = j-1;
										Z = k-1;
										//Takes the spot and returns.
										return 1;
									}
									else if (!ttt->checkMove(2, 2, 2)
									{
										X = i;
										Y = j-2;
										Z = k-2;
										//Takes the spot and returns.
										return 1;
									}

								}
								else if (!ttt->checkMove(i+1, j, k-1) && !ttt->checkMove(i+2, j, k-2))
								{
									if (!ttt->checkMove(1, 0, 1)
									{
										X = i+1;
										Y = j;
										Z = k-1;
										//Takes the spot and returns.
										return 1;
									}
									else if (!ttt->checkMove(0, 0, 2)
									{
										X = i+2;
										Y = j-2;
										Z = k;
										//Takes the spot and returns.
										return 1;
									}

								}

							}
							else if (i == 0 && j == 0 && k == size - 1)
							{
								//Checks to see if this spot is free.
								if (!ttt->checkMove(i, j-1, k) && !ttt->checkMove(i, j-2, k))
								{
									if (!ttt->checkMove(2, 1, 0)
									{
										X = i;
										Y = j-1;
										Z = k;
										//Takes the spot and returns.
										return 1;
									}
									else if (!ttt->checkMove(2, 2, 0)
									{
										X = i;
										Y = j-2;
										Z = k;
										//Takes the spot and returns.
										return 1;
									}

								}
								else if (!ttt->checkMove(i+1, j, k) && !ttt->checkMove(i+2, j, k))
								{
									if (!ttt->checkMove(1, 0, 0)
									{
										X = i+1;
										Y = j;
										Z = k;
										//Takes the spot and returns.
										return 1;
									}
									else if (!ttt->checkMove(0, 0, 0)
									{
										X = i+2;
										Y = j;
										Z = k;
										//Takes the spot and returns.
										return 1;
									}
								}
								else if (!ttt->checkMove(i+1, j-1, k) && !ttt->checkMove(i+1, j-2, k))
								{
									if (!ttt->checkMove(1, 1, 0)
									{
										X = i+1;
										Y = j-1;
										Z = k;
										//Takes the spot and returns.
										return 1;
									}
									else if (!ttt->checkMove(0, 2, 0)
									{
										X = i+2;
										Y = j-2;
										Z = k;
										//Takes the spot and returns.
										return 1;
									}

								}
								else if (!ttt->checkMove(i, j, k-1) && !ttt->checkMove(i, j, k-2))
								{
									if (!ttt->checkMove(2, 0, 1)
									{
										X = i;
										Y = j;
										Z = k-1;
										//Takes the spot and returns.
										return 1;
									}
									else if (!ttt->checkMove(2, 0, 2)
									{
										X = i;
										Y = j;
										Z = k-2;
										//Takes the spot and returns.
										return 1;
									}

								}
								else if (!ttt->checkMove(i, j-1, k-1) && !ttt->checkMove(i, j-2, k-2))
								{
									if (!ttt->checkMove(2, 1, 0)
									{
										X = i;
										Y = j-1;
										Z = k-1;
										//Takes the spot and returns.
										return 1;
									}
									else if (!ttt->checkMove(2, 2, 2)
									{
										X = i;
										Y = j-2;
										Z = k-2;
										//Takes the spot and returns.
										return 1;
									}

								}
								else if (!ttt->checkMove(i+1, j, k-1) && !ttt->checkMove(i+2, j, k-2))
								{
									if (!ttt->checkMove(1, 0, 1)
									{
										X = i+1;
										Y = j;
										Z = k-1;
										//Takes the spot and returns.
										return 1;
									}
									else if (!ttt->checkMove(0, 0, 2)
									{
										X = i+2;
										Y = j-2;
										Z = k;
										//Takes the spot and returns.
										return 1;
									}

								}

							}*/
}
			
//Check if centre piece is open. Doesn't even need to be a function.
bool TakeCentre(int size, TTTBoard3 *ttt)
{
	if (!ttt->checkMove(size/2, size/2, size/2))
	{
		return 1;
	}
	return 0;
}

//Checks if every corner is open.
//Returns the value of the first open corner.
int TakeCorner(int size, TTTBoard3 *ttt)
{
	if (!ttt->checkMove(0, 0, 0))
	{
		return 1;
	}
	if (!ttt->checkMove(0, size - 1, 0))
	{
		return 2;
	}
	if (!ttt->checkMove(0, 0, size -1))
	{
		return 3;
	}
	if (!ttt->checkMove(size - 1, 0, 0))
	{
		return 4;
	}
	if (!ttt->checkMove(size - 1, size - 1, 0))
	{
		return 5;
	}
	if (!ttt->checkMove(size - 1, 0, size - 1))
	{
		return 6;
	}
	if (!ttt->checkMove(0, size - 1, size - 1))
	{
		return 7;
	}
	if (!ttt->checkMove(size - 1, size - 1, size - 1))
	{
		return 8;
	}
	//If no corners are availablae then try again
	return 0;
	//Really? ALL the corners are taken, and nobody has won yet? WOW I don't think that's even possible
}

//YAY, that's it!
