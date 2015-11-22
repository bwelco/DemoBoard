#include <myhead.h>

// int T  温度
// int R 湿度  使用gettemperature();后可以打印出温湿度的值
int recv_lock = 0;
unsigned char flag1 = 0,flag2 = 0,temp1,temp2;
char strbuf[50] = {0};
int posi = 0;
int temp_lock = 0;
int card_id_posi = 0;
char cardid[20] = {0};
char cardid_temp[20];

char tab1[20];
char tab2[20];

int temp_max = 100;
int temp_min = -40;
int light_max = 99999;
int light_min = -1;
int humi_max = 100;
int humi_min = 0;

int temp_max_flag = 0;
int temp_min_flag = 0;

int light_max_flag = 0;
int light_min_flag = 0;

int humi_max_flag = 0;
int humi_min_flag = 0;

int redlight_flag = 0;
int sound_flag = 0;

int steer_flag = 0;
int card_flag = 0;
char led_set[4];
char setcard_buf[20];
int steer_degree = 0;

int lock_2 = 0;
int lock_3 = 0;
int card_flag_c = 0;
int delay_flag = 0;
int testflag = 0;
int main()
{	
	bpm = 0;
    system_init();	
	sendstr("Programme starting...\n");
	
	while(1)
	{   		
		while(recv_lock != 1)
		{
			if(redlight_flag == 1)
			{
				if(redlight == 1)
				    bpm = 1;
				else
					bpm = 0;
			}
			if(mykey == 0)
			{
				//sound_delay();
				if(mykey == 0)
				{
					while(lock_2 == 1);
					lock_3 = 1;
					
					bpm = 1;
					stop_interrupt();
					pwm_value = turn(90);
					InitSteering();
					interrupt1_lock = 1;
					interrupt3_lock = 1;
					
					delay_ms_steering(1000);
					delay_ms_steering(1000);
					delay_ms_steering(500);
					StopSteering();
					start_interrupt();
					sendstr("OK\n");
					interrupt1_lock = 0;
					interrupt3_lock = 0;
					bpm = 0;
					
					lock_3 = 0;
				}
			}
			if(sound_key == 0 && sound_flag == 1)
			{
				//sound_delay();
				if(sound_key == 0)
				{
				//	out1 = 0;
				//	sprintf(send_message, "out1 = 0\n");
				//	sendstr(send_message);
				//	sound_key = 1;
					
					if(testflag == 0)
					{
						out1 = 0;
					    sprintf(send_message, "out1 = 0\n");
					    sendstr(send_message);
					    sound_key = 1;
						testflag = 1;
						continue;
					}
					if(testflag == 1)
					{
						out1 = 1;
					    sprintf(send_message, "out1 = 1\n");
					    sendstr(send_message);
					    sound_key = 1;
						testflag = 0;
						continue;
					}
					/*if(testflag == 0)
					{
						red = led_set[0] - '0';
						green = led_set[1]- '0';
						blue = led_set[2] - '0';	
						testflag = 1;
						delay_ms_steering(1000);
					//	delay_ms_steering(1000);
						delay_ms_steering(500);
					}
					
					if(testflag == 1)
					{
						red = 1;
						green = 1;
						blue = 1;	
						testflag = 0;
						delay_ms_steering(1000);
						//delay_ms_steering(1000);
						delay_ms_steering(500);
					}*/
				}
				
            }
			
			if(temp_min_flag == 1 && temp_min > (int)TH)
			{
				out1 = 0;
				sprintf(send_message, "out1 = 0\n");    //温度 < 下线值  输出1开
				sendstr(send_message);
			}
			
			
			if(temp_max_flag == 1 && (int)TH > temp_max)
			{
				out1 = 1;
				sprintf(send_message, "out1 = 1\n");    //温度 > 上限值  输出1关
				sendstr(send_message);
			}
			
			if(humi_max_flag == 1 && (int)RH > humi_max)
			{
				out2 = 0;
				sprintf(send_message, "out2 = 1\n");    //湿度 > 上限值  输出2关
				sendstr(send_message);
			}
			
			if(humi_min_flag == 1 && (int)RH < humi_min)
			{
				out2 = 1;
				sprintf(send_message, "out2 = 0\n");    //湿度 < 下限值  输出2开
				sendstr(send_message);
			}
			
			if(light_min_flag == 1 && light_compare < light_min)
			{
				out3 = 0;
				sprintf(send_message, "out3 = 0\n");    //光照 < 下限值  输出3开
				sendstr(send_message);
				
				red = led_set[0] - '0';
		        green = led_set[1]- '0';
		        blue = led_set[2] - '0';		
			}
			
			if(light_max_flag == 1 && light_compare > light_max)
			{
				out3 = 1;
				sprintf(send_message, "out3 = 1\n");    //光照 > 上限值  输出3关
				sendstr(send_message);
				
				red = 1;
		        green = 1;
		        blue = 1;	
			}
			
			//if(card_flag_c == 1)
			//{
			//	//android_control_lcd1602();
			//	card_flag_c = 0;
			//}
			
			//if(android_flag == 0)
			//{
			//	normal_lcd1602_show();
			//}
			/*
			if(delay_flag == 1 && flag2 == 0)
			{
				CR = 0;
				IE2  =  IE2 | 0X00;
				normal_lcd1602_show();
				delay_ms_steering(1000);
				delay_ms_steering(1000);
				delay_ms_steering(500);
				delay_flag = 0;
				IE2  =  IE2 | 0X01;
				PCA_init();
			}
			*/
			if(flag2 == 1)
			{
				if(android_flag == 1)
				{
					sprintf(send_message, "card id = %s\n", cardid);
					sendstr(send_message);
				}
				if(strcmp(cardid, setcard_buf) != 0)
				{
					continue;
				}
				if(steer_flag == 1 && card_flag == 1 && 
					(strcmp(cardid, setcard_buf) == 0))
				{
					while(lock_2 == 1);
					lock_3 = 1;
					
					bpm = 1;
					stop_interrupt();
					pwm_value = turn(steer_degree);
					InitSteering();
					interrupt1_lock = 1;
					interrupt3_lock = 1;
					
					delay_ms_steering(1000);
					delay_ms_steering(1000);
					delay_ms_steering(500);
					StopSteering();
					start_interrupt();
					sendstr("OK\n");
					interrupt1_lock = 0;
					interrupt3_lock = 0;
					bpm = 0;
					
					lock_3 = 0;
					
                }
				stop_interrupt();
			//	Delay500ms();
				//Delay500ms();
				
				while(S2CON&S2RI)
				{
					S2CON&=~S2RI;
					temp2=S2BUF;
				}
				flag2 = 0;
				start_interrupt();
				
			}
        }
		handle_message();
		recv_lock = 0;
		
	}
}

void sound_delay(unsigned int z)
{																							   
    unsigned int i,j;
    for(i=z;i>0;i--)
        for(j=110;j>0;j--);
} 
