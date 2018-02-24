#ifndef _LAYOUT_MANAGER_
#define _LAYOUT_MANAGER_
#include <applib>

class LayoutManager {
	private:
		int height;
		int width; 
		int background_color;
	public: 
		LayoutManager() {
			std::cout << "HELLO" << std::endl;
		}	
};

#endif