#include <myhead.h>
unsigned int pwm_value=1500;

int interrupt1_lock = 0;
int interrupt3_lock = 0;

void delay_ms_steering(unsigned int x)
{
	unsigned int i;
	while(x--)for(i=0;i<125;i++);
}

unsigned int turn(int degree)
{
    unsigned int temp;
	float temp2;
	temp2 = (2000 / 180)*degree + 500;
	temp2 = (temp2 / (180 + 30)) * 180;
	temp = (unsigned int)temp2;
	return temp;
}
void bpm_on()
{
	bpm = 1;
	bpm_flag = 1;
}

void bpm_off()
{
	bpm = 0;
	bpm_flag = 0;
}
/*
void turn_90()
{
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
}
*/
