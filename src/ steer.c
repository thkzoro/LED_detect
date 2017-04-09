#include <msp430.h>
#include <global.h>

void steer_init(void){
    steer_position=0;
    TA1CCR1 = 1000;
    steer_delay_time=20*steer_cale;
    TA1_work_mode_switch(TA1_steer_mode);
    test_data_number++;

}

void steer_turn(int a){
    steer_position+=a;
    TA1CCR1 = a*steer_min_angle+1000;
    steer_delay_time = a*steer_cale;
    TA1_work_mode_switch(TA1_steer_mode);
}



