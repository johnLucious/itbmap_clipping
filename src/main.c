/**** Assignment - IF3260 Computer Graphics *****/
/* File		: main.c							*/
/* Create ITB map 2D (buildings, roads) and		*/
/* Clip objects into moving viewport			*/
/************************************************/

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <linux/fb.h>
#include <sys/mman.h>
#include <sys/ioctl.h>
#include <string.h>
#include <math.h>
#include <ncurses.h>

#define HEIGHT 500
#define WIDTH 800
#define INIT_HEIGHT 100
#define INIT_WIDTH 100

struct fb_var_screeninfo vinfo;
struct fb_fix_screeninfo finfo;

typedef struct{
    int x, y;
}point;

typedef struct{
    point point1; //koord. titik awal
    point point2; //koord. titik akhir
}line;



char *fbp = 0;
char bg[1000][1000];
int fbfd = 0;
long int screensize = 0;
long int location = 0;
long int nowHeight = 0;
long int nowWidth = 0;

line clipPoint;

const int INSIDE = 0;
const int LEFT = 1;
const int RIGHT = 2;
const int BOTTOM = 4;
const int TOP = 8;

//define const int x_max, y_max, x_min, y_min


void getPixelColor(int x, int y, int *rColor, int *gColor, int *bColor);
void printPixel(int x, int y, int colorR, int colorG, int colorB);
void drawLine(point p1, point p2, int thickness, int colorR, int colorG, int colorB);
void drawCircle(point center, int radius, int colorR, int colorG, int colorB);
void drawCircle(point center, int radius, int colorR, int colorG, int colorB);
void clearScreen();
void init();
void swap(int* a, int* b);
int computeCode(point p);
void cohenSutherlandClipping(point p1, point p2);
point setPoint(int x, int y);

int main() {
    init();   
    int i,j;
    initscr();
    clear();
    noecho();
    keypad(stdscr, TRUE);
    refresh();
    clearScreen();
	
    while(1){
		refresh();
		clearScreen();
		point p1 = setPoint(300,400);
		point p2 = setPoint(400,400);
		cohenSutherlandClipping(p1,p2);
		p1 = clipPoint.point1;
		p2 = clipPoint.point2;
		if (p1.x != -1 && p2.y != -1)
			drawLine(p1, p2, 1, 107, 91, 0);
        if (getch() == KEY_UP && nowHeight >= 10){
			nowHeight -= 10;
			clear();
		}
		else if (getch() == KEY_DOWN && nowHeight <= 220){
			nowHeight += 10;
			clear();
		}
		else if (getch() == KEY_LEFT && nowWidth >= 10){
			nowWidth -= 10;
			clear();
		}
		else if (getch() == KEY_RIGHT && nowWidth <= 400){
			nowWidth += 10;
			clear();
		}
		
    }
    
    munmap(fbp, screensize);
    close(fbfd);
    return 0;
}

void swap(int* a, int* b){
    int temp = *a;
    *a = *b;
    *b = temp;
}

point setPoint(int x, int y){
    point p;
    p.x = x;
    p.y = y;

    return p;
}

void init(){
    fbfd = open("/dev/fb0", O_RDWR);
    if (fbfd == -1) {
        perror("Error: cannot open framebuffer device");
        exit(1);
    }
    printf("The framebuffer device was opened successfully.\n");

    // Get fixed screen information
    if (ioctl(fbfd, FBIOGET_FSCREENINFO, &finfo) == -1) {
        perror("Error reading fixed information");
        exit(2);
    }

    // Get variable screen information
    if (ioctl(fbfd, FBIOGET_VSCREENINFO, &vinfo) == -1) {
        perror("Error reading variable information");
        exit(3);
    }

    printf("%dx%d, %dbpp\n", vinfo.xres, vinfo.yres, vinfo.bits_per_pixel);

    // Figure out the size of the screen in bytes
    screensize = vinfo.xres * vinfo.yres * vinfo.bits_per_pixel / 8;

    // Map the device to memory
    fbp = (char *)mmap(0, screensize, PROT_READ | PROT_WRITE, MAP_SHARED, fbfd, 0);
    if ((int)fbp == -1) {
        perror("Error: failed to map framebuffer device to memory");
        exit(4);
    }
    printf("The framebuffer device was mapped to memory successfully.\n");

}

void clearScreen(){
    for (int h = nowHeight; h < HEIGHT + nowHeight; h++){
        for (int w = nowWidth; w < WIDTH + nowWidth; w++) {
			printPixel(w,h,122,224,255);
        }
    }
}

void getPixelColor(int x, int y, int *rColor, int *gColor, int *bColor) {
      location = (x+vinfo.xoffset) * (vinfo.bits_per_pixel/8) +
                       (y+vinfo.yoffset) * finfo.line_length;
                       
            *bColor = *(fbp+location);
            *gColor = *(fbp+location+1);
            *rColor = *(fbp+location+2);
}

void printPixel(int x, int y, int colorR, int colorG, int colorB){	//Print Pixel Color using RGB
    location = (x+vinfo.xoffset) * (vinfo.bits_per_pixel/8) +
                       (y+vinfo.yoffset) * finfo.line_length;

    if (vinfo.bits_per_pixel == 32) {
        *(fbp + location)     = colorB;		//Blue Color
        *(fbp + location + 1) = colorG;		//Green Color
        *(fbp + location + 2) = colorR;		//Red Color
        *(fbp + location + 3) = 0;			//Transparancy
    }
}

