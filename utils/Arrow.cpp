#include "Arrow.h"
#include "../Transform2D.h"
#include "../Defines.h"

Arrow::Arrow() {
	isOutOfScreen = true;
}

Arrow::Arrow(Position pos, float an) {
	isOutOfScreen = false;
	origin_position = pos;
	angle = an;
}

Arrow::~Arrow()
{
}


bool Arrow::checkIfOutOfScreen() {

	if (pos.x > init_window_width ||
		pos.y > (init_window_height - init_scoreboard_height - init_powerbar_height) + init_powerbar_height ||
		pos.y < init_powerbar_height) {
		return true;
	}
	return false;
}

void Arrow::setArrowOutOfScreen() {
	isOutOfScreen = true;
	origin_position = Position(-100, -100);
}


void Arrow::updatePosition() {
	pos.x = origin_position.x + distance_from_origin * cos(angle);
	pos.y = origin_position.y + distance_from_origin * sin(angle);
}
void Arrow::moveAndUpdatePosition() {
	distance_from_origin = distance_from_origin + arrow_x_step;
	updatePosition();
}

