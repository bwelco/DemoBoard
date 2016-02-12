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
int card_id_count_flag = 0;
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
int android_control_flag = 0;
int timeoutflag = 0;

int light_max_flag = 0;
int light_min_flag = 0;

int humi_max_flag = 0;
int humi_min_flag = 0;

int redlight_flag = 0;
int sound_flag = 0;

int steer_flag = 0;
int card_flag = 0;
char led_set[4];
char setcard_buf[15];
int steer_degree = 0;

int lock_2 = 0;
int lock_3 = 0;
int card_flag_c = 0;
int delay_flag = 0;
int testflag = 0;

char Sys_init_info[100] ={ "51 Demo Board\r\n"	
						   "Copyright (c) 2016 bwelco <1143955880@qq.com>\r\n"	   
						   "Build Date 2016-01-30\r\n"	   
						   "Version 1.0\r\n"			 };
int main()
{	
	bpm_off();
    system_init();	
	sendstr(Sys_init_info);
	sendstr("Programme Init Success. Baud:9600\n\t");
	led_set[0] = '1';
	led_set[1] = '1';
	led_set[2] = '1';
	while(1)
	{   		
		while(recv_lock != 1)
		{
			/*
				红外联动蜂鸣器：模拟家庭安全卫士
				人体红外检测到人                     蜂鸣器开
				人体红外未检测到人                   蜂鸣器关	   
			*/
			if(redlight_flag == 1)
			{
				if(redlight == 1)
				    bpm_on();
				else
					bpm_off();
			}

			/* 板子上的按键按下的时候，将舵机复位成90°*/
			if(mykey == 0)
			{
				normal_lcd1602_show();
				while(lock_2 == 1);
				lock_3 = 1;
				
				bpm_on();
				stop_interrupt();
				pwm_value = turn(90);
				InitSteering();
				interrupt1_lock = 1;
				interrupt3_lock = 1;
				normal_lcd1602_show();
				
				delay_ms_steering(1000);
				delay_ms_steering(1000);
				delay_ms_steering(500);
				StopSteering();
				start_interrupt();
				sendstr("OK\n");
				interrupt1_lock = 0;
				interrupt3_lock = 0;
				bpm_off();
								
				lock_3 = 0;
				normal_lcd1602_show();
				
			}

			/*	
				声音联动：模拟声控开关
				声音值到达特定值（电位器可调）       输出三开
				声音值再次到达特定值（电位器可调）   输出三关
			 */
			if(sound_key == 0 && sound_flag == 1)		   //声控开关
			{
				if(testflag == 0)
				{
					out3 = 0;
				    sprintf(send_message, "out3 = 0\n");
				    sendstr(send_message);

					/*声控开关接收延时*/
				   	delay_ms_steering(1000);
					delay_ms_steering(1000);
					delay_ms_steering(500);

					testflag = 1;
				
				}
				else if(testflag == 1)
				{
					out3 = 1;
				    sprintf(send_message, "out3 = 1\n");
				    sendstr(send_message);

						/*声控开关接收延时*/
				   	delay_ms_steering(1000);
					delay_ms_steering(1000);
					delay_ms_steering(500);
				   
					testflag = 0;
				
				}
			
            }

			/*
				温度联动输出一：模拟空调制热
			    当前温度值 < 下限值                 输出一开
			    当前温度值 > 上限值                 输出一关
			*/
			
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

			/*
				湿度联动输出二：模拟排湿风扇
    			当前湿度值 < 下限值                 输出二关
    			当前湿度值 > 上限值                 输出二开				
			*/
			
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

			/*
				光照联动LED：模拟自动路灯
    			当前光照值 < 下限值                 LED开
    			当前光照值 > 上限值                 LED关			 
			*/
			
			if(light_min_flag == 1 && light_compare < light_min)
			{
				//out3 = 0;
				//sprintf(send_message, "out3 = 0\n");    //光照 < 下限值  输出3开
			//	sendstr(send_message);
				
				red = led_set[0] - '0';
		        green = led_set[1]- '0';
		        blue = led_set[2] - '0';		
			}
			
			if(light_max_flag == 1 && light_compare > light_max)
			{
			//	out3 = 1;
			//	sprintf(send_message, "out3 = 1\n");    //光照 > 上限值  输出3关
			//	sendstr(send_message);
				
				red = 1;
		        green = 1;
		        blue = 1;	
			}

			/*
			     检测到RFID读卡器读取中断，向上位机传输卡号
			*/

			if(flag2 == 1)
			{
				/* 第一次,往cardid_temp缓冲区里面写值,并发送 */
				if(card_id_count_flag == 0)		   
				{
					strcpy(cardid_temp, cardid);
					card_id_count_flag++;
					sprintf(send_message, "*card id = %s#\n", cardid);
					sendstr(send_message);
				}
				/* 跟之前的缓冲区卡号不一样	*/
				if(strcmp(cardid_temp, cardid) != 0)   
				{
					sprintf(send_message, "*card id = %s#\n", cardid);
					sendstr(send_message);
					strcpy(cardid_temp, cardid);
				}
			
				/* 卡号不匹配 */
				if(strcmp(cardid, setcard_buf) != 0)
				{
					continue;
				}

				/* 卡号匹配并且卡值设置打开 */
				if(steer_flag == 1 && card_flag == 1 && 
					(strcmp(cardid, setcard_buf) == 0))
				{
					normal_lcd1602_show();
					while(lock_2 == 1);
					lock_3 = 1;
					
					bpm_on();
					stop_interrupt();
					pwm_value = turn(steer_degree);
					InitSteering();
					interrupt1_lock = 1;
					interrupt3_lock = 1;
					normal_lcd1602_show();
					
					delay_ms_steering(1000);
					delay_ms_steering(1000);
					delay_ms_steering(500);
					StopSteering();
					start_interrupt();
					sendstr("OK\n");
					interrupt1_lock = 0;
					interrupt3_lock = 0;
					bpm_off();
					
					lock_3 = 0;
					normal_lcd1602_show();;
					
                }
				stop_interrupt();		
		        /* 清空读卡器缓冲区 */	
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
/* 延时函数 */
void sound_delay(unsigned int z)
{																							   
    unsigned int i,j;
    for(i=z;i>0;i--)
        for(j=110;j>0;j--);
} 
