#include<iostream>
#include<conio.h>
#include<fstream>
#include<time.h>
using namespace std;

#define CAPACITY 100

void init(char Board[][CAPACITY], int& dim, char pName[2][30], char pSym[], int& NOP, int& turn, int& winCount);
void printBoard(char Board[][CAPACITY], int  dim);
void userInput(int& ri, int& ci, char pName[], char pSym);
bool validInput(int ri, int ci, char Board[][CAPACITY], int dim);
void updateBoard(char Board[][CAPACITY], int  dim, int ri, int ci, char pSym);
bool horizontalCheck(char Board[][CAPACITY], int dim, int winCount, char pSym, int ri, int ci);
bool vericalCheck(char Board[][CAPACITY], int dim, int winCount, char pSym, int ri, int ci);
bool rightDiagonalCheck(char Board[][CAPACITY], int dim, int winCount, char pSym, int ri, int ci);
bool leftDiagonalCheck(char Board[][CAPACITY], int dim, int winCount, char pSym, int ri, int ci);
bool isWinHere(char Board[][CAPACITY], int  dim, int winCount, char pSym, int ri, int ci);
bool isWin(char Board[][CAPACITY], int  dim, int winCount, char pSym);
bool isDraw(char Board[][CAPACITY], int dim);
void turnChange(int& turn, int NOP);

int main()
{
	cout << "\n\n\t\t\tThe Game of Gomoku...!!!\n\n";
	cout << "\n\n\t\t\t    Let us play...!\n\n" << endl;
	srand(time(0));
	char choice;
	char Board[CAPACITY][CAPACITY];
	char pName[2][30];
	char pSym[2];
	int turn, ri, ci, dim, NOP, winCount;
	bool gameOver = false;
	int winnerCount[2] = { 0, 0 };
	int winner = -1;
	do
	{
		cout << "Initializing...!!!" << endl;
		init(Board, dim, pName, pSym, NOP, turn, winCount);
		do
		{
			printBoard(Board, dim);

			do
			{
				userInput(ri, ci, pName[turn], pSym[turn]);
				if (!validInput(ri, ci, Board, dim))
				{
					cout << "Invalid Input" << endl;

				}
			} while (!validInput(ri, ci, Board, dim));
			updateBoard(Board, dim, ri, ci, pSym[turn]);
			gameOver = isWin(Board, dim, winCount, pSym[turn]);
			if (gameOver)
				winner = turn;
			else if (isDraw(Board, dim))
				gameOver = true;
			if (!gameOver)
				turnChange(turn, NOP);
		} while (!gameOver);
		cout << endl;
		if (winner == -1)
			cout << "Game Draw!" << endl;
		else
		{
			cout << pName[turn] << " has won!" << endl;
			winnerCount[winner]++;
		}
		cout << "Do you want to play again? y/n ";
		cin >> choice;
	} while (choice == 'y' || choice == 'Y');
	for (int i = 0; i < 2; i++)
	{
		cout << "Player" << pName[i] << " has won " << winnerCount[i] << " times";
	}
}
void init(char Board[][CAPACITY], int& dim, char pName[2][30], char pSym[], int& NOP, int& turn, int& winCount)
{
	cout << "Dimension: ";
	cin >> dim;
	cout << "Win Count: ";
	cin >> winCount;
	cout << "# of Players: ";
	cin >> NOP;
	for (int i = 0; i < NOP; i++)
	{
		cout << "Enter player " << i + 1 << "'s name: ";
		cin >> pName[i]; 
	}
	for (int i = 0; i < NOP; i++)
	{
		cout << "Enter player " << i + 1 << "'s symbol: ";
		cin >> pSym[i];
	}
	for (int ri = 0; ri < dim; ri++)
	{
		for (int ci = 0; ci < dim; ci++)
		{
			Board[ri][ci] = '-';
		}
	}
	turn = rand() % 2;
}
void printBoard(char Board[][CAPACITY], int  dim)
{
	system("clear");   
	for (int ri = 0; ri < dim; ri++)
	{
		for (int ci = 0; ci < dim; ci++)
		{
			cout << Board[ri][ci] << "   ";
		}
		cout << endl;
	}
}
void userInput(int& ri, int& ci, char pName[], char pSym)
{
	cout << pName << "'s Turn to place '" << pSym << " ' (ri, ci): ";
	cin >> ri;
	cin >> ci;
	ri--;
	ci--;
}
bool validInput(int ri, int ci, char Board[][CAPACITY], int dim)
{
	return ((ri >= 0 && ci >= 0) && (ri <= dim && ci <= dim) && Board[ri][ci] == '-');
}
void updateBoard(char Board[][CAPACITY], int  dim, int ri, int ci, char pSym)
{
	Board[ri][ci] = pSym;
}
bool horizontalCheck(char Board[][CAPACITY], int dim, int winCount, char pSym, int ri, int ci)
{
	if (ci + winCount - 1 >= dim)
		return false;
	for (int i = 0; i < winCount; i++)
	{
		if (Board[ri][ci + i] != pSym)
			return false;
	}
	return true;
}
bool vericalCheck(char Board[][CAPACITY], int dim, int winCount, char pSym, int ri, int ci)
{
	if (ri + winCount - 1 >= dim)
		return false;
	for (int i = 0; i < winCount; i++)
	{
		if (Board[ri + i][ci] != pSym)
			return false;
	}
	return true;
}
bool rightDiagonalCheck(char Board[][CAPACITY], int dim, int winCount, char pSym, int ri, int ci)
{
	if (ri + winCount - 1 >= dim)
		return false;
	for (int i = 0; i < winCount; i++)
	{
		if (Board[ri + i][ci + i] != pSym)
			return false;
	}
	return true;
}
bool leftDiagonalCheck(char Board[][CAPACITY], int dim, int winCount, char pSym, int ri, int ci)
{
	if (ci - (winCount - 1) < 0)
		return false;
	for (int i = 0; i < winCount; i++)
	{
		if (Board[ri + i][ci - i] != pSym)
			return false;
	}
	return true;

}
bool isWinHere(char Board[][CAPACITY], int  dim, int winCount, char pSym, int ri, int ci)
{
	bool horizontal = horizontalCheck(Board, dim, winCount, pSym, ri, ci);
	bool vertical = vericalCheck(Board, dim, winCount, pSym, ri, ci);
	bool leftDiagonal = leftDiagonalCheck(Board, dim, winCount, pSym, ri, ci);
	bool rightDiagnal = rightDiagonalCheck(Board, dim, winCount, pSym, ri, ci);
	return (horizontal || vertical || leftDiagonal || rightDiagnal);
}
bool isWin(char Board[][CAPACITY], int  dim, int winCount, char pSym)
{
	for (int ri = 0; ri < dim; ri++)
	{
		for (int ci = 0; ci < dim; ci++)
		{
			if (isWinHere(Board, dim, winCount, pSym, ri, ci))
				return true;
		}
	}

	return false;
}
bool isDraw(char Board[][CAPACITY], int dim)
{
	for (int ri = 0; ri < dim; ri++)
	{
		for (int ci = 0; ci < dim; ci++)
		{
			if (Board[ri][ci] == '-')
				return false;
		}
	}
	return true;
}
void turnChange(int& turn, int NOP)
{
	turn = (turn + 1) % NOP;
}

