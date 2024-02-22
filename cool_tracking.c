#include <cool_tracking.h>

const int GREEN = 0; // Color channel to singal free roam
const int PURPLE = 1; // Color channel to signal rotate in place
const int ORANGE = 2; // Color channel to signal stop
const unsigned char *img;

int target;
int STOPPAGE = 0;

void recon_mode(){
    if(analog(LEFT) > 1900){
        while(analog(LEFT) > 1900){
        printf("Obstacle Detected on left side.\n");
        create_drive_direct(150, 100);
        }
    }
        
    if(analog(RIGHT) > 1900){
        while(analog(RIGHT) > 1900){
        printf("Obstacle Detected on right side.\n");
        create_drive_direct(100, 150);
        }
    }

    // If the left bumper has been hit, back up and turn right.
    if(get_create_lbump(0.1) == 1 || get_create_lflightbump(0.1) == 1 
        || get_create_lclightbump(0.1) == 1 || get_create_llightbump(0.1) == 1){
        
        create_drive_straight(-150);
        msleep(1000);
        create_spin_CW(100);
        msleep(1000);
    }
    // If the right bumper has been hit, back up and turn left.
    if(get_create_rbump(0.1) == 1 || get_create_rflightbump(0.1) == 1 
        || get_create_rclightbump(0.1) == 1 || get_create_rlightbump(0.1) == 1){
        
        create_drive_straight(-150);
        msleep(1000);
        create_spin_CCW(100);
        msleep(1000);
    }
}

void sentry_mode(){
    if(target == BULLSEYE)
        create_stop();
    if(target < LEFT_BORDER)
    	create_spin_CCW(50);
    if(target > LEFT_BORDER && target < BULLSEYE)
    	create_spin_CCW(25);
    if(target > BULLSEYE && target < RIGHT_BORDER)
       	create_spin_CW(25);
    if(target > RIGHT_BORDER)
       	create_spin_CW(50);
}

void camOps(){
   int r;
   int c;
   int ix;

   while (STOPPAGE != 1) {
    camera_update();
    img=get_camera_frame(); // get a camera frame and display it in graphics window
    for(r=0; r<120; r++){
        for(c=0; c<160; c++){
            ix=3*(160*r + c); // index of pixel to paint into row r, column c
            graphics_pixel(c,r,img[ix+2],img[ix+1],img[ix]); // RGB order by reversing GBR
        }
    }
    graphics_update();
    if(get_object_count(ORANGE) > 0)
        STOPPAGE = 1;
   }
}

void driveOps(){        
    while(STOPPAGE != 1){
        target = get_object_center_x(0, 0);
        create_drive_direct(target, 160-target);
        recon_mode();
        if(get_object_count(PURPLE) > 1)
            sentry_mode();
    }
}