void drawLine(point p1, point p2, int thickness, int colorR, int colorG, int colorB){//Bresenham
    int x1 = p1.x, y1 = p1.y, x2 = p2.x, y2 = p2.y;
    int steep = 0;
    if(abs(x1-x2) < abs(y1-y2)){
        swap(&x1, &y1);
        swap(&x2, &y2);
        steep = 1;
    }
    if(x1 > x2){
        swap(&x1,&x2);
        swap(&y1,&y2);
    }
    int dx = x2-x1;
    int dy = y2-y1;
    int derr = 2 * abs(dy);
    int err = 0;
    int y = y1;
    for(int x = x1; x <= x2; x++){
        if(steep){
            printPixel(y,x,colorR,colorG,colorB);
        }else{
            printPixel(x,y,colorR,colorG,colorB);
        }
        err+=derr;
        if(err > dx){
            y += (y2>y1)?1:-1;
            err -= 2 * dx;
        }
    }
}

void drawCircle(point center, int radius, int colorR, int colorG, int colorB){//Mid Point Algo
    int x = radius, y = 0;
    printPixel(x + center.x, y + center.y, colorR, colorG, colorB);
    if(radius > 0){
        printPixel(-x + center.x, y + center.y, colorR, colorG, colorB);
        printPixel(y + center.x, x + center.y, colorR, colorG, colorB);
        printPixel(y + center.x, -x + center.y, colorR, colorG, colorB);      
    }
    
    int P = 1 - radius;
    while(x > y){
        y++;
        if(P <= 0){
            P = P + 2*y + 1;
        }else{
            x--;
            P = P + 2*y - 2*x + 1;
        }

        if(x < y){ break; }
        printPixel(x + center.x, y + center.y, colorR, colorG, colorB);
        printPixel(-x + center.x, y + center.y, colorR, colorG, colorB);
        printPixel(x + center.x, -y + center.y, colorR, colorG, colorB);
        printPixel(-x + center.x, -y + center.y, colorR, colorG, colorB); 

        if(x != y){
            printPixel(y + center.x, x + center.y, colorR, colorG, colorB);
            printPixel(-y + center.x, x + center.y, colorR, colorG, colorB);
            printPixel(y + center.x, -x + center.y, colorR, colorG, colorB);
            printPixel(-y + center.x, -x + center.y, colorR, colorG, colorB); 

        }
    }
}

int computeCode(point p){
	int x_min = nowWidth;
	int y_min = HEIGHT + nowHeight;
	int x_max = WIDTH + nowWidth;
	int y_max = nowHeight;
	
    int x = p.x;
    int y = p.y;
    int code = INSIDE;
    if(x<x_min){code |= LEFT;}
    else if(x>x_max){code |= RIGHT;}

    if(y>y_min){code |= BOTTOM;}
    else if(y<y_max){code|=TOP;}

    return code;
}

void cohenSutherlandClipping(point p1, point p2){
	int x_min = nowWidth;
	int y_min = HEIGHT + nowHeight;
	int x_max = WIDTH + nowWidth;
	int y_max = nowHeight;
	
    double x1 = p1.x, y1 = p1.y;
    double x2 = p2.x, y2 = p2.y;
    int code1 = computeCode(p1);
    int code2 = computeCode(p2);

    int isDrawn = 0;
    while(1){
        if((code1==0) && (code2==0)){ //2 endline di dlm rectangle yang akan digambar
            isDrawn = 1;
            break;
        }else if(code1 & code2){//clipPoint dan tidak 0, tidak digambar
            //bikin point -1
            point p1; p1.x = -1; p1.y = -1;
            point p2; p2.x = -1; p2.y = -1;
            clipPoint.point1 = p1;
            clipPoint.point2 = p2;
            break;
        }else{
            //harus diclip sebagian dari garis
            int code_out;
            double x,y;
            //ambil code yang di luar rectangle
            if(code1!=0){code_out = code1;}
            else{code_out = code2;}

            //find intersection point
            if(code_out&TOP){//point di atas rectangle
                x = x1+(x2-x1)*(y_max - y1) / (y2-y1);
                y = y_max;
            }else if(code_out & BOTTOM){//point di bawah rectangle
                x = x1 + (x2-x1)*(y_min-y1) / (y2-y1);
                y = y_min;
            }else if(code_out & RIGHT){
                y = y1 + (y2-y1) * (x_max-x1) / (x2-x1);
                x = x_max;
            }else if(code_out & LEFT){
                y = y1 + (y2-y1) * (x_min-x1) / (x2-x1);
                x = x_min;
            }

            //replace point outsite rectable dengan point yang di border
            if(code_out == code1){
                x1 = x;
                y1 = y;
                code1 = computeCode(p1);
            }else{
                x2 = x;
                y2 = y;
                code2 = computeCode(p2);
            }
            isDrawn = 1;
            break;
        }
    }
    if(isDrawn){
        point p1; p1.x = x1; p1.y = y1;
        point p2; p2.x = x2; p2.y = y2;
        clipPoint.point1 = p1;
        clipPoint.point2 = p2;
    }
}
