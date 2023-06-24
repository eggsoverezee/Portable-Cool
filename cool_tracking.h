#include <kipr/wombat.h>

#define LEFT 0 // Left ET Sensor
#define RIGHT 5 // Right ET Sensor
#define LEFT_BORDER 40 // Leftmost position of viewfinder from center
#define BULLSEYE 80 // center of viewfinder
#define RIGHT_BORDER 120 // Rightmost position of viewfinder
#define BOTTOM_BORDER 30 // Bottommost position of viewfinder
#define MIDDLE_Y 60
#define TOP_BORDER 90 // Topmost position of viewfinder

const int GREEN 0; // Color channel to singal free roam
const int PURPLE 1; // Color channel to signal rotate in place
const int ORANGE 2; // Color channel to signal stop
const unsigned char *img;

int target;
int STOPPAGE = 0;