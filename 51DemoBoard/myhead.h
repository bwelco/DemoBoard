#include <stc12c5a60s2.h>
#include <stdio.h>
#include <string.h>
#include <intrins.h> 
/*
   ��Ƭ���� ������2015��8��15�� 22:09:17 985��
             ����2015��8��19�� 17:45:20 1379��
   Author : MoreFree
*/

typedef unsigned char  U8;       /* defined for unsigned 8-bits integer variable 	  */
typedef signed   char  S8;       /* defined for signed 8-bits integer variable		  */
typedef unsigned int   U16;      /* defined for unsigned 16-bits integer variable     */
typedef signed   int   S16;      /* defined for signed 16-bits integer variable 	  */
typedef unsigned long  U32;      /* defined for unsigned 32-bits integer variable 	  */
typedef signed   long  S32;      /* defined for signed 32-bits integer variable 	  */
typedef float          F32;      /* single precision floating point variable (32bits) */
typedef double         F64;      /* double precision floating point variable (64bits) */
/**************main*********************/
extern int recv_lock;
#define S2RI 0x01	//����2�����ж������־λ  recv
#define S2TI 0x02	//����2�����ж������־λ  send
extern void UART_1SendOneByte(unsigned char c);
extern void UART_2SendOneByte(unsigned char c);
extern unsigned char flag1,flag2,temp1,temp2;
extern char strbuf[50];
extern void handle_message();
extern int temp_lock;
extern void stop_interrupt();
extern void start_interrupt();
extern char cardid[20];
extern char cardid_temp[20];

extern int posi;
extern int temp_lock;
extern int card_id_posi;
extern int delay_flag;

extern int temp_max;
extern int temp_min;
extern int light_max;
extern int light_min;
extern int humi_max;
extern int humi_min;
extern int temp_max_flag;
extern int temp_min_flag;

extern int light_max_flag;
extern int light_min_flag;

extern int humi_max_flag;
extern int humi_min_flag;

extern int redlight_flag;
extern int sound_flag;
extern int steer_flag;
extern int card_flag;
extern char setcard_buf[20];
extern int steer_degree;


extern char tab1[20];
extern char tab2[20];
extern char led_set[4];

extern unsigned short T_PCA0;     
extern unsigned short T_PCA1;
extern int cnt;
extern void PCA_init();
/**************system_init***************/
extern void system_init(void);
extern int lock_2;
extern int lock_3;

extern void sendstr(char *str);
extern char send_message[30];
/*******************temperature************/

#define uchar unsigned char
#define uint unsigned int
extern U8  U8FLAG,k;
extern U8  U8count,U8temp;
extern U8  U8T_data_H,U8T_data_L,U8RH_data_H,U8RH_data_L,U8checkdata;
extern U8  U8T_data_H_temp,U8T_data_L_temp,U8RH_data_H_temp,U8RH_data_L_temp,U8checkdata_temp;
extern U8  U8comdata;
extern U8  outdata[9];  
extern U8  indata[9];
extern U8  count, count_r;
extern U8  str[9];
extern U16 U16temp1,U16temp2;

extern void Delay_10us();
extern void Delay18ms();

extern void Delay500ms();
extern void  COM(void);
extern void RH_(void);
extern void gettemperature();
extern int TH, TL;
extern int RH, RL;
extern void sound_delay(unsigned int z);

/************************steering****************/

extern unsigned int pwm_value;
extern void delay_ms_steering(unsigned int x);
extern unsigned int turn(int degree);
extern void InitSteering(void);
extern void StopSteering(void);
//extern void turn_90();

extern int interrupt1_lock;
extern int interrupt3_lock;
extern char ledstr2[50];

/**************** light ***********************/
#define   uchar unsigned char
#define   uint unsigned int	
#define   DataPort P0	 //LCD1602���ݶ˿�

sbit	  SCL = P2^5;      //IICʱ�����Ŷ���
sbit  	  SDA = P2^4;      //IIC�������Ŷ���
sbit      redlight = P3^2;

sbit      out1 = P1^4;
sbit      out2 = P1^7;
sbit      out3 = P1^6;

sbit      dht11  = P2^7 ;
sbit      pwm = P1^5;
sbit      bpm = P2^2;
sbit      sound_key = P3^4;

sbit      red =  P2^1;
sbit      green = P2^0;
sbit      blue = P2^3;

sbit      lcden = P2^6;
sbit      lcdrw = P1^1;
sbit      lcdrs = P1^0;
sbit      mykey = P3^7;



#define	  SlaveAddress   0x46 //����������IIC�����еĴӵ�ַ,����ALT  ADDRESS��ַ���Ų�ͬ�޸�
                              //ALT  ADDRESS���Žӵ�ʱ��ַΪ0xA6���ӵ�Դʱ��ַΪ0x3A
typedef   unsigned char BYTE;
typedef   unsigned short WORD;

extern BYTE    BUF[8];                         //�������ݻ�����      	
extern uchar   ge,shi,bai,qian,wan;            //��ʾ����
extern int     dis_data;                       //����
extern int light_compare;
extern void delay_nms(unsigned int k);

extern void Init_BH1750(void);

extern void conversion(uint temp_data);

extern void  Single_Write_BH1750(uchar REG_Address);               //����д������
extern uchar Single_Read_BH1750(uchar REG_Address);                //������ȡ�ڲ��Ĵ�������
extern void  Multiple_Read_BH1750();                               //�����Ķ�ȡ�ڲ��Ĵ�������
//------------------------------------
extern void Delay5us();
extern void Delay5ms();
extern void BH1750_Start();                    //��ʼ�ź�
extern void BH1750_Stop();                     //ֹͣ�ź�
extern void BH1750_SendACK(bit ack);           //Ӧ��ACK
extern bit  BH1750_RecvACK();                  //��ack
extern void BH1750_SendByte(BYTE dat);         //IIC�����ֽ�д
extern BYTE BH1750_RecvByte();                 //IIC�����ֽڶ�
extern void getled();
extern char ledstr[50];
//---------------lcd1602-----------------------
extern void lcd_delay(int z);
extern void write_com_1602_morefree (unsigned char com);
extern void write_date_1602_morefree (unsigned char date);
extern void init_1602_morefree();
// void android_control_lcd1602();
extern void normal_lcd1602_show();
extern void welcome();
extern int android_flag;
