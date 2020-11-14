#include "Position.h"

Position::Position()
{
	x = 0;
	y = 0;
}

Position::Position(int xx, int yy)
{
	x = xx;
	y = yy;
}

Position::~Position()
{
}

void Position::setValue(int cx, int cy)
{
	x = cx;
	y = cy;
}


