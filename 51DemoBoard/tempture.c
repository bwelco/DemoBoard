#include <myhead.h>

#define uchar unsigned char
#define uint unsigned int


U8  U8FLAG, k;
U8  U8count, U8temp;
U8  U8T_data_H, U8T_data_L, U8RH_data_H, U8RH_data_L, U8checkdata;
U8  U8T_data_H_temp, U8T_data_L_temp, U8RH_data_H_temp, U8RH_data_L_temp, U8checkdata_temp;
U8  U8comdata;
U8  outdata[9];  
U8  indata[9];
U8  count, count_r=0;
U8  str[9] = {"RS232"};
U16 U16temp1, U16temp2;
int TL = 0;
int RL = 0;
int TH = 0;
int RH = 0;


void Delay_10us()		//@11.0592MHz
{
	unsigned char i;

	_nop_();
	_nop_();
	_nop_();
	i = 24;
	while (--i);
}

void Delay18ms()		//@11.0592MHz
{
	unsigned char i, j, k;

	_nop_();
	_nop_();
	i = 1;
	j = 194;
	k = 159;
	do
	{
		do
		{
			while (--k);
		} while (--j);
	} while (--i);
}

void Delay500ms()		//@11.0592MHz
{
	unsigned char i, j, k;

	i = 22;
	j = 3;
	k = 227;
	do
	{
		do
		{
			while (--k);
		} while (--j);
	} while (--i);
}

//----------------------------------------------
void  COM(void)
{
	U8 i;
	for(i = 0; i < 8; i ++)	   
	{
		U8FLAG=2;	
		while((!dht11)&&U8FLAG++);
		Delay_10us();
		Delay_10us();
		Delay_10us();
		U8temp=0;
		if(dht11)
			U8temp=1;
		U8FLAG=2;
		while((dht11)&&U8FLAG++);
			  
		if(U8FLAG==1)
			break;
		U8comdata<<=1;
		U8comdata|=U8temp;    
	}
	   
}


void RH_(void)
{
	dht11=0;
	Delay18ms();
	dht11=1;
	Delay_10us();
	Delay_10us();
	dht11=1; 
	if(!dht11)	
	{
		U8FLAG=2;
		while((!dht11)&&U8FLAG++);
		U8FLAG=2;
		while((dht11)&&U8FLAG++);
		COM();
		U8RH_data_H_temp=U8comdata;
		COM();
		U8RH_data_L_temp=U8comdata;
		COM();
		U8T_data_H_temp=U8comdata;
		COM();
		U8T_data_L_temp=U8comdata;
		COM();
		U8checkdata_temp=U8comdata;
		dht11=1;
			
		U8temp=(U8T_data_H_temp+U8T_data_L_temp+U8RH_data_H_temp+U8RH_data_L_temp);
		if(U8temp==U8checkdata_temp)
		{
			U8RH_data_H = U8RH_data_H_temp;
			U8RH_data_L = U8RH_data_L_temp;
			U8T_data_H=U8T_data_H_temp;
			U8T_data_L=U8T_data_L_temp;
			U8checkdata=U8checkdata_temp;
		}
	}

}
	
void gettemperature()
{
    RH_();		
	TH = (int)(U8T_data_H);
	TL = (int)(U8T_data_L);
	
	RH = (int)(U8RH_data_H);		
	RL = (int)(U8RH_data_L);
	//Delay500ms();
    //Delay500ms();
	//Delay500ms();
	//Delay500ms();
	//Delay500ms();
}
