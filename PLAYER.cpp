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
#include "PLAYER.h"

/*
 * purpose: constructor
 * parameters: N/A
 * returns: creates an instance of the Player Object
 */
PLAYER::PLAYER() :
	player_status(ALIVE)
{
	position = {1,1};
	facing = {false, true, false, false};
	next_Square = {1,2};
	arrow = true;
	gold = false;
}

/*
 * purpose: destructor
 * parameters: N/A
 * returns: destroys an instance of the Player Object
 */
PLAYER::~PLAYER() {}

vector<int> PLAYER::Get_Position()
{
	return position;
}

/*
 * purpose: tells the user and program which way the player is currently facing
 * parameters: N/A
 * returns: a string object with the direction
 */
string PLAYER::Get_Facing()
{
	if(facing[0]) return "up";
	if(facing[1]) return "right";
	if(facing[2]) return "down";
	if(facing[3]) return "left";

	return "algo not working";
}

/*
 * purpose: turns the player 1 direction to the left
 * parameters: N/A
 * returns: N/A
 */
void PLAYER::Turn_Left()
{
	if(facing[0])
	{
		facing[0] = false;
		facing[3] = true;
		next_Square = this->Get_Next_Square();
		return;
	}

	for(int i = 1; i < 4; i++)
	{
		if(facing[i])
		{
			facing[i] = false;
			facing[i-1] = true;
			break;
		}
	}
	next_Square = this->Get_Next_Square();
	return;
}

/*
 * purpose: turns the player one direction to the right
 * parameters: N/A
 * returns: N/A
 */
void PLAYER::Turn_Right()
{
	if(facing[3])
	{
		facing[3] = false;
		facing[0] = true;
		next_Square = this->Get_Next_Square();
		return;
	}
	for(int i = 0; i < 3; i++)
	{
		if(facing[i])
		{
			facing[i] = false;
			facing[i+1] = true;
			break;
		}
	}
	next_Square = this->Get_Next_Square();
	return;
}

/*
 * purpose: to get the next square based on which way the player is facing and it's current direction
 * parameters: N/A
 * returns: the vector of int with the coordinates of the next square
 */
vector<int> PLAYER::Get_Next_Square()
{
	string dir = this->Get_Facing();
	char looking = dir[0];
	vector<int> pos = this->position;
	vector<int> ret;
	int row = pos[0];
	int col = pos[1];

	switch(looking)
	{
		case 'u':
			row -= 1;
			ret = {row, col};
			return ret;

		case 'r':
			col += 1;
			ret = {row, col};
			return ret;

		case 'd':
			row += 1;
			ret = {row, col};
			return ret;

		case 'l':
			col -= 1;
			ret = {row, col};
			return ret;
	}
	return pos;
}

/*
 * purpose: moves the player into the square designated as next
 * parameters: N/A
 * returns: N/A
 */
void PLAYER::Move_Forward()
{
	position = this->Get_Next_Square();

	return;
}

/*
 * purpose: removes gold from the cave when a player is standing in the correct square
 * parameters: a reference to the map of the cave
 * returns: true if the gold is successfully picked up, else otherwise
 */
bool PLAYER::Pickup_Gold(CAVE &cave)
{
	if(cave.Square_Contains_Gold(position))
	{
		cave.Remove_Gold(position);
		gold = true;
	}
	return gold;
}

/*
 * purpose: shoots the player's arrow and records if the wumpus is hit or not
 * parameters: a reference to the map of the cave
 * returns: true if the wumpus is hit and you have an arrow, else otherwise
 */
bool PLAYER::Shoot_Arrow(CAVE &cave)
{
	if(!arrow) return false;

	arrow = false;
	string dir = this->Get_Facing();
	char looking = dir[0];
	int row, col;
	bool shot = false;
	vector<int> next;


	switch(looking)
	{
		case 'u':
			next = next_Square;
			while(row > 0)
			{
				row = next[0];
				col = next[1];
				shot = cave.Shoot_Square(next);
				if(shot) break;
				else
				{
					next = {row - 1, col};
				}
			}
			return shot;

		case 'r':
			next = next_Square;
			while(col < 5)
			{
				row = next[0];
				col = next[1];
				shot = cave.Shoot_Square(next);
				if(shot) break;
				else
				{
					next = {row, col + 1};
				}
			}
			return shot;


		case 'd':
			next = next_Square;
			while(row < 5)
			{
				row = next[0];
				col = next[1];
				shot = cave.Shoot_Square(next);
				if(shot) break;
				else
				{
					next = {row + 1, col};
				}
			}
			return shot;

		case 'l':
			next = next_Square;
			while(col > 0)
			{
				row = next[0];
				col = next[1];
				shot = cave.Shoot_Square(next);
				if(shot) break;
				else
				{
					next = {row, col - 1};
				}
			}
			return shot;
	}

	return false;
}

/*
 * purpose: changes the player status to escaped and ends the level
 * parameters: N/A
 * returns: N/A
 */
void PLAYER::Climb_Ladder()
{
	player_status = ESCAPED;
	return;
}

/*
 * purpose: access to the arrow field of player
 * parameters: N/A
 * returns: true if the player has an arrow, false otherwise
 */
bool PLAYER::Has_Arrow()
{
	return arrow;
}

/*
 * purpose: access to the gold field of player
 * parameters: N/A
 * returns: true if the player has a gold, false otherwise
 */
bool PLAYER::Has_Gold()
{
	return gold;
}

/*
 * purpose: updates the status of the player given position and the position of the pits
 * and the wumpus
 * parameters: a reference to the map of the cave
 * returns: true if the player is alive, false otherwise
 */
bool PLAYER::Update_Player_Status(CAVE &cave)
{
	if(cave.Square_Contains_Living_Wumpus(position))
		{
			player_status = EATEN;
			return false;
		}
	if(cave.Square_Contains_Pit(position))
		{
			player_status = FELL;
			return false;
		}
	return true;
}

/*
 * purpose: access to the player_status field of player
 * parameters: N/A
 * returns: true if the player has Escaped, false otherwise
 */
bool PLAYER::Escaped()
{
	if(player_status == ESCAPED) return true;
	else return false;
}

/*
 * purpose: access to the player_status field of player
 * parameters: N/A
 * returns: true if the player has been Eaten, false otherwise
 */
bool PLAYER::Eaten()
{
	if(player_status == EATEN) return true;
	else return false;
}

/*
 * purpose: access to the player_status field of player
 * parameters: N/A
 * returns: true if the player has Fallen into a pit, false otherwise
 */
bool PLAYER::Fell()
{
	if(player_status == FELL) return true;
	else return false;
}
