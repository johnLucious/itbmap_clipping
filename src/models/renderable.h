#ifndef _RENDERABLE_
#define _RENDERABLE_

#include <applib>

class Renderable {
	private:
		std::vector<Point> points;
		int color_r;
		int color_g;
		int color_b;

	public:
		std::vector<Point> getPoints();
};

#endif