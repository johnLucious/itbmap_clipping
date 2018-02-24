#ifndef _RENDERABLE_
#define _RENDERABLE_

#include <applib>

class Renderable {
	private:
		std::vector<Point> points;
		std::unordered_map<int, std::unordered_map<int, bool> > pixels;
		int color_r;
		int color_g;
		int color_b;

	public:
		std::vector<Point>& getPoints();
        void setPoints(std::vector<Point>& _points){
            points = _points;
        }
        const std::unordered_map<int, std::unordered_map<int, bool> >& getPixels();
        static std::vector<Renderable *> parseFile(std::string filename);
		/*
		 * Generate borders in pixels
		 */
		void createBorder();
		/*
		 * Rastering color in pixels
		 */
		void rasterColor();
};

#endif