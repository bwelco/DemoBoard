#include <myhead.h>

// int T  �¶�
// int R ʪ��  ʹ��gettemperature();����Դ�ӡ����ʪ�ȵ�ֵ
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
				����������������ģ���ͥ��ȫ��ʿ
				��������⵽��                     ��������
				�������δ��⵽��                   ��������	   
			*/
			if(redlight_flag == 1)
			{
				if(redlight == 1)
				    bpm_on();
				else
					bpm_off();
			}

			/* �����ϵİ������µ�ʱ�򣬽������λ��90��*/
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
				����������ģ�����ؿ���
				����ֵ�����ض�ֵ����λ���ɵ���       �������
				����ֵ�ٴε����ض�ֵ����λ���ɵ���   �������
			 */
			if(sound_key == 0 && sound_flag == 1)		   //���ؿ���
			{
				if(testflag == 0)
				{
					out3 = 0;
				    sprintf(send_message, "out3 = 0\n");
				    sendstr(send_message);

					/*���ؿ��ؽ�����ʱ*/
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

						/*���ؿ��ؽ�����ʱ*/
				   	delay_ms_steering(1000);
					delay_ms_steering(1000);
					delay_ms_steering(500);
				   
					testflag = 0;
				
				}
			
            }

			/*
				�¶��������һ��ģ��յ�����
			    ��ǰ�¶�ֵ < ����ֵ                 ���һ��
			    ��ǰ�¶�ֵ > ����ֵ                 ���һ��
			*/
			
			if(temp_min_flag == 1 && temp_min > (int)TH)
			{
				out1 = 0;
				sprintf(send_message, "out1 = 0\n");    //�¶� < ����ֵ  ���1��
				sendstr(send_message);
			}
			
			
			if(temp_max_flag == 1 && (int)TH > temp_max)
			{
				out1 = 1;
				sprintf(send_message, "out1 = 1\n");    //�¶� > ����ֵ  ���1��
				sendstr(send_message);
			}

			/*
				ʪ�������������ģ����ʪ����
    			��ǰʪ��ֵ < ����ֵ                 �������
    			��ǰʪ��ֵ > ����ֵ                 �������				
			*/
			
			if(humi_max_flag == 1 && (int)RH > humi_max)
			{
				out2 = 0;
				sprintf(send_message, "out2 = 1\n");    //ʪ�� > ����ֵ  ���2��
				sendstr(send_message);
			}
			
			if(humi_min_flag == 1 && (int)RH < humi_min)
			{
				out2 = 1;
				sprintf(send_message, "out2 = 0\n");    //ʪ�� < ����ֵ  ���2��
				sendstr(send_message);
			}

			/*
				��������LED��ģ���Զ�·��
    			��ǰ����ֵ < ����ֵ                 LED��
    			��ǰ����ֵ > ����ֵ                 LED��			 
			*/
			
			if(light_min_flag == 1 && light_compare < light_min)
			{
				//out3 = 0;
				//sprintf(send_message, "out3 = 0\n");    //���� < ����ֵ  ���3��
			//	sendstr(send_message);
				
				red = led_set[0] - '0';
		        green = led_set[1]- '0';
		        blue = led_set[2] - '0';		
			}
			
			if(light_max_flag == 1 && light_compare > light_max)
			{
			//	out3 = 1;
			//	sprintf(send_message, "out3 = 1\n");    //���� > ����ֵ  ���3��
			//	sendstr(send_message);
				
				red = 1;
		        green = 1;
		        blue = 1;	
			}

			/*
			     ��⵽RFID��������ȡ�жϣ�����λ�����俨��
			*/

			if(flag2 == 1)
			{
				/* ��һ��,��cardid_temp����������дֵ,������ */
				if(card_id_count_flag == 0)		   
				{
					strcpy(cardid_temp, cardid);
					card_id_count_flag++;
					sprintf(send_message, "*card id = %s#\n", cardid);
					sendstr(send_message);
				}
				/* ��֮ǰ�Ļ��������Ų�һ��	*/
				if(strcmp(cardid_temp, cardid) != 0)   
				{
					sprintf(send_message, "*card id = %s#\n", cardid);
					sendstr(send_message);
					strcpy(cardid_temp, cardid);
				}
			
				/* ���Ų�ƥ�� */
				if(strcmp(cardid, setcard_buf) != 0)
				{
					continue;
				}

				/* ����ƥ�䲢�ҿ�ֵ���ô� */
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
		        /* ��ն����������� */	
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
/* ��ʱ���� */
void sound_delay(unsigned int z)
{																							   
    unsigned int i,j;
    for(i=z;i>0;i--)
        for(j=110;j>0;j--);
} 
