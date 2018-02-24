#ifndef _FBDRIVER_
#define _FBDRIVER_
#include <applib>

class Driver {
	public:
		struct fb_var_screeninfo vinfo;
		struct fb_fix_screeninfo finfo;
		char *fbp;
		int fbfd;
		long int screensize;
		long int location;

		Driver();
		void init();
		void initCaptureKeyboard();
};

#endif