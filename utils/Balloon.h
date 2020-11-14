#include "Position.h"

class Balloon
{
public:
	Balloon();
	Balloon(Position);
	~Balloon();

	Position position = Position();
	bool wasHit = false;
	bool isOutOfScreen = true;
	bool isRed = false;
	 
	void climbUp();
	bool isOutOfScreenCheck();
	void setOutOfScreen();
	void resetPosition(int);
};

