#include "turn.h"

#define LEFT 23
#define MID  24
#define RIGHT 25

void init_trace()
{
	pinMode(LEFT, INPUT);
	pinMode(MID, INPUT);
	pinMode(RIGHT, INPUT);
}

void trace_car()
{
	init();
	init_x();
	int index=0;

	while(1)
	{
		int R, L, M;
		int time = 100;

		L=digitalRead(LEFT);
    	R=digitalRead(RIGHT);
		M=digitalRead(MID);
		if((R==LOW&&M==HIGH&&L==LOW)||(R==HIGH&&M==HIGH&&L==LOW)
				||(R==LOW&&M==HIGH&&L==HIGH)||(R==HIGH&&M==HIGH&&L==HIGH))
		{
			printf("go ahead\n");
			t_up(50, time);
			if(R==HIGH&&L==HIGH) index=3;
			else if(L==HIGH) index=1; 
			else if(R==HIGH) index=2;
		}
		else if(R==LOW&&M==LOW&&L==HIGH&&index!=1)
		{
			printf("left\n");
			t_left(50,time);
		}
		else if(R==HIGH&&M==LOW&&L==LOW&&index!=2)
		{
			printf("right\n");
			t_right(50, time);
		}
		else if(R==LOW&&M==LOW&&L==LOW)
		{
			printf("index==%d\n",index);
			while(index==1&&M!=HIGH) {
				t_left(50, 100);
				printf("left_2");
				M=digitalRead(MID);
			}
			while(index==2&&M!=HIGH) {
				t_right(50, 100);
			    printf("right_2\n");
				M=digitalRead(MID);
			}
			t_up(50,100);
		}
        else{
            printf("stop\n");
            t_stop(200);
        }
	}
}

int main(void)
{
	trace_car();

	return 0;
}