#include <myhead.h>
int numcc = 0;
int cnt = 0;
void Uart() interrupt 4 using 1
{
    unsigned char recv_data;
	if(RI == 1)
	{
	    recv_data = SBUF;
		RI = 0;
	
		if(recv_data != '*')
		{
			strbuf[posi++] = recv_data;	
		}
		else
		{
			temp_lock = 0;
			strbuf[posi] = '\0';
		    recv_lock = 1;
			posi = 0;
		}
	}

}

void UART_2Interrupt(void) interrupt 8
{
	if(S2CON&S2RI)
	{
		S2CON&=~S2RI;
		temp2=S2BUF;
		if(temp2 == 0x02)
		{
			card_id_posi = 0;			
        }
		if(temp2 != 0x02 && temp2 != 0x03)
		{
			cardid[card_id_posi++] = temp2;
		}
		if(temp2 == 0x03)
		{
			flag2 = 1;
			cardid[card_id_posi - 2] = '\0';
		}
	} 
}

void timer0(void) interrupt 1
{
	if(interrupt1_lock == 1)
	{
		pwm=1;
		
		TH0=-20000/256;
		TL0=-20000%256;
		if(interrupt1_lock == 1)
			TR1=1;
	}
}

void timer1(void) interrupt 3
{
	if(interrupt3_lock == 1)
	{
		pwm=0;
		TH1=-pwm_value/256;
		TL1=-pwm_value%256;
		if(interrupt3_lock == 1)
			TR1=0;
    }
}

void PCA_isr() interrupt 7
{	
	if(android_control_flag == 0)		 //客户端不在线时
	{
		CCF0 = 0;
		CCAP0L = T_PCA0;
		CCAP0H = T_PCA0 >> 8;
		T_PCA0 += 46080;
		cnt++;
		if (cnt == 20)   //1s
		{
			cnt = 0; 
			numcc = 0;
			gettemperature();
			getled();
			normal_lcd1602_show();
		}
	 }
	 if(android_control_flag == 1)	     //客户端在线时  心跳检测
	 {
	 	CCF0 = 0;
		CCAP0L = T_PCA0;
		CCAP0H = T_PCA0 >> 8;
		T_PCA0 += 46080;
		cnt++;
		if (cnt == 20)   //1s
		{
			cnt = 0; 
			timeoutflag++;
			if(timeoutflag == 3)  //5s超时检测
			{
				bpm_on();
				Delay500ms();
				bpm_off();
				android_control_flag = 0;   //跳到正常循环
			}
		}

	 }
}






