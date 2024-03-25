#include   <AT89X52.h>
#include   <system.h>
#define    BEEP     P3_6
#define    PWMOUT   P3_7
unsigned   char     count=0;      //定义变量“count”为定时器计数中间值
unsigned   char     pwm_level=10; //定义“pwm_level”为亮度等级，0-20。值越大，灯越暗
unsigned   int      i;            //计数值
/*---定时器T0初始化---*/
void T0_INT(void)
{
  TMOD=0x11;
  TL0=(65535-50)%256;  //设定T0初值，50个计数值，时间是50*2us=0.1ms
  TH0=(65535-50)/256;  //设定T0初值，50个计数值，时间是50*2us=0.1ms
  IE=0x8A;             //开启定时器中断
  TR0=1;               //TR0=1开启定时器，TR0=0关闭定时器
}
/*---T0中断，约0.1ms/次，用于产生PWM波形---*/
void time0() interrupt 1
{	
  TL0=(65535-50)%256;
  TH0=(65535-50)/256;
  count++;
  if(count>20)
	{
	  count=0;
    }
  if((count<(pwm_level+1))&&(count<21))
  {
	PWMOUT=1;
  }
	else
	{ 
	  PWMOUT=0;
	}
}
/*程序从这里开始运行*/
main()
{ 
  T0_INT();
  ledpoweroff();        //所有的LED断电
  ledpoweron();		    //所有的LED上电
  ledallon();           //所有的LED亮
  for(i=0;i<100;i++)    //循环100次，让蜂鸣器响一下
  {
     BEEP=0;
     DelayMs(1);
	 BEEP=1; 
	 DelayMs(1); 
  }	
  DelayMs(1000);        //延时1秒左右
  ledalloff();          //关闭所有的LED灯
  while(1)			    //主循环
  {
     for(i=1;i<17;i++)  //循环16次，用于对称点亮LED灯
       {
         ledon(i);
		 ledon(32-i);
		 DelayMs(10);
		 BEEP=~BEEP;
       }
	 DelayMs(500);
	 for(i=1;i<17;i++)  //循环16次，用于对称关闭LED灯
       {
         ledoff(i);
		 ledoff(32-i);
		 DelayMs(10);
		 BEEP=~BEEP;
       }
	 DelayMs(500);		//等待0.5秒
  }
  
}