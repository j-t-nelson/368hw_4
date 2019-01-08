#ifndef CAVE_H_
#define CAVE_H_

#include <iostream>
#include <map>
#include <vector>
#include <set>
#include <string>
#include <time.h>

using namespace std;

class CAVE {
	map<vector<int>, set<string> > cave_map;
	vector<string> cave_diagram;

	enum STATUS {
		ALIVE, DEAD
	};
	STATUS wumpus_status;

public:
	CAVE();
	~CAVE();
	vector<int> Get_A_Random_Square();
	bool Is_Square_Valid(const vector<int> &square);
	void Print_Cave_Diagram();
	void Initialize_Cave_Map();
	void Initialize_Cave_Diagram();
	void Print_Square(const vector<int> &rc);
	bool Remove_Gold(const vector<int> &rc);
	bool Square_Contains_Living_Wumpus(const vector<int> &rc);
	bool Square_Contains_Pit(const vector<int> &rc);
	bool Square_Contains_Gold(const vector<int> &rc);
	bool Square_Contains_Ladder(const vector<int> &rc);
	bool Shoot_Square(const vector<int> &rc);
	bool Is_Wumpus_Alive();
};
#endif
