#include "turn.h"

void init(){
	//初始化wiringPi库
	if(wiringPiSetup()==-1) 
		printf("init unsuccessfully..\n");  
	else 
		printf("init successfully..\n");  
	//设置阵脚模式
	pinMode(AIN1, OUTPUT);
	pinMode(AIN2, OUTPUT);
	pinMode(BIN1, OUTPUT);
	pinMode(BIN2, OUTPUT);
	softPwmCreate(PWMA, 0, 255);	
	softPwmCreate(PWMB, 0, 255);
}

void t_up(unsigned int speed, unsigned int t_time) //前进
{
	digitalWrite(AIN2,0);
    digitalWrite(AIN1,1);
    softPwmWrite(PWMA,speed); 
    digitalWrite(BIN2,0);
    digitalWrite(BIN1,1);
    softPwmWrite(PWMB,speed);
    delay(t_time);
}

void t_stop(unsigned int t_time)//停止
{
        digitalWrite(AIN2,0);
        digitalWrite(AIN1,0);
        softPwmWrite(PWMA,0);
        digitalWrite(BIN2,0);
        digitalWrite(BIN1,0);
        softPwmWrite(PWMB,0);
        delay(t_time);
}
void t_down(unsigned int speed,unsigned int t_time)
{
        digitalWrite(AIN2,1);
        digitalWrite(AIN1,0);
        softPwmWrite(PWMA,speed);      
        digitalWrite(BIN2,1);
        digitalWrite(BIN1,0);
        softPwmWrite(PWMB,speed);
        delay(t_time);
}
void t_left(unsigned int speed,unsigned int t_time)
{
        digitalWrite(AIN2,1);
        digitalWrite(AIN1,0);
        softPwmWrite(PWMA,speed);      
        digitalWrite(BIN2,0);
        digitalWrite(BIN1,1);
        softPwmWrite(PWMB,speed);
        delay(t_time);
}
void t_right(unsigned int speed,unsigned int t_time)
{
        digitalWrite(AIN2,0);
        digitalWrite(AIN1,1);
        softPwmWrite(PWMA,speed);      
        digitalWrite(BIN2,1);
        digitalWrite(BIN1,0);
        softPwmWrite(PWMB,speed);
        delay(t_time);
}

void control(){

	init();

	char c='0';
	int time=500;

	while(c!='q'){
		system("stty raw");
		c=getchar();
		system("stty -raw");
		switch(c){
			case 'w': t_up(50, 100); break;//前进
			case 's': t_down(50, 100); break;//后退
			case 'a': t_left(50, 100); break;//左转
			case 'd': t_right(50, 100);break;//右转
			default:break;
		}

	}
	t_stop(200);
	printf("demo end..\n");

}
//测试按键控制小车
/*
int main(void)
{
	control();

	return 0;
}
*/