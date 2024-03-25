#include <AT89X52.h>
#include <system.h>
/*****************************
  所有LED上电
*****************************/
void ledpoweron(void)
{
	P3_7=0;
}
/*****************************
  所有LED断电
*****************************/
void ledpoweroff(void)
{
	P3_7=1;
}
/*****************************
  LED全亮
*****************************/
void ledallon(void)
{
    P0=0X00;
	P1=0X00;
	P2=0X00;
	P3=P3&0XC0;
}
/*****************************
  LED全灭
*****************************/
void ledalloff(void)
{
    P0=0Xff;
	P1=0Xff;
	P2=0Xff;
	P3=P3|0X3f;
}
/*****************************
   控制某个LED亮，1-30
*****************************/
void ledon(unsigned char i)
{
  switch (i)
	{
        case  1  : P0=P0&0x7f;break;
		case  2  : P0=P0&0xbf;break;
		case  3  : P0=P0&0xdf;break;
		case  4  : P0=P0&0xef;break;
		case  5  : P0=P0&0xf7;break;
		case  6  : P0=P0&0xfb;break;
		case  7  : P0=P0&0xfd;break;
		case  8  : P0=P0&0xfe;break;//
		case  9  : P1=P1&0xfe;break;
		case  10 : P1=P1&0xfd;break;
		case  11 : P1=P1&0xfb;break;
		case  12 : P1=P1&0xf7;break;
		case  13 : P1=P1&0xef;break;
		case  14 : P1=P1&0xdf;break;
		case  15 : P1=P1&0xbf;break;
		case  16 : P1=P1&0x7f;break;//
		case  17 : P3=P3&0xfe;break;
		case  18 : P3=P3&0xfd;break;
		case  19 : P3=P3&0xfb;break;
		case  20 : P3=P3&0xf7;break;
		case  21 : P3=P3&0xef;break;
		case  22 : P3=P3&0xdf;break;
		case  23 : P2=P2&0xfe;break;
		case  24 : P2=P2&0xfd;break;
		case  25 : P2=P2&0xfb;break;
		case  26 : P2=P2&0xf7;break;
		case  27 : P2=P2&0xef;break;
		case  28 : P2=P2&0xdf;break;
		case  29 : P2=P2&0xbf;break;
		case  30 : P2=P2&0x7f;break;
		default  : break;
  }
}
/*****************************
   控制某个LED灯灭，1-30
*****************************/
void ledoff(unsigned char i)
{
  switch (i)
	{
        case  1  : P0=P0|0x80;break;
		case  2  : P0=P0|0x40;break;
		case  3  : P0=P0|0x20;break;
		case  4  : P0=P0|0x10;break;
		case  5  : P0=P0|0x08;break;
		case  6  : P0=P0|0x04;break;
		case  7  : P0=P0|0x02;break;
		case  8  : P0=P0|0x01;break;//
		case  9  : P1=P1|0x01;break;
		case  10 : P1=P1|0x02;break;
		case  11 : P1=P1|0x04;break;
		case  12 : P1=P1|0x08;break;
		case  13 : P1=P1|0x10;break;
		case  14 : P1=P1|0x20;break;
		case  15 : P1=P1|0x40;break;
		case  16 : P1=P1|0x80;break;//
		case  17 : P3=P3|0x01;break;
		case  18 : P3=P3|0x02;break;
		case  19 : P3=P3|0x04;break;
		case  20 : P3=P3|0x08;break;
		case  21 : P3=P3|0x10;break;
		case  22 : P3=P3|0x20;break;
		case  23 : P2=P2|0x01;break;
		case  24 : P2=P2|0x02;break;
		case  25 : P2=P2|0x04;break;
		case  26 : P2=P2|0x08;break;
		case  27 : P2=P2|0x10;break;
		case  28 : P2=P2|0x20;break;
		case  29 : P2=P2|0x40;break;
		case  30 : P2=P2|0x80;break;
		default  : break;
  }
}
