#include <kipr/wombat.h>
#include "cool_tracking.h"

 int main(){
    create_connect();
    camera_open();
    graphics_open(160, 120);
    thread camThread = thread_create(camOps);
    thread driveThread = thread_create(driveOps);
    thread_start(camThread);
    thread_start(driveThread);

    while(1){
        if(STOPPAGE == 1){
            thread_destroy(camThread);
            thread_destroy(driveThread);
            break;
        }
        else{
            thread_wait(camThread);
            thread_wait(driveThread);
        }
    }

    camera_close();
    create_disconnect();
    return 0;
}
