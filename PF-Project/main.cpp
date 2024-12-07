#include <iostream>
#include <iostream>
#include <cstring>
// For random number generation
#include <ctime>
#include <cstdlib>
// For sleep function
#include <chrono>
#include <thread>
// For keys input
#include <conio.h>

using namespace std;

const int ROW = 30;
const int COL = 50;
int spaceship_x = COL / 2;
int spaceship_y = ROW - 3;
char map[ROW][COL];

// Initializing map with spaces
void initMap() {
    for (int i = 0; i < ROW; i++) {
        for (int j = 0; j < COL; j++) {
            map[i][j] = ' ';
        }
    }
}

// Making boundaries
void mapBoundary() {
    for (int i = 0; i < ROW; ++i) {
        map[i][0] = '|';
        map[i][COL - 1] = '|';
    }
    for (int j = 0; j < COL; ++j) {
        map[0][j] = '=';
        map[ROW - 1][j] = '=';
    }
}

// Drawing map
void drawMap() {
    mapBoundary();
    for (int i = 0; i < ROW; ++i) {
        for (int j = 0; j < COL; ++j) {
            cout << map[i][j];
        }
        cout << endl;
    }
}

// For generating random asteroids
void stars() {
    int x = rand() % (COL - 2) + 1;
    map[1][x] = '*';
}

// For moving asteroids down
void moveStars() {
    for (int i = ROW - 2; i > 0; i--) {
        for (int j = 1; j < COL - 1; j++) {
            if (map[i][j] == '*') {
                map[i][j] = ' ';
                if (i + 1 < ROW - 1) {
                    map[i + 1][j] = '*';
                }
            }
        }
    }
}

// For generating random asteroids
void asteroid() {
    int x = rand() % (COL - 2) + 1;
    map[1][x] = '#';
}

// For moving asteroids down
void moveAsteroids() {
    for (int i = ROW - 2; i > 0; i--) {
        for (int j = 1; j < COL - 1; j++) {
            if (map[i][j] == '#') {
                map[i][j] = ' ';
                if (i + 1 < ROW - 1) {
                    map[i + 1][j] = '#';
                }
            }
        }
    }
}

// display spaceship
void drawSpaceship() {
    map[spaceship_y][spaceship_x - 1] = '<';
    map[spaceship_y][spaceship_x] = '^';
    map[spaceship_y][spaceship_x + 1] = '>';
}
// remove spaceship
void removeSpaceship() {
	map[spaceship_y][spaceship_x - 1] = ' ';
	map[spaceship_y][spaceship_x] = ' ';
	map[spaceship_y][spaceship_x + 1] = ' ';
}
// For movement of spaceship
void moveSpaceship(char move) {
    if (move == 75 && spaceship_x > 2) {
		removeSpaceship();
        spaceship_x--;
    }
    else if (move == 77 && spaceship_x < COL - 3) {
		removeSpaceship();
        spaceship_x++;
    }
    else if (move == 'b' || move == 'B') {
        if (spaceship_y > ROW - 11) {
			removeSpaceship();
            spaceship_y--;
        }
    }
}

int main() {
    srand(time(0));
    initMap();
	drawMap();
    while (true) {
        asteroid();
        moveAsteroids();
		stars();
		moveStars();
        if (_kbhit()) {
            char key = _getch();
            moveSpaceship(key);
        }
        drawSpaceship();
        drawMap();
        std::this_thread::sleep_for(std::chrono::milliseconds(150)); // Smooth update
        system("cls");
		cin.clear();
    }
	system("pause");
    return 0;
}

