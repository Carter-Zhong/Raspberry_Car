#include <wiringPi.h>
#include <softPwm.h>
#include <stdio.h>
#include <stdlib.h>

#define PWMA 1
#define AIN2 2
#define AIN1 3
#define PWMB 4
#define BIN1 5
#define BIN2 6

void init();

void t_up(unsigned int speed, unsigned int t_time);//前进

void t_stop(unsigned int t_time);//停止

void t_down(unsigned int speed, unsigned int t_time);//后退

void t_left(unsigned int speed, unsigned int t_time);//左转

void t_right(unsigned int speed, unsigned int t_time);//右转

void control()//键盘控制

