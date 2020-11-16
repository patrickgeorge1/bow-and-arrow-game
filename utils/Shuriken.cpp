#include <math.h>
#include "Shuriken.h"


Shuriken::Shuriken()
{
}

Shuriken::~Shuriken()
{
}


bool Shuriken::checkIfHitPlayer(Position player_position) {
	int player_x = player_position.x;
	int player_y = player_position.y + init_player_height / 2;

	int x_displacement = player_x - pos.x;
	int y_displacement = player_y - pos.y;
	int sq_x = x_displacement * x_displacement;
	int sq_y = y_displacement * y_displacement;
	
	int c1 = init_player_height / 2.5f;
	int c2 = init_player_height / 2.5f;
	float ip = sqrt(c1 * c1 + c2 * c2);


	float distance = sqrt(sq_x + sq_y);
	float min_dist_threshold = ip + (init_player_height / 2);

	return (distance <= min_dist_threshold);
}

void Shuriken::resetCoordinates(Position p)
{
	pos.x = p.x;
	pos.y = p.y;
}

void Shuriken::moveShuriken()
{
	pos.x -= shuriken_x_step;
}

void Shuriken::spinShuriken()
{
	degrees++;
	degrees %= 360;
}

bool Shuriken::checkIfOutOfTheScreen()
{
	return (pos.x <= 0);
}
