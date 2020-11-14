#ifndef Position_HEADER
#define Position_HEADER

class Position {
	public:
		Position();
		Position(int, int);
		~Position();

		void setValue(int, int);

		int x;
		int y;
};

#endif