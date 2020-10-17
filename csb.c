#include "pca9685.h"
#include <stdio.h>
#include <stdlib.h>
#include <softPwm.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <time.h>
#include <sys/time.h>
#include <wiringPi.h>
#include <softPwm.h>
#include "avoid.h"
#include "turn.h"
#define PIN_BASE 300
#define MAX_PWM 4096
#define HERTZ 50
#define BUFSIZE 512
#define max(x,y) ((x)>(y)? (x):(y))
#define min(x,y) ((x)<(y)? (x):(y))
#define Trig  28
#define Echo  29
void PWM_write(int servonum,float x);

/*******************舵机定义*************************
*****************************************************/
int myservo1 = 0; //舵机定义 超声波摇头

void ultraInit(void)//初始化
{
  pinMode(Echo, INPUT);
  pinMode(Trig, OUTPUT);
}
float disMeasure(void)//超声波
{
  struct timeval tv1;
  struct timeval tv2;
  long start, stop;
  float dis;
  digitalWrite(Trig, LOW);
  delayMicroseconds(2);
  digitalWrite(Trig, HIGH);
  delayMicroseconds(10);       //发出超声波脉冲
  digitalWrite(Trig, LOW);
  while(!(digitalRead(Echo) == 1));
  gettimeofday(&tv1, NULL);           //获取当前时间
  while(!(digitalRead(Echo) == 0));
  gettimeofday(&tv2, NULL);           //获取当前时间
  start = tv1.tv_sec * 1000000 + tv1.tv_usec;   //微秒级的时间
  stop  = tv2.tv_sec * 1000000 + tv2.tv_usec;
  dis = (float)(stop - start) / 1000000 * 34990 / 2;  //求出距离
  return dis;
}
/******************超声波前方向避障***********************/
float front_detection()
{
 float dis_f;
 PWM_write(myservo1,90);
 delay(500);
 dis_f =  disMeasure();
 return dis_f;  
}
/******************超声波左方向避障***********************/
float left_detection()
{
 float dis_l;
 PWM_write(myservo1,175);
 delay(500);
 dis_l = disMeasure();
 return dis_l;
}
/*******************右侧方向避障***************************/
float right_detection()
{
       float dis_r;
       PWM_write(myservo1,5);
       delay(500);
       dis_r =  disMeasure();
       return dis_r;
}
int main(int argc, char *argv[])
{
    float dis1,dis2,dis3;
    // char buf[BUFSIZE]={0xff,0x00,0x00,0x00,0xff};
    int time=1;
     /*RPI*/
    wiringPiSetup();
    init_b();
    /*WiringPi GPIO*/
    ultraInit();            //超声波初始化    
       /*PWM output*/
    init();
       // Setup with pinbase 300 and i2c location 0x40
    int fd = pca9685Setup(PIN_BASE, 0x40, HERTZ);
    if (fd < 0)
    {
        printf("Error in setup\n");
        return fd;
    }
       // Reset all output
    pca9685PWMReset(fd);
    printf("ok");
    int i=90;
    while(i--){
        dis1 = front_detection();
	      printf("dis1[%.2f]aa\n", dis1);
        if(dis1 < 30){
            t_stop(200);
		        printf("1\n");
            t_down(50,100);
            t_stop(200);
            dis2 = left_detection();
            dis3 = right_detection();
		        printf("dis2[%.2f]", dis2);
		        printf("dis3[%.2f]", dis3);
            if(dis2 < 30 && dis3 < 30){
                t_left(50,1000);
                printf("2\n");
		        }
            else if (dis2 > dis3){
                t_left(50,300);
                t_stop(100);
			         printf("3\n");
            }
            else if(dis2 < dis3){
                t_right(50,300);
			          printf("4\n");
                t_stop(100);
            }else{
				        t_stop(100);
		        }
        }
        else{
		        printf("5\n");
		        // t_right(50,30);
            t_up(20,10);
		        avoid_car();
        }
	  }
    t_stop(100);
    return 0;
}
/**
 * Calculate the number of ticks the signal should be high for the required amount of time
 */
int calcTicks(float impulseMs, int hertz)
{
       float cycleMs = 1000.0f / hertz;
       return (int)(MAX_PWM * impulseMs / cycleMs + 0.5f);
}
/********************  舵机摇头*****************************/
void PWM_write(int servonum,float x)
{
  float y;
  int tick;
  y=x/90.0+0.5;
  y=max(y,0.5);
  y=min(y,2.5);
  tick = calcTicks(y, HERTZ);
  pwmWrite(PIN_BASE+servonum,tick);
}
