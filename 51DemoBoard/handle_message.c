#include <myhead.h>
char send_message[30];
int tempdegree;
char *p;
//int android_flag = 0;

int commandflag = 0;
void handle_message()
{
    if(strncmp(strbuf, "test", 4) == 0)
	{
	//	android_flag = 1;
		//CR = 0;  
		sprintf(send_message, "*return test#\n");
		sendstr(send_message);
		temp_lock = 1;
		commandflag = 1;
		android_control_flag = 1;
    }
	
	else if(strncmp(strbuf, "GETTEMPERATURE", strlen("GETTEMPERATURE")) == 0)
	{
		int i = 0;
		gettemperature();
		sprintf(send_message, "*T = %d.%d#\n", TH, TL);
		sendstr(send_message);
		
		if(out1 == 1)
			i = 1;
		else 
			i = 0;
		sprintf(send_message, "*out1 = %d#\n", i);
		sendstr(send_message);
		normal_lcd1602_show();
	}
	else if(strncmp(strbuf, "GETHUNIDITY", strlen("GETTEMPERATURE")) == 0)
	{
		int i = 0;
		gettemperature();
		sprintf(send_message, "*R = %d.%d#\n", RH, RL);
		sendstr(send_message);
		
		if(out2 == 1)
			i = 1;
		else 
			i = 0;
		sprintf(send_message, "*out2 = %d#\n", i);
		sendstr(send_message);
		normal_lcd1602_show();
	}
	else if(strncmp(strbuf, "GETLIGHT", strlen("GETLIGHT")) == 0)
	{
		int i = 0;
		getled();
		sendstr(ledstr);
		if(out3 == 1)
			i = 1;
		else 
			i = 0;
		sprintf(send_message, "*out3 = %d#\n",i);
		sendstr(send_message);
		normal_lcd1602_show();
	}
	else if(strncmp(strbuf, "SETSTEER", strlen("SETSTEER")) == 0)
	{
		p = strbuf;
		tempdegree = 0;
		p = p + 8;
		
		while(*p != '\0')
		{
			tempdegree = tempdegree * 10 + (*p - '0');
			p++;
        }
		
		normal_lcd1602_show();
		
		stop_interrupt();
		pwm_value = turn(tempdegree);
		InitSteering();
		interrupt1_lock = 1;
		interrupt3_lock = 1;
		normal_lcd1602_show();
		
		delay_ms_steering(1000);
		delay_ms_steering(1000);
		delay_ms_steering(500);

		StopSteering();
		start_interrupt();
		
		interrupt1_lock = 0;
		interrupt3_lock = 0;
		//android_control_lcd1602();
		normal_lcd1602_show();
		
		//lock_3 = 0;
    }
	
	else if(strncmp(strbuf, "OUT1ON", strlen("OUT1ON")) == 0)
	{
		out1 = 0;
    }
	
	else if(strncmp(strbuf, "OUT2ON", strlen("OUT2ON")) == 0)
	{
		out2 = 0;
    }
	
	else if(strncmp(strbuf, "OUT3ON", strlen("OUT3ON")) == 0)
	{
		out3 = 0;		
    }
	
	else if(strncmp(strbuf, "OUT1OFF", strlen("OUT1OFF")) == 0)
	{
		out1 = 1;
    }
	
	else if(strncmp(strbuf, "OUT2OFF", strlen("OUT2OFF")) == 0)
	{
		out2 = 1;
    }
	
	else if(strncmp(strbuf, "OUT3OFF", strlen("OUT3OFF")) == 0)
	{
		out3 = 1;		
    }
	
	else if(strncmp(strbuf, "SETRGB", strlen("SETRGB")) == 0)
	{
		red = strbuf[6] - '0';
		green = strbuf[7]- '0';
		blue = strbuf[8] - '0';		
		
		delay_ms_steering(1000);
		delay_ms_steering(1000);
		delay_ms_steering(500);
		
		red = green = blue = 1;
    }
	
	else if(strncmp(strbuf, "BPMON", strlen("BPMON")) == 0)
	{
		bpm_on();
    }
	
	else if(strncmp(strbuf, "BPMOFF", strlen("BPMOFF")) == 0)
	{
		bpm_off();		
    }
	
	else if(strncmp(strbuf, "SETMAX", strlen("SETMAX")) == 0)   //setmaxtemp1223
	{
		p = strbuf;
		p = p + 6;
		
		if(*p == 'T')
		{
			temp_max = 0;
			p = p + 4;
			if(*p == '\0')
			{
				temp_max_flag = 0;
				temp_max = 100;
				
				return;
			}
			while(*p != '\0')
			{
				temp_max = temp_max * 10 + (*p - '0');
				p++;
			}
			temp_max_flag = 1;
			
		}
		
		if(*p == 'L')
		{
			light_max = 0;
			p = p + 5;
			if(*p == '\0')
			{
				light_max_flag = 0;
				light_max = 99999;
				return;
			}
			while(*p != '\0')
			{
				light_max = light_max * 10 + (*p - '0');
				p++;
			}
			light_max_flag = 1;
		}
		
		if(*p == 'H')
		{
			humi_max = 0;
			p = p + 4;
			if(*p == '\0')
			{
				humi_max_flag = 0;
				humi_max = 100;
				return;
			}
			while(*p != '\0')
			{
				humi_max = humi_max * 10 + (*p - '0');
				p++;
			}
			humi_max_flag = 1;
		}
    }
	
	else if(strncmp(strbuf, "SETMIN", strlen("SETMIN")) == 0)   //setmaxtemp1223
	{
		p = strbuf;
		p = p + 6;
		
		if(*p == 'T')
		{
			temp_min = 0;
			p = p + 4;
			if(*p == '\0')
			{
				temp_min_flag = 0;
				temp_min = -40;
				return;
			}
			while(*p != '\0')
			{
				temp_min = temp_min * 10 + (*p - '0');
				p++;
			}
			temp_min_flag = 1;
			sprintf(send_message, "*Th = %d, tempmin = %d#\n", (int)TH, temp_min);
			sendstr(send_message);
		}
		
		if(*p == 'L')
		{
			light_min = 0;
			p = p + 5;
			if(*p == '\0')
			{
				light_min_flag = 0;
				light_min = -1;
				return;
			}
			while(*p != '\0')
			{
				light_min = light_min * 10 + (*p - '0');
				p++;
			}
			light_min_flag = 1;
			sprintf(send_message, "*T = %d#\n", light_compare);
		    sendstr(send_message);
		}
		
		if(*p == 'H')
		{
			humi_min = 0;
			p = p + 4;
			if(*p == '\0')
			{
				humi_min_flag = 0;
				humi_min = 0;
				return;
			}
			while(*p != '\0')
			{
				humi_min = humi_min * 10 + (*p - '0');
				p++;
			}
			humi_min_flag = 1;
		}
    }
	

	
	else if(strncmp(strbuf, "CARDSET", strlen("CARDSET")) == 0)
	{
		char *q = setcard_buf;
		p = strbuf;
		p = p + 7;
		while(*p != '\0')
		{
			*q = *p;
			q++;
			p++;
		}
		*q = '\0';
		card_flag = 1;
    }
	
	else if(strncmp(strbuf, "STEERSET", strlen("STEERSET")) == 0)
	{
		p = strbuf;
		p = p + 8;
		steer_degree = 0;
		while(*p != '\0')
		{
			steer_degree = steer_degree * 10 + (*p - '0');
			p++;
		}
		steer_flag = 1;
    }
	
	else if(strncmp(strbuf, "GETOUT1", strlen("GETOUT1")) == 0)
	{
		int i = 0;
		if(out1 == 1)
			i = 1;
		else 
			i = 0;
		sprintf(send_message, "*out1 = %d#\n",i);
		sendstr(send_message);
    }
	
	else if(strncmp(strbuf, "GETOUT2", strlen("GETOUT2")) == 0)
	{
		int i = 0;
		if(out2 == 1)
			i = 1;
		else 
			i = 0;
		sprintf(send_message, "*out2 = %d#\n",i);
		sendstr(send_message);
    }
	
	else if(strncmp(strbuf, "GETOUT3", strlen("GETOUT3")) == 0)
	{
		int i = 0;
		if(out3 == 1)
			i = 1;
		else 
			i = 0;
		sprintf(send_message, "*out3 = %d#\n",i);
		sendstr(send_message);
    }
	
	else if(strncmp(strbuf, "SOUNDFLAG", strlen("SOUNDFLAG")) == 0)
	{
		p = strbuf + 9;
		if(*p == '1')
			sound_flag = 1;
		if(*p == '0')
			sound_flag = 0;
    }
	
	else if(strncmp(strbuf, "LIGHTFLAG", strlen("LIGHTFLAG")) == 0)
	{
		p = strbuf + 9;
		if(*p == '1')
			redlight_flag = 1;
		if(*p == '0')
		{
			redlight_flag = 0;
			bpm_off();
		}
    }
	
	else if(strncmp(strbuf, "GETREDLIGHT", strlen("GETREDLIGHT")) == 0)
	{
		int i = 0;
		if(redlight_flag == 1)
			i = 1;
		else 
			i = 0;
		sprintf(send_message, "*redlight = %d#\n",i);
		sendstr(send_message);
    }
	
	else if(strncmp(strbuf, "GETSOUNDFLAG", strlen("GETSOUNDFLAG")) == 0)
	{
		int i = 0;
		if(sound_flag == 1)
			i = 1;
		else 
			i = 0;
		sprintf(send_message, "*sound = %d#\n",i);
		sendstr(send_message);
    }
	
	else if(strncmp(strbuf, "GETALLFLAGINIT", strlen("GETALLFLAGINIT")) == 0)
	{
	    int i = 0;
		int rcc,gcc,bcc;
		gettemperature();
	//	CR = 0;
		sprintf(send_message, "*T = %d.%d#\n", TH, TL);
		sendstr(send_message);
	//	Delay18ms();
		sprintf(send_message, "*R = %d.%d#\n", RH, RL);
		sendstr(send_message);
	//	Delay18ms();
	
		getled();
		normal_lcd1602_show();
		sendstr(ledstr);
	//	Delay18ms();
		/***********out1***********/
		if(out1 == 1)
			i = 1;
		else 
			i = 0;
		sprintf(send_message, "*out1 = %d#\n", i);
		sendstr(send_message);
	//	Delay18ms();
	
		/***********out2***********/
		if(out2 == 1)
			i = 1;
		else 
			i = 0;
		sprintf(send_message, "*out2 = %d#\n", i);
		sendstr(send_message);
	//	Delay18ms();
	
		/***********out3***********/
		if(out3 == 1)
			i = 1;
		else 
			i = 0;
		sprintf(send_message, "*out3 = %d#\n",i);
		sendstr(send_message);
	//	Delay18ms();
	
		/*********led******************/
		
		if(red == 0) rcc = 0; else rcc = 1;
		if(green == 0) gcc = 0; else gcc = 1;
		if(blue == 0) bcc = 0; else bcc = 1;
		sprintf(send_message, "*RGB = %c%c%c#\n", led_set[0], led_set[1] ,led_set[2]);
		sendstr(send_message);
		
	//	Delay18ms();
	
		/**************bpm****************/
	
		sprintf(send_message, "*bpm = %d#\n", bpm_flag);
		sendstr(send_message);
	//	Delay18ms();
	
		/**********************soundflag*************/
		if(sound_flag == 1)
			i = 1;
		else 
			i = 0;
		sprintf(send_message, "*sound = %d#\n",i);
		sendstr(send_message);

		/*******************redlight**************/
		if(redlight_flag == 1)
			i = 1;
		else 
			i = 0;
		sprintf(send_message, "*redlight = %d#\n",i);
		sendstr(send_message);

	
		sprintf(send_message, "*REFRESHOK#\n");
		sendstr(send_message);
		timeoutflag = 0;

	

    }
	else if(strncmp(strbuf, "GETALLSTATE", strlen("GETALLSTATE")) == 0)
	{
	    int i = 0;
		int rcc,gcc,bcc;
			gettemperature();
	//	CR = 0;
		//android_flag = 1;

		sprintf(send_message, "*T = %d.%d#\n", TH, TL);
		sendstr(send_message);

		sprintf(send_message, "*R = %d.%d#\n", RH, RL);
		sendstr(send_message);

			getled();
		normal_lcd1602_show();
		sendstr(ledstr);


		/***********out1***********/
		if(out1 == 1)
			i = 1;
		else 
			i = 0;
		sprintf(send_message, "*out1 = %d#\n", i);
		sendstr(send_message);
	
		/***********out2***********/
		if(out2 == 1)
			i = 1;
		else 
			i = 0;
		sprintf(send_message, "*out2 = %d#\n", i);
		sendstr(send_message);
	
		/***********out3***********/
		if(out3 == 1)
			i = 1;
		else 
			i = 0;
		sprintf(send_message, "*out3 = %d#\n",i);
		sendstr(send_message);
	
		/*********led******************/
		
		if(red == 0) rcc = 0; else rcc = 1;
		if(green == 0) gcc = 0; else gcc = 1;
		if(blue == 0) bcc = 0; else bcc = 1;
		sprintf(send_message, "*RGB = %c%c%c#\n", led_set[0], led_set[1] ,led_set[2]);
		sendstr(send_message);
		
	
		/**************bpm****************/
	
		sprintf(send_message, "*bpm = %d#\n", bpm_flag);
		sendstr(send_message);
	
		/**********************soundflag*************/
		if(sound_flag == 1)
			i = 1;
		else 
			i = 0;
		sprintf(send_message, "*sound = %d#\n",i);
		sendstr(send_message);
		
		/*******************redlight**************/
		if(redlight_flag == 1)
			i = 1;
		else 
			i = 0;
		sprintf(send_message, "*redlight = %d#\n",i);
		sendstr(send_message);
		timeoutflag = 0;

    }
	else if(strncmp(strbuf, "EXIT", strlen("EXIT")) == 0)
	{
	    sendstr("*EXITOK#\n");
	//	PCA_init();
		bpm_on();
		Delay500ms();
		bpm_off();
	
		normal_lcd1602_show();
    }		
	else if(strncmp(strbuf, "SETMYLED", strlen("SETMYLED")) == 0)
	{
	
		p = strbuf + 8;
		led_set[0] = *p;
		led_set[1] = *(p + 1);
		led_set[2] = *(p + 2);
		sprintf(send_message, "*rgb:%c%c%c#\n", led_set[0], led_set[1], led_set[2]);
		sendstr(send_message);
		
		sendstr(send_message);
	}
	else 
	{
	    sprintf(send_message,"*Error Code:%s#\n",strbuf);
		sendstr(send_message);
	}			  

	sprintf(send_message, "*Command Done.#\n");
	sendstr(send_message);

}
