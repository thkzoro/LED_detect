/*
 * TA.c
 *
 *  Created on: 2017年3月26日
 *      Author: kang
 */
#include <msp430.h>
#include <global.h>



#define sample_interval 2000 //采样间隔为1ms
/*控制AD采样*/
inline void control_AD_mode(void){
    TA1CCR0 = sample_interval;
    TA1CCTL0 |= CCIE;
    TA1CTL = TASSEL_2 | ID_3 | MC_1;
}

/*控制舵机*/
inline void control_steer_mode(void){
    /*设置舵机PWM频率为50HZ,占空比*/
    TA1CCR0=steer_freq;
    TA1CCTL1 |= OUTMOD_7 | CCIE;
    TA1CTL = TASSEL_2 | ID_3 | MC_1;
}

/*捕获模式*/
inline void capture_mode(void){
    TA1CCTL2 |= CCIE;
    TA1CTL = TASSEL_2 | ID_0 | MC_2;
}

void TA1_work_mode_switch(int mode){
    TA1CTL |= TACLR;   //清分频系数和工作模式
    switch(mode){
    case TA1_AD_mode:       control_AD_mode();      break;

    case TA1_steer_mode:    control_steer_mode();   break;

    case TA1_capture_mode:
        TA1CCTL2 |= CCIE;
        TA1CTL = TASSEL_2 | ID_0 | MC_2;
        break;

    default: break;
    }

}
