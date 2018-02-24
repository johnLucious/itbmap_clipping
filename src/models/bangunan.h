#ifndef _BANGUNAN_
#define _BANGUNAN_

#include<applib>

class Bangunan : public Renderable {

	public:
		std::vector<Bangunan> parseFile(std::string filename);
};

#endif