
#include "Position.h"
#include <include/glm.h>

class Arrow {
public:
	Arrow();
	Arrow(Position, float);
	~Arrow();

	// default
	Position origin_position = Position();
	float angle;

	// dynamic
	int distance_from_origin = 0;
	Position pos = Position();
	glm::mat3 modelMatrix = glm::mat3(1);
	bool isOutOfScreen = true;


	// change position coordinates
	void updatePosition();

	// move and change position coordinates
	void moveAndUpdatePosition();

	bool checkIfOutOfScreen();

	// mark an arrow as being out of screen
	void setArrowOutOfScreen();


};