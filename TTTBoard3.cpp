#include "TTTBoard3.h"
#include "player.h"


//Tells drawboard the letter corresponding to each space. (X, O or space for empty)
char getLetter(int move);


//Constructor Function
TTTBoard3::TTTBoard3(int N)
{
	
	// Hard code an N... NO
	//N = 3;

	// Allocate size N to the POINTER to currentState
	// Allocating the "outer dimension" (one of the dimensions)
	// - This is going the be an array (*) of arrays of size N (new int[N])
	currentState = new int**[N];

	// For each part of the above array, allocate another array.
	for (int i = 0; i < N; i++)
	{
		currentState[i] = new int*[N];

		// For each part of the above array, allocate ANOTHER array.
		for (int j = 0; j < N; j++)
		{
			currentState[i][j] = new int[N];
		}
	}

	// Initialiaze board (all spots are empty)
	TTTBoard3::reset(N);
}

//Destructor Function
TTTBoard3::~TTTBoard3()
{
	int N = 3;
	//Cannot pass a variable, so it doesn't work for 4x4x4 or 5x5x5 fully

	// Delete the "inner part of the array

	for (int j = 0; j < N; j++)
	{
		for (int i = 0; i < N; i++)
		{
			delete [] currentState[j][i];
		}
		delete [] currentState[j];
	}
	// Delete the outer part of the array.
	delete [] currentState;
}

//Checks to see if winner
//Goes through every freaking combination of rows, columns, diagonals, 3D stuff, etc.
int TTTBoard3::isWinner(int N)
{
	//This is the thing that is compared to every element in a given row/column
	int winFlag;


	//---Traditional 2D win (k is 3rd)-----------------------------------

	// Check "2D" wins when the height (k) is fixed.
	for(int k = 0; k < N; k++)
	{ // Loop over each height
		// Your 2D "isWinner" code

		// This has row as "fast" index and column as "slow" index
		for(int j = 0; j < N; j++)
		{ //Column number
			winFlag = currentState[0][j][k]; //It equals the first element of the given row
			for(int i = 0; i < N; i++)
			{
				//One does not equal winFlag
				if(currentState[i][j][k] != winFlag)
				{
					//So the row is not a winner
					winFlag = -1; 
					break;
				}	
			}
			if(winFlag != -1)
			{
				//Say who won and exit
				std::cout << getLetter(winFlag) << " WINS!!!" << std::endl;
				return(winFlag);
			}
		}

	
		// This has column as "fast" index and row as "slow" index
		for(int j = 0; j < N; j++)
		{ //Row number
			winFlag = currentState[j][0][k];
			for(int i = 0; i < N; i++)
			{
				if(currentState[j][i][k] != winFlag)
				{
					winFlag = -1;
					break;
				}	
			}
			if(winFlag != -1)
			{
				std::cout << getLetter(winFlag) << " WINS!!!" << std::endl;
				return(winFlag);
			}
		}

		// Diagonals (first (0,0) -> (1,1) -> (2,2) )
		winFlag = currentState[0][0][k];
		for(int i = 0; i < N; i++)
		{
			if(currentState[i][i][k] != winFlag)
			{
					winFlag = -1;
					break;
			}	
		}
		if(winFlag != -1)
		{
			std::cout << getLetter(winFlag) << " WINS!!!" << std::endl;
			return(winFlag);
		}

		
		// Diagonals (first (0,2) -> (1,1) -> (2,0) )
		winFlag = currentState[0][N-1][k];
		for(int i = 0; i < N; i++)
		{
			if(currentState[i][N-(i+1)][k] != winFlag)
			{
				winFlag = -1;
				break;
			}
		}
		if(winFlag != -1)
		{
			std::cout << getLetter(winFlag) << " WINS!!!" << std::endl;
			return(winFlag);
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
			winFlag = currentState[0][k][j];
			for(int i = 0; i < N; i++)
			{
				if(currentState[i][k][j] != winFlag)
				{
					winFlag = -1;
					break;
				}	
			}
			if(winFlag != -1)
			{
				std::cout << getLetter(winFlag) << " WINS!!!" << std::endl;
				return(winFlag);
			}
		}

	
		// This has column as "fast" index and row as "slow" index
		for(int j = 0; j < N; j++)
		{ //Row number
			winFlag = currentState[j][k][0];
			for(int i = 0; i < N; i++)
			{
				if(currentState[j][k][i] != winFlag)
				{
					winFlag = -1;
					break;
				}	
			}
			if(winFlag != -1)
			{
				std::cout << getLetter(winFlag) << " WINS!!!" << std::endl;
				return(winFlag);
			}
		}

		// Diagonals (first (0,0) -> (1,1) -> (2,2) )
		winFlag = currentState[0][k][0];
		for(int i = 0; i < N; i++)
		{
			if(currentState[i][k][i] != winFlag)
			{
					winFlag = -1;
					break;
			}	
		}
		if(winFlag != -1)
		{
			std::cout << getLetter(winFlag) << " WINS!!!" << std::endl;
			return(winFlag);
		}

		
		// Diagonals (first (0,2) -> (1,1) -> (2,0) )
		winFlag = currentState[0][k][N-1];
		for(int i = 0; i < N; i++)
		{
			if(currentState[i][k][N-(i+1)] != winFlag)
			{
				winFlag = -1;
				break;
			}
		}
		if(winFlag != -1)
		{
			std::cout << getLetter(winFlag) << " WINS!!!" << std::endl;
			return(winFlag);
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
			winFlag = currentState[k][0][j];
			for(int i = 0; i < N; i++)
			{
				if(currentState[k][i][j] != winFlag)
				{
					winFlag = -1;
					break;
				}	
			}
			if(winFlag != -1)
			{
				std::cout << getLetter(winFlag) << " WINS!!!" << std::endl;
				return(winFlag);
			}
		}

	
		// This has column as "fast" index and row as "slow" index
		for(int j = 0; j < N; j++)
		{ //Row number
			winFlag = currentState[k][j][0];
			for(int i = 0; i < N; i++)
			{
				if(currentState[k][j][i] != winFlag)
				{
					winFlag = -1;
					break;
				}	
			}
			if(winFlag != -1)
			{
				std::cout << getLetter(winFlag) << " WINS!!!" << std::endl;
				return(winFlag);
			}
		}

		// Diagonals (first (0,0) -> (1,1) -> (2,2) )
		winFlag = currentState[k][0][0];
		for(int i = 0; i < N; i++)
		{
			if(currentState[k][i][i] != winFlag)
			{
					winFlag = -1;
					break;
			}	
		}
		if(winFlag != -1)
		{
			std::cout << getLetter(winFlag) << " WINS!!!" << std::endl;
			return(winFlag);
		}

		
		// Diagonals (first (0,2) -> (1,1) -> (2,0) )
		winFlag = currentState[k][0][N-1];
		for(int i = 0; i < N; i++)
		{
			if(currentState[k][i][N-(i+1)] != winFlag)
			{
				winFlag = -1;
				break;
			}
		}
		if(winFlag != -1)
		{
			std::cout << getLetter(winFlag) << " WINS!!!" << std::endl;
			return(winFlag);
		}

	}
	//----END Traditional 2D win-------------------------------

	// Check 3D diagonals
	// (0,0,0) (1,1,1) (2,2,2)
	winFlag = currentState[0][0][0];
	for(int i = 0; i < N; i++)
	{
		if(currentState[i][i][i] != winFlag)
		{
			winFlag = -1;
			break;
		}
	}
	if(winFlag != -1)
	{
		std::cout << getLetter(winFlag) << " WINS!!!" << std::endl;
		return(winFlag);
	}

	// (2,0,0) (1,1,1) (0,2,2)
	winFlag = currentState[N-1][0][0];
	for(int i = 0; i < N; i++)
	{
		if(currentState[N-(i+1)][i][i] != winFlag)
		{
			winFlag = -1;
			break;
		}
	}
	if(winFlag != -1)
	{
		std::cout << getLetter(winFlag) << " WINS!!!" << std::endl;
		return(winFlag);
	}

	// (0,2,0) (1,1,1) (2,0,2)
	winFlag = currentState[0][N-1][0];
	for(int i = 0; i < N; i++)
	{
		if(currentState[i][N-(i+1)][i] != winFlag)
		{
			winFlag = -1;
			break;
		}
	}
	if(winFlag != -1)
	{
		std::cout << getLetter(winFlag) << " WINS!!!" << std::endl;
		return(winFlag);
	}

	// (2,2,0) (1,1,1) (0,0,2)
	winFlag = currentState[0][0][N-1];
	for(int i = 0; i < N; i++)
	{
		if(currentState[i][i][N-(i+1)] != winFlag)
		{
			winFlag = -1;
			break;
		}
	}
	if(winFlag != -1)
	{
		std::cout << getLetter(winFlag) << " WINS!!!" << std::endl;
		return(winFlag);
	}

	// End checking
	// Return -1 (no win) if NONE of the above are winners
	return(-1);
}

