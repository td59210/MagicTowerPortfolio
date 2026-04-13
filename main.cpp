#include <iostream>
#include <string>
#include <vector>
#include <cctype>

using namespace std;


class Player {
private:
	int strength;
	int health;
	int defense;
	//int keys;
	int blueKeys;
	int redKeys;
	int row;
	int col; //column

public:

	Player() {
		health = 100;
		strength = 20;
		defense = 10;
		redKeys = 0;
		blueKeys = 0;
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
	int getRedKeys() {
		return redKeys;
	}
	int getBlueKeys() {
		return blueKeys;
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
	void addKey(string type) {
		if (type == "red") redKeys++;
		else if (type == "blue") blueKeys++;
	}

	bool useKey(string type) {
		if (type == "red" && redKeys > 0) {
			redKeys--;
			return true;
		}
		else if (type == "blue" && blueKeys > 0) {
			blueKeys--;
			return true;
		}
		return false;
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
		cout << "Keys:\n";
		cout << "Red: " << redKeys << endl;
		cout << "Blue: " << blueKeys << endl;
	}

};

class Enemy {
private:
	int health;
	int strength;
	int defense;

public:
	Enemy(int h, int s, int d) {
		health = h;
		strength = s;
		defense = d;
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

//polymorphism for tiles
class DamageTile {
public: 
	virtual int getDamage() = 0;
	virtual string getName() = 0;
};

class Lava : public DamageTile {
public:
	int getDamage() { 
		return 5; 
	}
	string getName() { 
		return "Lava"; 
	}
};

class Spikes : public DamageTile {
public:
	int getDamage() { 
		return 3;
	}
	string getName() { 
		return "Spikes"; 
	}
};

class Poison : public DamageTile {
public:
	int getDamage() { 
		return 2; 
	}
	string getName() {
		return "Poison"; 
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

	//getter for tile inspection
	char getTile(int r, int c) {
		if (inBounds(r, c)) {
			return grid[r][c];
		}
		return '#'; // fallback (wall)
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
				if (i == player.getRow() && j == player.getCol()) {
					cout << "@";
				}
				else {
					cout << grid[i][j];
				}
			}
			cout << endl;
		}
	
		//display stats
		cout << "\nHealth: " << player.getHealth();
		cout << "\nStrength: " << player.getStrength();   
		cout << "\nDefense: " << player.getDefense();
		cout << "\nKeys:";
		cout << "\nRed: " << player.getRedKeys();
		cout << "\nBlue: " << player.getBlueKeys();
	
	}
	//check bounds
	bool inBounds(int r, int c) {
		return r >= 0 && r < rows && c >= 0 && c < cols;
	}

	//movement
	bool movePlayer(Player& player, char dir) {
		int newRow = player.getRow(); //initialize new pos
		int newCol = player.getCol();

		if (dir == 'U') {
			newRow--;
		}
		else if (dir == 'D') {
			newRow++;
		}
		else if (dir == 'L') {
			newCol--;
		}
		else if (dir == 'R') {
			newCol++;
		}

		//check bounds
		if (!inBounds(newRow, newCol)) {
			return false;
		}

		//checking spaces and outputting info
		char tile = grid[newRow][newCol];


		if (tile == '#') {
			cout << "\nYou've hit a wall!\n";
			return false;
		}

		/* if (tile == 'K') {
			cout << "\nYou've found a key!\n";
			player.addKey();
			grid[newRow][newCol] = '.'; //replaces item with empty space or .
			cout << "\n";
			player.printStats();
		} */

		if (tile == 'r') {
			cout << "Found RED key!\n";
			player.addKey("red");
			grid[newRow][newCol] = '.';
		}

		if (tile == 'R') {
			if (player.useKey("red")) {
				cout << "Unlocked RED door!\n";
				grid[newRow][newCol] = '.';
			}
			else {
				cout << "Need RED key!\n";
				return false;
			}
		}

		if (tile == 'b') {
			cout << "Found BLUE key!\n";
			player.addKey("blue");
			grid[newRow][newCol] = '.';
		}

		if (tile == 'B') {
			if (player.useKey("blue")) {
				cout << "Unlocked BLUE door!\n";
				grid[newRow][newCol] = '.';
			}
			else {
				cout << "Need BLUE key!\n";
				return false;
			}
		}

		/* if (tile == 'D') { //door
			if (player.useKey()) {
				cout << "\nYou've unlocked the door!\n";
				grid[newRow][newCol] = '.';
				cout << "\n";
				player.printStats();
			}
			else {
				cout << "\nYou need a key.\n";
				return false;
			}
		} */

		if (tile == 'H') {
			cout << "\nYou've found a health potion!\n";
			int heal = 5 + rand() % 11;
			player.addHealth(heal);
			cout << "Healed for " << heal << endl;
			grid[newRow][newCol] = '.';
			cout << "\n";
			player.printStats();
			//cout << "Your new health is: " << player.getHealth();
		}

		if (tile == 'S') {
			cout << "\nYou've found a strength potion!\n";
			int strength = 5 + rand() % 11;
			player.addStrength(strength);
			cout << "Strength added: " << strength << endl;
			grid[newRow][newCol] = '.';
			cout << "\n";
			player.printStats();
		}

		if (tile == 'F') {
			cout << "\nYou've found a defense potion!\n";
			int defense = 5 + rand() % 11;
			player.addDefense(defense);
			cout << "Added defense: " << defense << endl;
			grid[newRow][newCol] = '.';
			cout << "\n";
			player.printStats();
		}

		//tiles
		if (tile == 'L' || tile == 'T' || tile == 'P') {

			DamageTile* dmgTile;

			if (tile == 'L') {
				dmgTile = new Lava();
			}
			else if (tile == 'T') {
				 dmgTile = new Spikes();
			}
			else {
				dmgTile = new Poison();
			}

			cout << "\nYou stepped on " << dmgTile->getName() << "!";
			cout << " Took " << dmgTile->getDamage() << " damage!\n";

			player.takeDamage(dmgTile->getDamage());
		}

		if (tile == 'E') {
			cout << "\nAn enemy appeared! Your fight will now begin!\n";

			Enemy enemy(50 + rand() % 20, 10 + rand() % 5, 5 + rand() % 5);

			//fight 
			while (player.isAlive() && enemy.isAlive()) {

				//player attacks
				int dmgp = player.getStrength() - enemy.getDefense();
				if (dmgp <= 0) dmgp = 1; //prevent infinite loop

				enemy.takeDamage(dmgp);

				cout << "\nYou attack the enemy for " << dmgp << " damage.";
				cout << "\nEnemy health: " << enemy.getHealth() << endl;

				//check if enemy died
				if (!enemy.isAlive()) break;

				//enemy attacks
				int dmge = enemy.getStrength() - player.getDefense();
				if (dmge <= 0) dmge = 1;

				player.takeDamage(dmge);

				cout << "Enemy attacks you for " << dmge << " damage.";
				cout << "\nYour health: " << player.getHealth() << endl;
			}

			if (!player.isAlive()) {
				cout << "\nYou were defeated! The game will end.\n";
				return true; //end game
			}

			cout << "\nYou defeated the enemy! You may move on.\n";

			grid[newRow][newCol] = '.';
		}
		
		if (tile == 'G') {
			cout << "\nYou've reached the goal! You win!\n";
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
			"#b..H..G#",
			"#########"
			});

		levels.push_back({
			"########",
			"#G..#E.#",
			"#.#R#.r#",
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
	vector<string> dungeonNames;

public:
	
	Game() {
		dungeons = Dungeon::getPreDungeon();
		dungeonNames.push_back("Level 1");
		dungeonNames.push_back("Level 2");
	}

	void printLegend() {
			cout << "\n--- LEGEND ---\n";
			cout << "# = Wall\n";
			cout << ". = Empty\n";
			cout << "@ = Player\n";
			cout << "r = Red key\n";
			cout << "R = Red door\n";
			cout << "L = Lava\n";
			cout << "T = Spikes\n";
			cout << "P = Poison\n";
			cout << "H = Health Potion\n";
			cout << "S = Strength Potion\n";
			cout << "F = Defense Potion\n";
			cout << "E = Enemy\n";
			cout << "G = Goal\n\n";
	}

	//level editor

	void levelEditor() {
		int rows, cols;

		cout << "\n--- Level Editor ---\n";
		cout << "1. Create new dungeon\n";
		cout << "2. Edit existing dungeon\n\n";
		

		int mode;
		cin >> mode;

		vector<string> newGrid;
		bool editingExisting = false;
		int editIndex = -1;

		if (mode == 2 && !dungeons.empty()) {
			cout << "\nChoose a dungeon to edit:\n";
			for (int i = 0; i < dungeonNames.size(); i++) {
				cout << i + 1 << ") " << dungeonNames[i] << endl;
			}

			int choice;
			cin >> choice;

			if (choice < 1 || choice > dungeons.size()) {
				cout << "Invalid choice.\n";
				return;
			}

			newGrid = dungeons[choice - 1];
			rows = newGrid.size();
			cols = newGrid[0].size();

			editIndex = choice - 1;
			editingExisting = true;
		}
		else {

			//printLegend();

			cout << "Maximum size for dungeon is 10x10.\n";

			cout << "Enter rows (1-10): \n";
			while (!(cin >> rows) || rows < 1 || rows > 10) {
				cout << "Invalid. Enter 1-10: ";
				cin.clear();
				cin.ignore(10000, '\n');
			}

			cout << "Enter columns (1-10): \n";
			while (!(cin >> cols) || cols < 1 || cols > 10) {
				cout << "Invalid. Enter 1-10: ";
				cin.clear();
				cin.ignore(10000, '\n');
			}
			newGrid = vector<string>(rows, string(cols, '.'));
		}

		//vector<string> newGrid(rows, string(cols, '.'));

		bool editing = true;

		while (editing) {
			cout << "\nCurrent Dungeon looks like: \n";

			for (int r = 0; r < rows; r++) {
				for (int c = 0; c < cols; c++) {
					cout << newGrid[r][c];
				}
				cout << endl;
			}

			printLegend();

			cout << "\n1. Place object.\n";
			cout << "2. Save current dungeon. \n";
			cout << "Your choice: \n";

			int choice;
			while (!(cin >> choice) || (choice != 1 && choice != 2)) {
				cout << "Invalid choice. Enter 1 or 2: ";
				cin.clear();
				cin.ignore(10000, '\n');
			}

			if (choice == 1) {

				printLegend();

				cout << "\nEnter object character: ";
				char obj;
				cin >> obj;

				//validate only accepted objs are added
				if (obj != '#' && obj != '.' && obj != '@' &&
					obj != 'H' && obj != 'S' &&
					obj != 'F' && obj != 'E' &&
					obj != 'G' && obj != 'L' && 
					obj != 'T' && obj != 'P' &&
					obj != 'r' && obj != 'R' && 
					obj != 'b' && obj !='B') {

					cout << "Invalid object type.\n";
					continue; 
				}

				int r, c;

				cout << "Enter row (0-" << rows - 1 << "): ";
				while (!(cin >> r) || r < 0 || r >= rows) {
					cout << "Invalid row. Try again: ";
					cin.clear();
					cin.ignore(10000, '\n');
				}

				cout << "Enter col (0-" << cols - 1 << "): ";
				while (!(cin >> c) || c < 0 || c >= cols) {
					cout << "Invalid col. Try again: ";
					cin.clear();
					cin.ignore(10000, '\n');
				}

				newGrid[r][c] = obj;
			}
			else if (choice == 2) {

				if (editingExisting) {
					dungeons[editIndex] = newGrid;
					cout << "Dungeon updated!\n";
				}
				else {
					string name;
					cout << "Enter dungeon name: ";
					cin >> name;

					dungeons.push_back(newGrid);
					dungeonNames.push_back(name);

					cout << "Dungeon saved!\n";
				}

				editing = false;
			}
			else {
				cout << "Invalid choice.\n";
			}
		}
	
	}

	void run() {
		while (true) {
			cout << "\n---Welcome to the Magic Tower---\n";
			cout << "1) Enter a dungeon\n";
			cout << "2) Create a dungeon\n";
			cout << "3) Exit\n";

			string choice;
			cout << "Your choice: ";
			cin >> choice;

			for (char& c : choice) {
				c = tolower(c);
			}

			if (choice == "1" || choice == "enter" || choice == "one") {

				cout << "\nChoose a dungeon:\n";
				for (int i = 0; i < dungeons.size() && i < dungeonNames.size(); i++) {
					cout << i + 1 << ") " << dungeonNames[i] << endl;
				}

				string selection;
				cin >> selection;
				
				int input = -1;

				//dungeon name check
				for (int i = 0; i < dungeonNames.size(); i++) {
					if (selection == dungeonNames[i]) {
						input = i;
						break;
					}
				}

				//number check
				for (int i = 0; i < dungeons.size(); i++) {
					if (selection == to_string(i + 1)) {
						input = i;
						break;
					}
				}

				if (input == -1) {
					cout << "Invalid selection.\n";
					continue;
				}

				Player player;
				Dungeon dungeon(dungeons[input]);

				dungeon.findStart(player);
				printLegend();

				bool gameOver = false;

				while (!gameOver && player.isAlive()) {
					dungeon.print(player);

					string move; //take in words
					cout << "\nMove (W/A/S/D): ";
					cin >> move;

					char dir; //will sue to set strings to match directions
					for (char& c : move) {
						c = tolower(c);
					}

					//loops for movement
					if ( move == "up" || move == "w") {
						dir = 'U';
					}
					else if (move == "down" || move == "s") {
						dir = 'D';
					}
					else if ( move == "right" || move == "d") {
						dir = 'R';
					}
					else if ( move == "left" || move == "a") {
						dir = 'L';
					}
					else if (move == "quit" || move =="q") {
							cout << "Exiting dungeon...\n";
							break;
					}
					else if (move == "inspect") {
						int r, c;
						cout << "Enter row and col seperated by space: ";
						cin >> r >> c;

						char tile = dungeon.getTile(r, c);

						cout << "\n--- INSPECT ---\n";

						if (tile == '#') {
							cout << "Wall: cannot pass.\n";
						}
						else if (tile == '.') {
							cout << "Empty space.\n";
						}
						else if (tile == 'r') {
							cout << "Red key\n";
						}
						else if (tile == 'R') {
							cout << "Red door: needs red key.\n";
						}
						else if (tile == 'b') {
							cout << "Blue key\n";
						}
						else if (tile == 'B') {
							cout << "Blue door: needs blue key.\n";
						}
						else if (tile == 'H') {
							cout << "Health Potion: restores health.\n";
						}
						else if (tile == 'S') {
							cout << "Strength Potion: increases strength.\n";
						}
						else if (tile == 'F') {
							cout << "Defense Potion: increases defense.\n";
						}
						else if (tile == 'L') {
							cout << "Lava: deals 5 damage.\n";
						}
						else if (tile == 'T') {
							cout << "Spikes: deal 3 damage.\n";
						}
						else if (tile == 'P') {
							cout << "Poison: deals 2 damage.\n";
						}
						else if (tile == 'E') {
							cout << "Enemy:\n";
							cout << "HP: 50-70\n";
							cout << "Strength: 10-15\n";
							cout << "Defense: 5-10\n";
						}
						else if (tile == 'G') {
							cout << "Goal: reach this to win.\n";
						}
						else if (tile == '@') {
							cout << "Player start position.\n";
						}
						else {
							cout << "Unknown tile.\n";
						}

						cout << "---------------\n";
						continue;
					}
					else {
						cout << "Invalid move.\n";
						continue;
					}

					gameOver = dungeon.movePlayer(player, dir);
				}

				if (!player.isAlive()) {
					cout << "\nYou died. Game over.\n";
				}
			}

			else if (choice == "2" || choice == "create") {
				levelEditor();
			}

			else if (choice == "3" || choice == "exit") {
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