#include <vector>
#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

//Thomas Klaesges
//~4.5 hours spent total

//Prints out the chess board
void printBoard(vector<vector<int>> vec) {
	for (int i = 0; i < vec.size(); i++) {
		for (int j = 0; j < vec[i].size(); j++) {
			cout << setw(6) << setfill(' ') << vec[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl << endl;
}

//Checks if the knight can make a move
bool hasMoves(vector<vector<int>> board, int x, int y) {
	bool move{ false };
	if (board[y + 2][x + 1] > 0) {
		move = true;
	}
	if (board[y + 2][x - 1] > 0) {
		move = true;
	}
	if (board[y - 2][x + 1] > 0) {
		move = true;
	}
	if (board[y - 2][x - 1] > 0) {
		move = true;
	}
	if (board[y + 1][x + 2] > 0) {
		move = true;
	}
	if (board[y + 1][x - 2] > 0) {
		move = true;
	}
	if (board[y - 1][x + 2] > 0) {
		move = true;
	}
	if (board[y - 1][x - 2] > 0) {
		move = true;
	}
	return move;
}

//Returns a vector with the coordinates (x,y) of the next space the horse should move to
vector<int> findMove(vector<vector<int>> board, int x, int y) {
	int minMove{ 5000000 };
	int minX;
	int minY;

	if (board[y + 2][x + 1] < minMove && board[y + 2][x + 1] > 0) {
		minMove = board[y + 2][x + 1];
		minX = x + 1;
		minY = y + 2;
	}
	if (board[y + 2][x - 1] < minMove && board[y + 2][x - 1] > 0) {
		minMove = board[y + 2][x - 1];
		minX = x - 1;
		minY = y + 2;
	}
	if (board[y - 2][x - 1] < minMove && board[y - 2][x - 1] > 0) {
		minMove = board[y - 2][x - 1];
		minX = x - 1;
		minY = y - 2;
	}
	if (board[y - 2][x + 1] < minMove && board[y - 2][x + 1] > 0) {
		minMove = board[y - 2][x + 1];
		minX = x + 1;
		minY = y - 2;
	}
	if (board[y + 1][x - 2] < minMove && board[y + 1][x - 2] > 0) {
		minMove = board[y + 1][x - 2];
		minX = x - 2;
		minY = y + 1;
	}
	if (board[y + 1][x + 2] < minMove && board[y + 1][x + 2] > 0) {
		minMove = board[y + 1][x + 2];
		minX = x + 2;
		minY = y + 1;
	}
	if (board[y - 1][x - 2] < minMove && board[y - 1][x - 2] > 0) {
		minMove = board[y - 1][x - 2];
		minX = x - 2;
		minY = y - 1;
	}
	if (board[y - 1][x + 2] < minMove && board[y - 1][x + 2] > 0) {
		minMove = board[y - 1][x + 2];
		minX = x + 2;
		minY = y - 1;
	}
	vector<int> mins;
	mins.push_back(minX);
	mins.push_back(minY);

	return mins;
}

//Creates the chess board with numbers spiraling from center
vector<vector<int>> makeBoard(int sides) {
	//TRAVERSING THE VECTOR:
	//Decrementing outer vector (y) moves you up, incrementing moves you down
	//Decrementing inner vector (x) moves you right, incrementing moves you left
	int center = (sides / 2);
	int squareVal{ 2 };
	int sideSize{ 2 };
	int y{ center };
	int x{ center };
	vector<vector<int>> board(sides, vector<int>(sides, 0));
	board[y][x] = -15;
	//This for loops handles making the entire chess board
	for (int i = 0; i < sides / 2; i++) {

		x++;
		y--;
		//Loop to make the top 
		for (int j = 0; j < sideSize; j++) {
			x--;
			board[y][x] = squareVal;
			squareVal++;
		}
		
		//Loop to make the left side
		for (int j = 0; j < sideSize; j++) {
			y++;
			board[y][x] = squareVal;
			squareVal++;
		}
		
		//Loop to make the bottom side
		for (int j = 0; j < sideSize; j++) {
			x++;
			board[y][x] = squareVal;
			squareVal++;
		}
		
		//Loop to make the right side
		for (int j = 0; j < sideSize; j++) {
			y--;
			board[y][x] = squareVal;
			squareVal++;
		}
		sideSize += 2;
	}
	return board;
}

int main() {
	int sides{ 0 };
	cout << "How large would you like the sides? (Minimum of 61 if the knight moves to completion, odd numbers only): ";
	cin >> sides;
	vector<vector<int>> cuhDeyBoad = makeBoard(sides);

	printBoard(cuhDeyBoad);

	vector<int> moves;
	int horseX{ sides / 2 };
	int horseY{ sides / 2 };
	int movesMade{ 0 };

	char input;

	cout << "Would you like to proceed manually? (y/n)" << endl;

	cin >> input;

	if (input == 'y') {
		cout << "Would you like to make a move? (y/n)" << endl;

		cin >> input;


		//Loop for manual input
		while (input != 'n') {
			if (!hasMoves(cuhDeyBoad, horseX, horseY)) {
				cout << "No more moves!" << endl;
				cout << "The knight made " << movesMade << " moves." << endl;
				break;
			}

			vector<int> moves = findMove(cuhDeyBoad, horseX, horseY);

			cuhDeyBoad[horseY][horseX] = -1;

			horseX = moves[0];
			horseY = moves[1];

			cuhDeyBoad[horseY][horseX] = -15;

			printBoard(cuhDeyBoad);

			movesMade++;

			cout << "Would you like to make a move? (y/n)" << endl;

			cin >> input;
		}
	}
	else {
		while (hasMoves(cuhDeyBoad, horseX, horseY)) {
			vector<int> moves = findMove(cuhDeyBoad, horseX, horseY);

			cuhDeyBoad[horseY][horseX] = -1;

			horseX = moves[0];
			horseY = moves[1];

			cuhDeyBoad[horseY][horseX] = -15;

			movesMade++;

			//printBoard(cuhDeyBoad);

			//cout << endl;
		}
		printBoard(cuhDeyBoad);
		cout << "No more moves!" << endl;
		cout << "The knight made " << movesMade << " moves." << endl;
	}
}