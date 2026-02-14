#include <iostream>
#include <string>
#include <vector>

using namespace std;


class Player {
private:
	int strength;
	int health;
	int defense;
	int keys;
	int row;
	int col; //column

public:

	Player() {
		health = 100;
		strength = 20;
		defense = 10;
		keys = 0;
		row = 1;
		col = 1;
	}

	//position
	int getRow() {
		return row;
	}
	int getCol() {
		return col;
	}
	void setPosition(int r, int c) { //sets position
		row = r;
		col = c;
	}

	//getters for stats
	int getHealth() {
		return health;
	}
	int getStrength() {
		return strength;
	}
	int getDefense(){
		return defense;
	}
	int getKeys() {
		return keys;
	}

	//updating stats
	//adding
	void addHealth(int amount) {
		health += amount;
	}
	void addStrength(int amount) {
		strength += amount;
	}
	void addDefense(int amount) {
		defense += amount;
	}
	//damage
	void takeDamage(int damage) {
		health -= damage;
	}
	//keys
	void addKey() {
		keys++;
	}
	bool useKey() {
		if (keys > 0) { //check for keys
			keys--;
			return true; //yes there's keys
		}
		return false; //no keys
	}
	//alive or dead
	bool isAlive() {
		return health > 0;
	}

	//printing updated stats
	void printStats() {
		cout << "Your updated stats are:\n";
		cout << "Health: " << health << endl;
		cout << "Strength: " << strength << endl;
		cout << "Defense: " << defense << endl;
		cout << "Keys: " << keys << endl;
	}

};

class Dungeon {
private:
	vector<string> grid; //vector<vector<char>> grid;
	int rows;
	int cols;

public:
	Dungeon(vector<string> levelGrid) { //takes in chosen grid
		grid = levelGrid;
		rows = grid.size();
		cols = grid[0].size();
	}

	void print(Player& player) {
		cout << "\n";

		for (int i = 0; i < rows; i++) {
			for (int j = 0; j < cols; j++) {
				if (i == player.getRow() && j == player.getCol())
					cout << "@";
				else
					cout << grid[i][j];
			}
			cout << endl;
		}

		//display stats
		cout << "\nHealth: " << player.getHealth();
		cout << "\nStrength: " << player.getStrength();
		cout << "\nDefense: " << player.getDefense();
		cout << "\nKeys: " << player.getKeys();
	}
	//check bounds
	bool inBounds(int r, int c) {
		return r >= 0 && r < rows && c >= 0 && c < cols;
	}

	//movement
	bool movePlayer(Player& player, char dir) {
		int newRow = player.getRow(); //initialize new pos
		int newCol = player.getCol();

		if (dir == 'U' || dir == 'u')
			newRow--;
		else if (dir == 'D' || dir == 'd')
			newRow++;
		else if (dir == 'L' || dir == 'l')
			newCol--;
		else if (dir == 'R' || dir == 'r')
			newCol++;

		//check bounds
		if (!inBounds(newRow, newCol))
			return false;

		//checking spaces and outputting info
		char tile = grid[newRow][newCol];

		if (tile == '#') {
			cout << "You've hit a wall!\n";
			return false;
		}

		if (tile == 'K') {
			cout << "You've found a key!\n";
			player.addKey();
			grid[newRow][newCol] = '.'; //replaces item with empty space or .
			player.printStats();
		}

		if (tile == 'D') { //door
			if (player.useKey()) {
				cout << "You've unlocked the door!\n";
				grid[newRow][newCol] = '.';
				player.printStats();
			}
			else {
				cout << "You need a key.\n";
				return false;
			}
		}

		if (tile == 'H') {
			cout << "You've found a health potion!\n";
			player.addHealth(10);
			grid[newRow][newCol] = '.';
			player.printStats();
			//cout << "Your new health is: " << player.getHealth();
		}

		if (tile == 'S') {
			cout << "You've found a strength potion!\n";
			player.addStrength(5);
			grid[newRow][newCol] = '.';
			player.printStats();
		}

		if (tile == defense)
	}

};

class Enemy {
private:
	int health;
	int strength;
	int defense;

public:
	Enemy() {
		health = 50;
		strength = 10;
		defense = 5;
	}

	//stat getters
	int getHealth() {
		return health;
	}
	int getStrength() {
		return strength;
	}
	int getDefense() {
		return defense;
	}

	//damage
	void takeDamage(int damage) {
		health -= damage;
	}

	//alive or dead
	bool isAlive() {
		return health > 0;
	}
	
};

class Game {
private:



public:


};

class LevelEditor {

};


int main() {


}