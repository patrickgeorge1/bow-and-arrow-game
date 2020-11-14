#include "Balloon.h"
#include "../Defines.h"
#include <iostream>

Balloon::Balloon()
{
}

Balloon::Balloon(Position p)
{
	position.x = p.x;
	position.y = p.y;
}

Balloon::~Balloon()
{
}

void Balloon::climbUp()
{
	position.y += balloon_y_step;
}

bool Balloon::isOutOfScreenCheck()
{
	if (position.y > (init_window_height - init_scoreboard_height - init_powerbar_height) + init_powerbar_height) return true;
	return false;
}

void Balloon::setOutOfScreen() {
	isOutOfScreen = true;
}

void Balloon::resetPosition(int randNum) {
	position.y = 0;
	position.x = randNum;
}