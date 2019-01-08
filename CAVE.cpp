#include "CAVE.h"

CAVE::CAVE() :
		wumpus_status(ALIVE) {
	srand(time(NULL));
	Initialize_Cave_Map();
	Initialize_Cave_Diagram();
}

CAVE::~CAVE() {
}

vector<int> CAVE::Get_A_Random_Square() {
	return vector<int> { rand() % 4 + 1, rand() % 4 + 1 };
}

bool CAVE::Is_Square_Valid(const vector<int> &square) {
	for (auto e : square)
		if (e < 1 || e > 4)
			return false;
	return true;
}

void CAVE::Initialize_Cave_Map() {
	vector<int> ladder { 1, 1 }; // row column
	cave_map[ladder].insert("ladder");

	set<vector<int> > forbidden_squares;
	forbidden_squares.insert(ladder);

	vector<int> wumpus = Get_A_Random_Square();
	while (forbidden_squares.count(wumpus))
		wumpus = Get_A_Random_Square();
	cave_map[wumpus].insert("wumpus");
	forbidden_squares.insert(wumpus);

	set<vector<int> > pit_squares;
	for (int i = 0; i < 3; i++) {
		vector<int> pit = Get_A_Random_Square();
		while (forbidden_squares.count(pit))
			pit = Get_A_Random_Square();
		cave_map[pit].insert("pit");
		forbidden_squares.insert(pit);
		pit_squares.insert(pit);
	}

	forbidden_squares.erase(wumpus);
	vector<int> gold = Get_A_Random_Square();
	while (forbidden_squares.count(gold))
		gold = Get_A_Random_Square();
	cave_map[gold].insert("gold");

	vector<vector<int> > lrud { vector<int> { -1, 0 }, vector<int> { 1, 0 },
			vector<int> { 0, -1 }, vector<int> { 0, 1 } };
	for (auto &v : lrud) {
		vector<int> p { wumpus[0] + v[0], wumpus[1] + v[1] };
		if (Is_Square_Valid(p)) {
			cave_map[p].insert("stench");
		}
	}

	for (auto & pit : pit_squares) {
		for (auto &v : lrud) {
			vector<int> p { pit[0] + v[0], pit[1] + v[1] };
			if (Is_Square_Valid(p)) {
				cave_map[p].insert("breeze");
			}
		}
	}
}

void CAVE::Print_Square(const vector<int> &rc) {
	cout << "This part of the cave contains" << endl;
	if (cave_map[rc].empty()) {
		cout << "    nothing" << endl;
		return;
	}
	for (auto &s : cave_map[rc])
		cout << "    " << s << endl;
}

void CAVE::Initialize_Cave_Diagram() {
	cave_diagram.clear();
	int cell_rows = 5;
	int cell_columns = 11;
	int total_rows = cell_rows * 4 + 1;
	int total_columns = cell_columns * 4 + 1;

	for (int r = 0; r < total_rows; r++) {
		string row(total_columns, ' ');
		for (int c = 0; c < total_columns; c += cell_columns) {
			row[c] = '|';
		}
		cave_diagram.push_back(row);
	}

	for (int i = 0; i < total_rows; i += cell_rows) {
		cave_diagram[i] = string(total_columns, '-');
	}

	for (int r = 0; r < total_rows; r += cell_rows) {
		for (int c = 0; c < total_columns; c += cell_columns) {
			cave_diagram[r][c] = '+';
		}
	}

	for (auto c : cave_map) {
		const vector<int> &v = c.first;
		const set<string> &s = c.second;
		int row = 1 + cell_rows * (v[0] - 1);
		int col = 3 + cell_columns * (v[1] - 1);
		for (auto &e : s) {
			cave_diagram[row++].replace(col, e.length(), e);
		}
	}
}

void CAVE::Print_Cave_Diagram() {
	for (auto s : cave_diagram)
		cout << s << endl;
}

bool CAVE::Remove_Gold(const vector<int> &rc) {
	if (!Is_Square_Valid(rc))
		return false;
	cout << cave_map[rc].count("gold")<<endl;
	if (cave_map[rc].count("gold")) {
		cave_map[rc].erase("gold");
		Initialize_Cave_Diagram();
		return true;
	} else
		return false;
}

bool CAVE::Square_Contains_Living_Wumpus(const vector<int> &rc) {
	if (wumpus_status == DEAD)
		return false;
	if (!Is_Square_Valid(rc))
		return false;
	if (cave_map[rc].count("wumpus"))
		return true;
	return false;
}

bool CAVE::Square_Contains_Pit(const vector<int> &rc) {
	if (!Is_Square_Valid(rc))
		return false;
	if (cave_map[rc].count("pit"))
		return true;
	return false;
}

bool CAVE::Square_Contains_Gold(const vector<int> &rc) {
	if (!Is_Square_Valid(rc))
		return false;
	if (cave_map[rc].count("gold"))
		return true;
	return false;
}

bool CAVE::Square_Contains_Ladder(const vector<int> &rc) {
	if (!Is_Square_Valid(rc))
		return false;
	if (cave_map[rc].count("ladder"))
		return true;
	return false;
}

bool CAVE::Shoot_Square(const vector<int> &rc) {
	if (!Square_Contains_Living_Wumpus(rc))
		return false;
	wumpus_status = DEAD;
	return true;
}

bool CAVE::Is_Wumpus_Alive() {
	if (wumpus_status == ALIVE)
		return true;
	return false;
}

