#include "Position.h"
#include "../Defines.h"

class Shuriken
{
public:
	Shuriken();
	~Shuriken();

	Position pos = Position(init_window_width + 3 * init_player_height, init_window_height);
	bool isOutOfScreen = true;
	int degrees = 0;

	bool checkIfHitPlayer(Position);
	void resetCoordinates(Position);
	void moveShuriken();
	void spinShuriken();
	bool checkIfOutOfTheScreen();
};
