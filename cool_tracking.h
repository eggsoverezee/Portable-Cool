
#define LEFT 0 // Left ET Sensor
#define RIGHT 5 // Right ET Sensor
#define LEFT_BORDER 40 // Leftmost position of viewfinder from center
#define BULLSEYE 80 // center of viewfinder
#define RIGHT_BORDER 120 // Rightmost position of viewfinder
#define BOTTOM_BORDER 30 // Bottommost position of viewfinder
#define TOP_BORDER 90 // Topmost position of viewfinder
#define GREEN 0 // Color channel to signal free roam
#define PURPLE 1 // Color channel to signal rotate in place
#define ORANGE 2 // Color channel to signal stop

void recon_mode();
void sentry_mode();
void camOps();
void driveOps();