//Updates current state with newest move.
void TTTBoard3::makeMove(int i, int j, int k, int playerNumber)
{
	//Will set computer player number (2) equal to one, so it is an O.
	if (playerNumber > 1)
	{
		playerNumber = 1;
	}
	currentState[i][j][k] = playerNumber; //0 for X and 1 for O
}

//Checks to see if the given space is empty.
bool TTTBoard3::checkMove (int i, int j, int k)
{
	if (currentState[i][j][k] == -1)
	{
		return 0;
	}
	return 1;
}

//Tells drawboard the letter corresponding to each space.
char getLetter(int move)
{
	if (move == 0)
	{
		return 'X';
	}
	else if (move == 1)
	{
		return 'O';
	}
	else
		return ' '; //If nobody has gone, returns a space
}

//Resets the board to empty
void TTTBoard3::reset(int N)
{
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			for (int k = 0; k < N; k++)
			{

				currentState[i][j][k] = -1;
				//resets all positions to -1
			}
		}
	}
}

//Literally draws and labels board
void TTTBoard3::drawBoard(int N)
{
	//Clears screen before srawing grid so it's easier to read.
	(system("cls"));
	std::cout << std::endl << std::endl;

	for (int k = N - 1; k >= 0; k--)
	{
		for (int j = N - 1; j >= 0; j--)
		{
			if (j != N / 2)
			{
				std::cout << '\t' << j << "  "; //Labels rows
			}
			else
			{
				std::cout << "  " << k << '\t' << j << "  "; //Labels Height and row for a given row in each grid
			}
			for (int i = 0; i < N; i++)
			{
				std::cout << getLetter(currentState[i][j][k]); //<< std::endl; //Prints X, O or space
				if (i < N-1)
				{
					std::cout << " | "; //Lines between each column
				}
			
			}
			std::cout << std::endl;
			//lines between each row
			if (j > 0)
			{
				std::cout << "\t  ";
				for (int i = 0; i < N - 1; i++)
				{
					std::cout << "---|";
				}
				std::cout << "---" << std::endl;
			}
		}
		std::cout << std::endl;
	}
	//Labels columns
	std::cout << '\t';
	for (int i = 0; i < N; i++)
	{
		std::cout << "   " << i;
	}
	std::cout << std::endl;
}


//Allows a function to access currentState even though it's private.
//Not really necessary, but I'm using it for now
int TTTBoard3::getCurrent(int X, int Y, int Z)
{
	return currentState[X][Y][Z];
}

