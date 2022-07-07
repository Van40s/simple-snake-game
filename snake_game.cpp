#include <iostream>
#include <conio.h>
#include <windows.h>
#include <ctime>

void board(char **matrix, int sizeX, int sizeY, int *tailX, int *tailY, int fruitX, int fruitY, int *gamestop, int score) {
	int i, j;
	bool printed = false;
	for (i = 0; i < sizeY; i++) {
		for (j = 0; j < sizeX; j++) {
			if (tailX[0] == 0 || tailY[0] == 0 || tailX[0] == sizeX - 1 || tailY[0] == sizeY - 1) {
				*gamestop = 1;
				return;
			}
			if (i == 0 || j == 0 || i == sizeY - 1 || j == sizeX - 1) {
				matrix[i][j] = '#';
			}
			else if (i == tailY[0] && j == tailX[0]) {
				matrix[i][j] = 'O';
			}
			else if (i == fruitY && j == fruitX) {
				matrix[i][j] = 'F';
			}
			else {
				printed = false;
				for (int k = 0; k < score; k++) {
					if (i == tailY[k] && j == tailX[k]) {
						printed = true;
						matrix[i][j] = 'o';
					}
				}
				if (printed == false) {
					matrix[i][j] = 32;
				}
			}
		}
	}
	for (int k = score; k > 0; k--) {
		tailX[k] = tailX[k - 1];
		tailY[k] = tailY[k - 1];
	}
}

void bite(int* tailX, int* tailY, int* score) {
	int i;
	for (i = 1; i < *score; i++) {
		if (tailX[0] == tailX[i] && tailY[0] == tailY[i]) {
			*score -= (*score - i);
			return;
		}
	}
}

void draw(char** matrix, int sizeX, int sizeY) {
	int i, j;
	for (i = 0; i < sizeY; i++) {
		for (j = 0; j < sizeX; j++) {
			std::cout << matrix[i][j];
		}
		std::cout << "\n";
	}
}

void movement(char dir, int *tailX, int *tailY, int *gamestop){
	switch (dir) {
	case 'a':
		tailX[0] -= 1;
		break;
	case 'd':
		tailX[0] += 1;
		break;
	case 'w':
		tailY[0] -= 1;
		break;
	case 's':
		tailY[0] += 1;
		break;
	case 'p':

		break;
	case 'e':
		*gamestop = 0;
		break;
	}
}

int main() {
	srand(time(NULL));
	std::cout << "Please enter the lenght of the board" << std::endl;
	int sizeX, sizeY;
	std::cin >> sizeX >> sizeY;
	char** matrix;
	int tailX[50], tailY[50];
	matrix = new char* [sizeY];
	for (int i = 0; i < sizeY; i++) {
		matrix[i] = new char[sizeX];
	}
	int fruitX, fruitY, score = 1, gamestop = 0;
	tailY[0] = (rand() % (sizeX - 2)) + 1;
	tailX[0] = (rand() % (sizeY - 2)) + 1;
	fruitX = (rand() % (sizeX - 2)) + 1;
	fruitY = (rand() % (sizeY - 2)) + 1;
	char dir = 'p';
	do {
		system("cls");
		if (_kbhit()) {
			switch (_getch()) {
			case 'a':
				dir = 'a';
				break;
			case 'd':
				dir = 'd';
				break;
			case 'w':
				dir = 'w';
				break;
			case 's':
				dir = 's';
				break;
			case 'e':
				dir = 'e';
				break;
			case 'p':
				dir = 'p';
				break;
			}
		}
		
		if (tailX[0] == fruitX && tailY[0] == fruitY) {
			fruitX = (rand() % (sizeX - 2)) + 1;
			fruitY = (rand() % (sizeY - 2)) + 1;
			score++;
			switch (dir) {
			case 'a':
				tailX[score] = tailX[0] + score;
				tailY[score] = tailY[0];
				break;
			case 'd':
				tailX[score] = tailX[0] - score;
				tailY[score] = tailY[0];
				break;
			case 'w':
				tailX[score] = tailX[0];
				tailY[score] = tailY[0] + score;
				break;
			case 's':
				tailX[score] = tailX[0];
				tailY[score] = tailY[0] - score;
				break;
			}
		}
		movement(dir, tailX, tailY, &gamestop);
		bite(tailX, tailY, &score);
		board(matrix, sizeX, sizeY, tailX, tailY, fruitX, fruitY, &gamestop, score);
		Sleep(10);
		draw(matrix, sizeX, sizeY);
		if (gamestop == 1) {
			break;
		}
		std::cout << "Score: " << score;
	} while (dir != 'e');
	if (gamestop == 1) {
		std::cout << "You just hit a wall!" << std::endl;
	}
	else {
		std::cout << "\nYou exited the game" << std::endl;
	}
	for (int i = 0; i < sizeX; i++) {
		delete matrix[i];
	}
	delete[] matrix;
	return 0;
}
