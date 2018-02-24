#ifndef _JALAN_
#define _JALAN_

#include<applib>

class Jalan : public Renderable {

	public:
		std::vector<Jalan> parseFile(std::string filename);
};

#endif