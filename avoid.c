#include "avoid.h"
#include "turn.h"

void init_b()
{
	pinMode(ZUO_B, INPUT);
	pinMode(YOU_B, INPUT);
}

void avoid_car()
{
	int L, R;
	L = digitalRead(ZUO_B);
	R = digitalRead(YOU_B);

	if(L==LOW&&R==LOW)//后退
	{
		t_down(50,100);
		printf("down......................\n");
	}
	else if(L==HIGH&&R==LOW)//左转
	{
		t_left(50,100);
		printf("left\n");
	}
	else if(L==LOW&&R==HIGH)//右转
	{
		t_right(50,100);
		printf("right\n");
	}else{ //前进
		printf("go \n");
	//	runing(100,1,0,1,0);
	}
		
}