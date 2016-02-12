#include <myhead.h>
unsigned short T_PCA0;     
unsigned short T_PCA1;
void system_init(void)
{
/*********************** 
	定时器T1波特率产生器    串口1   TxD/P3.1  RxD/P3.0
	*****************/
	TMOD=0x20;			//设置定时器一为工作方式2
	TH1=0xfd;			//设置波特率为9600
	TL1=0xfd;

	TR1=1;
	REN=1;
	SM0=0;
	SM1=1;
	EA=1;
	ES=1;	
	//TI = 1;            //允许使用printf
	PS = 1;
	
/**************************
	独立波特率产生器     串口2	TxD2/P1.3   RxD2/P1.2
	********************/
	
	S2CON=  0x50;			//串口2工作在方式1  10位异步首发 S2REN = 1 允许接收	
	BRT = 0xfd;				//设置波特率为9600
	AUXR =  AUXR |0X10;		//允许波特率发生器运行
	AUXR1 =  AUXR1 & 0xef;	//S2_P4=0,将uart2切换到P1口
	IE2  =  IE2 | 0X01;	    //允许串口2中断
	
//	IP2 = 0X00;
//	IPH2 = 0X00;
	//PSPI = 0;
	//turn_90();

	/*串口1 > PCA中断 > 串口2*/
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
    TMOD=0x20;			//设置定时器一为工作方式2
	TH1=0xfd;			//设置波特率为9600
	TL1=0xfd;
	TR1=1;
	REN=1;
	SM0=0;
	SM1=1;
	EA=1;
	ES=1;	
	
	S2CON = 0x50;			//串口2工作在方式1  10位异步首发 S2REN = 1 允许接收	
	BRT = 0xfd;				//设置波特率为9600
	AUXR = AUXR |0X10;		//允许波特率发生器运行
	AUXR1 = AUXR1 & 0xef;	//S2_P4=0,将uart2切换到P1口
	IE2 = IE2 | 0X01;	    //允许串口2中断
	
	interrupt1_lock = 0;
	interrupt3_lock = 0;
	
	EA = 1;
	TR1 = 1;
	TR0 = 1;
	redlight = 1;
	
	
	/*串口1 > PCA中断 > 串口2*/
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
    T_PCA0 = 46080;      //定时器50ms,11.0592MHZ晶振，T_Value=46080.要两秒需循环
    CCAP0L = T_PCA0;
    CCAP0H = T_PCA0 >> 8;   //Initial PCA module-0
    T_PCA0 += 46080;        //PCA module-0 work in 16-bit timer mode
    CCAPM0 = 0x49;                     //and enable PCA interrupt            //Set PCA timer clock source as Fosc/12
	CR = 1;                 //PCA timer start run
    EA = 1;					//?PCA??          
}