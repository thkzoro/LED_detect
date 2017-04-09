
/*
 * global.h
 *
 *  Created on: 2017年3月26日
 *      Author: kang
 */
#include <msp430g2553.h>
#include <string.h>

#ifndef SRC_GLOBAL_H_
#define SRC_GLOBAL_H_

#define rt_freq 16000    //参考信号的频率为1K，换算成SMCLK的时钟周期
/*带通滤波器输出波形x(t)的频率误差范围，用于判断是否为驱动信号S(t)*/
#define xt_freq_err_range 800
#define AD_sample_time 10   //采样次数
/* 控制舵机的定时器频率设为2M，舵机工作频率为50HZ， TA_CCR0=2M/50=steer_freq=40000
 * 舵机转动范围：0~180°，对应控制占空比2.5%~12.5%，因此TA_CCR0=1000~5000;
 * 为了便于定时器控制舵机，设置舵机最小单位为9°，舵机位置0~180°->steer_position:0~20
 * 例：TA_CCR0=10*200+1000；舵机位置=90°
 * 舵机从A位置转到B位置，需要时间，舵机速度： 0.23秒/60度(4.8V)
 * 每9°需要34.5ms，50HZ一个周期=20ms，所以需要延时2*20ms，
 */
#define steer_freq 40000
#define steer_cale 3
#define  steer_min_angle    200
#define TA1_free_mode 0
#define TA1_AD_mode 1
#define TA1_steer_mode 2
#define TA1_capture_mode 3
#define xt_min_freq (capture_value+capture_overflow*16000000)>=(rt_freq-xt_freq_err_range)
#define xt_max_freq (capture_value+capture_overflow*16000000)<=(rt_freq+xt_freq_err_range)

extern void steer_init(void);
extern void steer_turn(int a);
extern void TA1_work_mode_switch(int mode);

enum run_state {
    sample_end,
    steer_turn_end,
    capture_finish,
    sleep,
    RX_complete,
    other
};

unsigned int capture_value;
unsigned int capture_overflow;
unsigned int AD_value[AD_sample_time];
unsigned int steer_delay_time;
unsigned int steer_position;
unsigned int test_data_number;
unsigned int run_status;
       float AD_result;



#endif /* SRC_GLOBAL_H_ */
