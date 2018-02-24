#ifndef _POHON_
#define _POHON_

#include<applib>

class Pohon : public Renderable {

	public:
		std::vector<Pohon> parseFile(std::string filename);
};

#endif