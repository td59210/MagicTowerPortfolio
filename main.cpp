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
	void addHealth(int x) {
		health += x;
	}
	void addStrength(int x) {
		strength += x;
	}
	void addDefense(int x) {
		defense += x;
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

	void findStart(Player& player) { //player will always start on the @
		for (int r = 0; r < grid.size(); r++) {
			for (int c = 0; c < grid[r].size(); c++) {
				if (grid[r][c] == '@') {
					player.setPosition(r, c);
					grid[r][c] = '.';
				}
			}
		}
	}


	void print(Player& player) {
		cout << "\n";

		for (int i = 0; i < rows; i++) { //moves player as @
			for (int j = 0; j < cols; j++) {
				if (i == player.getRow() && j == player.getCol())
					cout << "@";
				else
					cout << grid[i][j];
			}
			cout << endl;
		}
		/*
		//display stats
		cout << "\nHealth: " << player.getHealth();
		cout << "\nStrength: " << player.getStrength();   //->this ended up double printing, prefer other way
		cout << "\nDefense: " << player.getDefense();
		cout << "\nKeys: " << player.getKeys();
		*/
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
			cout << "\n";
			cout << "You've found a key!\n";
			player.addKey();
			grid[newRow][newCol] = '.'; //replaces item with empty space or .
			cout << "\n";
			player.printStats();
		}

		if (tile == 'D') { //door
			if (player.useKey()) {
				cout << "\n";
				cout << "You've unlocked the door!\n";
				grid[newRow][newCol] = '.';
				cout << "\n";
				player.printStats();
			}
			else {
				cout << "\n";
				cout << "You need a key.\n";
				return false;
			}
		}

		if (tile == 'H') {
			cout << "\n";
			cout << "You've found a health potion!\n";
			player.addHealth(10);
			grid[newRow][newCol] = '.';
			cout << "\n";
			player.printStats();
			//cout << "Your new health is: " << player.getHealth();
		}

		if (tile == 'S') {
			cout << "\n";
			cout << "You've found a strength potion!\n";
			player.addStrength(5);
			grid[newRow][newCol] = '.';
			cout << "\n";
			player.printStats();
		}

		if (tile == 'F') {
			cout << "\n";
			cout << "You've found a defense potion!\n";
			player.addDefense(5);
			grid[newRow][newCol] = '.';
			cout << "\n";
			player.printStats();
		}

		if (tile == 'E') {
			cout << "\n";
			cout << "An enemy appeared! Your fight will now begin!\n";
			Enemy enemy;

			//fight
			while (player.isAlive() && enemy.isAlive()) {
				int dmgp = player.getStrength() - enemy.getDefense(); //calc damage enemy wil take
				if (dmgp < 0) 
					dmgp = 0; //no negative damage
				enemy.takeDamage(dmgp); 

				if (enemy.isAlive()) {
					int dmge = enemy.getStrength() - player.getDefense();
					if (dmge < 0)
						dmge = 0;
					player.takeDamage(dmge);
				}

				if (!player.isAlive()) {
					cout << "\n";
					cout << "You were defeated! The game will end.\n";
					return true; //end game
				}
				cout << "\n";
				cout << "You defeated the enemy! You may move on.\n"; //this prints multiple time--> fix if time
			}
			grid[newRow][newCol] = '.';
		}
		
		if (tile == 'G') {
			cout << "\n";
			cout << "You've reached the goal! You win!\n";
			player.setPosition(newRow, newCol);
			return true; //win
		}

		player.setPosition(newRow, newCol);
		return false;
	}

	//preloaded dungeons

	static vector<vector<string>> getPreDungeon() {
		vector<vector<string>> levels;

		levels.push_back({
			"#########",
			"#@....E.#",
			"#.##.##.#",
			"#K..H..G#",
			"#########"
			});

		levels.push_back({
			"########",
			"#G..#E.#",
			"#.#D#.K#",
			"#.#H.S.#",
			"#@..F..#",
			"########"
			});

		return levels;
	}

};

class Game {
private:
	vector<vector<string>> dungeons;

public:
	
	Game() {
		dungeons = Dungeon::getPreDungeon();
	}

	//level editor

	void levelEditor() {
		int rows, cols;

		cout << "\n--- Level Editor ---\n";
		cout << "Use the following characters:\n";
		cout << "# = Wall\n";
		cout << ". = Empty space\n";
		cout << "@ = Player start (REQUIRED)\n";
		cout << "K = Key\n";
		cout << "D = Door\n";
		cout << "H = Health potion\n";
		cout << "S = Strength potion\n";
		cout << "F = Defense potion\n";
		cout << "E = Enemy\n";
		cout << "G = Goal (REQUIRED)\n\n";

		cout << "Limit rows and columns to 20.\n"; //add limit to check if time
		cout << "Enter number of rows: ";
		cin >> rows;
		cout << "Enter number of columns: ";
		cin >> cols;

		vector<string> newGrid(rows);

		cout << "\nEnter each row exactly " << cols << " characters long:\n";

		for (int i = 0; i < rows; i++) {
			cin >> newGrid[i];
		}

		dungeons.push_back(newGrid);
		cout << "Dungeon created!\n";
	}

	void run() {
		while (true) {
			cout << "\n---Welcome to the Magic Tower---\n";
			cout << "1) Enter a dungeon\n";
			cout << "2) Create a dungeon\n";
			cout << "3) Exit\n";

			int choice;
			cout << "Your choice: ";
			cin >> choice;

			if (choice == 1) {

				cout << "\nChoose a dungeon:\n";
				for (int i = 0; i < dungeons.size(); i++) {
					cout << i + 1 << ") Dungeon " << i + 1 << endl;
				}

				int selection;
				cin >> selection;
				selection--;

				if (selection < 0 || selection >= dungeons.size()) {
					cout << "Invalid selection.\n";
					continue;
				}

				Player player;
				Dungeon dungeon(dungeons[selection]);

				dungeon.findStart(player);

				bool gameOver = false;

				while (!gameOver && player.isAlive()) {
					dungeon.print(player);

					char move;
					cout << "\nMove (U/D/L/R): ";
					cin >> move;

					gameOver = dungeon.movePlayer(player, move);
				}

				if (!player.isAlive()) {
					cout << "\nYou died. Game over.\n";
				}
			}

			else if (choice == 2) {
				levelEditor();
			}

			else if (choice == 3) {
				cout << "Goodbye!\n";
				break;
			}

			else {
				cout << "Invalid choice.\n";
			}
		}
	}

};


int main() {
	
	Game game;
	game.run();
	return 0;

}