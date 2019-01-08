/* ******************************************************
 * Name: Jasper Nelson
 * Wisc ID: 9073545106
 * OS: MAC
 * IDE (or text editor): Eclipse
 * Compiler: Eclipse
 * How long did the assignment take you to complete in minutes: 300
 * What other resources did you consult (copy and paste links below):
 * cplusplus.com
 * stackoverflow.com
*/ //******************************************************
#ifndef PLAYER_H_
#define PLAYER_H_

#include <iostream>
#include <map>
#include <vector>
#include <set>
#include <string>
#include <time.h>
#include "CAVE.h"

using namespace std;

class PLAYER
{
	vector<int> position;
	vector<bool> facing;
	vector<int> next_Square;
	bool arrow;
	bool gold;

	enum STATUS
	{
		ALIVE, EATEN, FELL, ESCAPED
	};

	STATUS player_status;

public:

	PLAYER();
	~PLAYER();
	vector<int> Get_Position();
	string Get_Facing();
	void Turn_Left();
	void Turn_Right();
	vector<int> Get_Next_Square();
	void Move_Forward();
	bool Pickup_Gold(CAVE &cave);
	bool Shoot_Arrow(CAVE &cave);
	void Climb_Ladder();
	bool Has_Arrow();
	bool Has_Gold();
	bool Update_Player_Status(CAVE &cave);
	bool Escaped();
	bool Eaten();
	bool Fell();

};

#endif /* PLAYER_H_ */
