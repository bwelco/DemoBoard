#include <myhead.h>

void lcd_delay(int z)
{
	int a,b;
	for(a=z;a>0;a--)
	for(b=30;b>0;b--);
}

void write_com_1602_morefree (unsigned char com)
{
	 
	  lcdrs=0;
	  lcdrw=0;
	  P0=com;
	  lcd_delay(5);
	  lcden=1;
	  lcd_delay(5);
	  lcden=0;
}
void write_date_1602_morefree (unsigned char date)
{
    
	  lcdrs=1;
	  lcdrw=0;
	  P0=date;
	  lcd_delay(5);
	  lcden=1;
	  lcd_delay(5);
	  lcden=0;
} 
void init_1602_morefree()
{
	lcdrw=0;
	lcden=0;
	lcdrw=0;
	write_com_1602_morefree(0x38);
	write_com_1602_morefree(0x0c);
	write_com_1602_morefree(0x06);
	write_com_1602_morefree(0x01);
}
/*
void android_control_lcd1602()
{
	int i = 0;
	write_com_1602_morefree(0x80);
    sprintf(tab1, "     Android     ");
	sprintf(tab2, "   Controlling          ");
	for(i=0;i<strlen("     Android     ");i++)
	{
		write_date_1602_morefree(tab1[i]);
		lcd_delay(5);
	}
		
	write_com_1602_morefree(0x80+0x40);
	for(i=0;i<strlen("   Controlling          ");i++)
	{
		write_date_1602_morefree(tab2[i]);
		lcd_delay(5);
	}
}
*/
void normal_lcd1602_show()
{
	int i = 0;
	write_com_1602_morefree(0x80);
	if(TH > 50)
	{
		sprintf(tab1, "  T:OFF  R:OFF       ", TH, RH);
		sprintf(tab2, "   %s     ", ledstr2);
	}
	else
	{
		sprintf(tab1, "  T = %d R = %d       ", TH, RH);
		sprintf(tab2, "   %s     ", ledstr2);
	}
	
	for(i=0;i<strlen(tab1);i++)
	{
		write_date_1602_morefree(tab1[i]);
		lcd_delay(5);
	}
		
	write_com_1602_morefree(0x80+0x40);
	for(i=0;i<strlen(tab2);i++)
	{
		write_date_1602_morefree(tab2[i]);
		lcd_delay(5);
	}
}

void welcome()
{
	int i = 0;
	write_com_1602_morefree(0x80);
    sprintf(tab1, "  51DemoBoard      ");
	sprintf(tab2, "   Starting...          ");
	for(i=0;i<strlen(tab1);i++)
	{
		write_date_1602_morefree(tab1[i]);
		lcd_delay(5);
	}
		
	write_com_1602_morefree(0x80+0x40);
	for(i=0;i<strlen(tab2);i++)
	{
		write_date_1602_morefree(tab2[i]);
		lcd_delay(5);
	}
}
