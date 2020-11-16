#include "Position.h"
#include "../Defines.h"

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
	float scale = balloon_default_scale;
	 
	void climbUp();
	bool isOutOfScreenCheck();
	void setOutOfScreen();
	void resetPosition(int);
};

