#include <iostream>
#include <string>
#include <map>

#include "CAVE.h"
#include "PLAYER.h"
#include "PLAYER.h"

using namespace std;

int main() {
	enum GAME_STATUS {
		BEGIN, QUITTER, END
	};
	enum INPUT_OPTION {
		INVALID, QUIT, MOVE, LEFT, RIGHT, SHOOT, PICKUP, CLIMB, MAP, POSITION
	};
	map<char, INPUT_OPTION> char_to_input;
	char_to_input['q'] = QUIT;
	char_to_input['m'] = MOVE;
	char_to_input['l'] = LEFT;
	char_to_input['r'] = RIGHT;
	char_to_input['s'] = SHOOT;
	char_to_input['p'] = PICKUP;
	char_to_input['c'] = CLIMB;
	char_to_input['z'] = MAP;
	char_to_input['x'] = POSITION;

	CAVE cave;
	PLAYER player;
	int turn_counter = 0;
	GAME_STATUS game_status = BEGIN;

	while (game_status == BEGIN) {
		// print the turn message
		cout << "Turn " << ++turn_counter << ". ";
		cave.Print_Square(player.Get_Position());
		cout
				<< "(q)uit, (m)ove forward, (l)eft, (r)ight, (s)hoot, (p)ickup gold, (c)limb ladder, (z)display map, (x)print player position and facing"
				<< endl;
		cout << "Enter your choice: ";

		// read the whole line but just use the first character
		string line;
		getline(cin, line);
		cout << endl;
		char c = *line.begin();
		INPUT_OPTION choice = INVALID;
		if (char_to_input.count(c))
			choice = char_to_input[c];

		// perform player action
		switch (choice) {
		case QUIT: {
			game_status = QUITTER;
		}
			break;
		case MAP: {
			cave.Print_Cave_Diagram();
		}
			break;
		case POSITION: {
			vector<int> position = player.Get_Position();
			string direction = player.Get_Facing();
			cout << "You are in square (" << position[0] << "," << position[1]
					<< ") facing " << direction << endl;
		}
			break;
		case LEFT: {
			player.Turn_Left();
		}
			break;
		case RIGHT: {
			player.Turn_Right();
		}
			break;
		case MOVE: {
			vector<int> next_square = player.Get_Next_Square();
			bool valid = cave.Is_Square_Valid(next_square);
			if (valid) {
				player.Move_Forward();
				cout << "You step forward into the next square!" << endl;
			} else
				cout << "Bump! You have walked into a wall!" << endl;

		}
			break;
		case SHOOT: {
			if (player.Has_Arrow()) {
				bool wumpus_killed = player.Shoot_Arrow(cave);
				if (wumpus_killed)
					cout << "You hear a terrible scream!" << endl;
				else
					cout << "The arrow missed the wumpus!" << endl;
			} else
				cout << "You don't have another arrow!" << endl;
		}
			break;
		case PICKUP: {
			if (player.Pickup_Gold(cave))
				cout << "You have picked up a piece of gold!" << endl;
			else
				cout << "There isn't any gold here!" << endl;
		}
			break;
		case CLIMB: {
			if (cave.Square_Contains_Ladder(player.Get_Position()))
				player.Climb_Ladder();
			else
				cout << "There isn't a ladder here!" << endl;
		}
			break;
		case INVALID: // fall through to default
		default:
			cout << "Invalid choice" << endl;
		}

		// update character status
		bool still_alive = player.Update_Player_Status(cave);
		if (still_alive == false)
			game_status = END;
		if (player.Escaped())
			game_status = END;

	} // end of game while loop

// compute the player score
	if (game_status == QUITTER) {
		cout << endl
				<< "   ### GAME OVER ###\n   You have decided to quit.\n   Your final score is 0."
				<< endl;
		return 0;
	}
	if (player.Eaten()) {
		cout << endl
				<< "   ### GAME OVER ###\n   You were eaten by the wumpus.\n   Your final score is 0."
				<< endl;
		return 0;
	}
	if (player.Fell()) {
		cout << endl
				<< "   ### GAME OVER ###\n   You fell into a pit.\n   Your final score is 0."
				<< endl;
		return 0;
	}

	int score = 0;
	if (player.Has_Gold())
		score += 10;
	if (player.Has_Arrow() == false)
		score -= 5;
	if (cave.Is_Wumpus_Alive() == false)
		score += 5;
	if (player.Escaped() == false)
		score = 0;

	cout << endl << endl;
	cout << endl << "   ### GAME OVER ###\n   Your final score is " << score
			<< "." << endl;
	if (player.Has_Gold())
		cout << "   You have found the gold!" << endl;
	else
		cout << "   You have escaped with your life!" << endl;
	if (cave.Is_Wumpus_Alive() == false)
		cout << "   You have killed the wumpus" << endl;

	return 0;

}

