#include <lirc/lirc_client.h>
#include "turn.h"
#include <wiringPi.h>
#include <softPwm.h>

char *keymap[21] ={
       " KEY_CHANNELDOWN ",
       " KEY_CHANNEL ",
       " KEY_CHANNELUP ",
       " KEY_PREVIOUS ",
       " KEY_NEXT ",
       " KEY_PLAYPAUSE ",
       " KEY_VOLUMEDOWN ",
       " KEY_VOLUMEUP ",
       " KEY_EQUAL ",
       " KEY_NUMERIC_0 ",
       " BTN_0 ",
       " BTN_1 ",
       " KEY_NUMERIC_1 ",
       " KEY_NUMERIC_2 ",
       " KEY_NUMERIC_3 ",
       " KEY_NUMERIC_4 ",
       " KEY_NUMERIC_5 ",
       " KEY_NUMERIC_6 ",
       " KEY_NUMERIC_7 ",
       " KEY_NUMERIC_8 ",
       " KEY_NUMERIC_9 "
};
void ircontrol(char *code)
{
    if (strstr(code, keymap[1])){
        t_up(50,10);  
  	printf("pp\n");	
    }
    else if (strstr(code, keymap[7])){
	    printf("car_down\n");
        t_down(50,10);        
    }
    else if(strstr(code, keymap[3])){
	    printf("car_left\n");
        t_left(50,10);
    }
    else if(strstr(code,keymap[5])){
        t_right(50,10);
    }
    else if(strstr(code,keymap[4])){
        t_stop(10);
    }
}
int main(void)
{
    struct lirc_config *config;
    int buttonTimer = millis();
    char *code;
    char *c;
    if(wiringPiSetup() == -1){
        printf("setup wiringPi failed !");
        return 1; 
    }
	
    init();
    
    if(lirc_init("lirc",1)==-1)
        exit(EXIT_FAILURE);
    printf("1\n");    
    if(lirc_readconfig(NULL,&config,NULL)==0)
    {
        printf("2\n");
	      while(lirc_nextcode(&code)==0)
        {
            printf("3\n");
		        if(code==NULL) continue;{
            if (millis() - buttonTimer  > 400)
            {

                printf("4\n");
	              printf("%s\n", code);
			          ircontrol(code);
            }
        }
        free(code);
    }
    lirc_freeconfig(config);
    }
    lirc_deinit();
    exit(EXIT_SUCCESS);
    return 0;
}
