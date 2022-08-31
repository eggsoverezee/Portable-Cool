#include <kipr/wombat.h>
#define LEFT 0
#define RIGHT 5
#define LEFT_BORDER 40
#define BULLSEYE 80
#define RIGHT_BORDER 120
#define BOTTOM_BORDER 30
#define MIDDLE_Y 60
#define TOP_BORDER 90
#define PURPLE 1

int target;
int stoppage = 0;
const unsigned char *img;#include <kipr/wombat.h>
#define LEFT 0
#define RIGHT 5
#define LEFT_BORDER 40
#define BULLSEYE 80
#define RIGHT_BORDER 120
#define BOTTOM_BORDER 30
#define MIDDLE_Y 60
#define TOP_BORDER 90
#define PURPLE 1
#define PINK 4
int target;
int stoppage = 0;
const unsigned char *img;

void recon_mode()
{
if (analog(LEFT) > 1900)
        {
            while(analog(LEFT) > 1900){
            printf("Obstacle Detected on left side.\n");
            create_drive_direct(150, 100);
            }
        }
        
        if (analog(RIGHT) > 1900)
        {
            while(analog(RIGHT) > 1900){
            printf("Obstacle Detected on right side.\n");
            create_drive_direct(100, 150);
            }
        }
            
        if (get_create_lbump(0.1) == 1
            || get_create_lflightbump(0.1) == 1 
            || get_create_lclightbump(0.1) == 1
            || get_create_llightbump(0.1) == 1)
            // If the left bumper has been hit, back up and turn right.
        {
        	create_drive_straight(-150);
           	msleep(1000); // 3 seconds.
           	create_spin_CW(100);
           	msleep(1000);
        }
        
        if (get_create_rbump(0.1) == 1
            || get_create_rflightbump(0.1) == 1 
            || get_create_rclightbump(0.1) == 1 
            || get_create_rlightbump(0.1) == 1 )
            // If the right bumper has been hit, back up and turn left.
        {
        	create_drive_straight(-150);
           	msleep(1000); // 3 seconds.
           	create_spin_CCW(100);
           	msleep(1000);
        }
}

void sentry_mode()
{
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

void camOps() 
{
   int r;
   int c;
   int ix;

   while (stoppage != 1) 
   {
      camera_update();
      img=get_camera_frame(); // get a camera frame and display it in graphics window
      for(r=0; r<120; r++) 
      {
          for(c=0; c<160; c++) 
          {
              ix=3*(160*r + c); // index of pixel to paint into row r, column c
              graphics_pixel(c,r,img[ix+2],img[ix+1],img[ix]); // RGB order by reversing GBR
          }
      }
      graphics_update();
      if (get_object_count(2) > 0)
          stoppage = 1;
   }
}

void driveOps()
{        
        while(stoppage != 1)
        {
            target = get_object_center_x(0, 0);
            create_drive_direct(target, 160-target);
            recon_mode();
			if(get_object_count(PURPLE) > 1)
        		sentry_mode();
        }
}

int main()
{
   	create_connect();
   	camera_open();
    graphics_open(160, 120);
    
  	thread camThread = thread_create(camOps);
    thread driveThread = thread_create(driveOps);
	
    thread_start(camThread);
    thread_start(driveThread);
    while(1)
    {
        if(stoppage ==1)
        {
         	thread_destroy(camThread);
            thread_destroy(driveThread);
            break;
        }
        else
        {
        	thread_wait(camThread);
        	thread_wait(driveThread);
        }
    }

    camera_close();
	create_disconnect();
    return 0;
}

void recon_mode()
{
if (analog(LEFT) > 1900)
        {
            while(analog(LEFT) > 1900){
            printf("Obstacle Detected on left side.\n");
            create_drive_direct(150, 100);
            }
        }
        
        if (analog(RIGHT) > 1900)
        {
            while(analog(RIGHT) > 1900){
            printf("Obstacle Detected on right side.\n");
            create_drive_direct(100, 150);
            }
        }
            
        if (get_create_lbump(0.1) == 1
            || get_create_lflightbump(0.1) == 1 
            || get_create_lclightbump(0.1) == 1
            || get_create_llightbump(0.1) == 1)
            // If the left bumper has been hit, back up and turn right.
        {
        	create_drive_straight(-150);
           	msleep(1000); // 3 seconds.
           	create_spin_CW(100);
           	msleep(1000);
        }
        
        if (get_create_rbump(0.1) == 1
            || get_create_rflightbump(0.1) == 1 
            || get_create_rclightbump(0.1) == 1 
            || get_create_rlightbump(0.1) == 1 )
            // If the right bumper has been hit, back up and turn left.
        {
        	create_drive_straight(-150);
           	msleep(1000); // 3 seconds.
           	create_spin_CCW(100);
           	msleep(1000);
        }
}

void sentry_mode()
{
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

void camOps() 
{
   int r;
   int c;
   int ix;

   while (stoppage != 1) 
   {
      camera_update();
      img=get_camera_frame(); // get a camera frame and display it in graphics window
      for(r=0; r<120; r++) 
      {
          for(c=0; c<160; c++) 
          {
              ix=3*(160*r + c); // index of pixel to paint into row r, column c
              graphics_pixel(c,r,img[ix+2],img[ix+1],img[ix]); // RGB order by reversing GBR
          }
      }
      graphics_update();
      if (get_object_count(2) > 0)
          stoppage = 1;
   }
}

void driveOps()
{        
        while(stoppage != 1)
        {
            target = get_object_center_x(0, 0);
            create_drive_direct(target, 160-target);
            recon_mode();
			if(get_object_count(PURPLE) > 1)
        		sentry_mode();
        }
}

int main()
{
   	create_connect();
   	camera_open();
    graphics_open(160, 120);
    
  	thread camThread = thread_create(camOps);
    thread driveThread = thread_create(driveOps);
	
    thread_start(camThread);
    thread_start(driveThread);
    while(1)
    {
        if(stoppage ==1)
        {
         	thread_destroy(camThread);
            thread_destroy(driveThread);
            break;
        }
        else
        {
        	thread_wait(camThread);
        	thread_wait(driveThread);
        }
    }

    camera_close();
	create_disconnect();
    return 0;
}