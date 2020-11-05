#include "Position.h"

Position::Position()
{
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


