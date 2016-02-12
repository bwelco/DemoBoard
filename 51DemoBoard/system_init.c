#include <myhead.h>
unsigned short T_PCA0;     
unsigned short T_PCA1;
void system_init(void)
{
/*********************** 
	��ʱ��T1�����ʲ�����    ����1   TxD/P3.1  RxD/P3.0
	*****************/
	TMOD=0x20;			//���ö�ʱ��һΪ������ʽ2
	TH1=0xfd;			//���ò�����Ϊ9600
	TL1=0xfd;

	TR1=1;
	REN=1;
	SM0=0;
	SM1=1;
	EA=1;
	ES=1;	
	//TI = 1;            //����ʹ��printf
	PS = 1;
	
/**************************
	���������ʲ�����     ����2	TxD2/P1.3   RxD2/P1.2
	********************/
	
	S2CON=  0x50;			//����2�����ڷ�ʽ1  10λ�첽�׷� S2REN = 1 �������	
	BRT = 0xfd;				//���ò�����Ϊ9600
	AUXR =  AUXR |0X10;		//�������ʷ���������
	AUXR1 =  AUXR1 & 0xef;	//S2_P4=0,��uart2�л���P1��
	IE2  =  IE2 | 0X01;	    //������2�ж�
	
//	IP2 = 0X00;
//	IPH2 = 0X00;
	//PSPI = 0;
	//turn_90();

	/*����1 > PCA�ж� > ����2*/
    IPH = 0X90;
	IP = 0X10;
	IP2H = 0X00;
	IP2 = 0X01;

	init_1602_morefree();
	write_com_1602_morefree(0x80);
	welcome();
	PCA_init();
	//Delay100us();      
}

void stop_interrupt()
{
    TR1 = 0;
	EA = 0;
	
	interrupt1_lock = 0;
	interrupt3_lock = 0;
}

void start_interrupt()
{
    TMOD=0x20;			//���ö�ʱ��һΪ������ʽ2
	TH1=0xfd;			//���ò�����Ϊ9600
	TL1=0xfd;
	TR1=1;
	REN=1;
	SM0=0;
	SM1=1;
	EA=1;
	ES=1;	
	
	S2CON = 0x50;			//����2�����ڷ�ʽ1  10λ�첽�׷� S2REN = 1 �������	
	BRT = 0xfd;				//���ò�����Ϊ9600
	AUXR = AUXR |0X10;		//�������ʷ���������
	AUXR1 = AUXR1 & 0xef;	//S2_P4=0,��uart2�л���P1��
	IE2 = IE2 | 0X01;	    //������2�ж�
	
	interrupt1_lock = 0;
	interrupt3_lock = 0;
	
	EA = 1;
	TR1 = 1;
	TR0 = 1;
	redlight = 1;
	
	
	/*����1 > PCA�ж� > ����2*/
    IPH = 0X90;
	IP = 0X10;
	IP2H = 0X00;
	IP2 = 0X01;

}

void InitSteering(void)
{
	TMOD=0x11;
	TH0=-20000/256;
	TL0=-20000%256;
	TH1=-1500/256;
	TL1=-1500%256;
	EA=1;
	TR0=1;
	ET0=1;
	TR1=1;
	ET1=1;
	
}

void StopSteering(void)
{
	ET0 = 0;
	TR1 = 0;
	ET1 = 0;

	EA = 1;
}

void sendstr(char *str)
{
	int i;
    int len = strlen(str);
	char *p = str;
	
	for(i = 0; i < len; i++)
	{
		SBUF = *p;
		while(!TI);	   
		TI = 0;	 
		p++;
	}
}

void PCA_init()
{
    CCON = 0;               //Initial PCA control register
                            //PCA timer stop running
                            //Clear CF flag
                            //Clear all module interrupt flag
    CL = 0;                 //Reset PCA base timer
    CH = 0;
    CMOD = 0x00;
    T_PCA0 = 46080;      //��ʱ��50ms,11.0592MHZ����T_Value=46080.Ҫ������ѭ��
    CCAP0L = T_PCA0;
    CCAP0H = T_PCA0 >> 8;   //Initial PCA module-0
    T_PCA0 += 46080;        //PCA module-0 work in 16-bit timer mode
    CCAPM0 = 0x49;                     //and enable PCA interrupt            //Set PCA timer clock source as Fosc/12
	CR = 1;                 //PCA timer start run
    EA = 1;					//?PCA??          
}