#include   <AT89X52.h>
#include   <system.h>
#define    BEEP     P3_6
#define    PWMOUT   P3_7
unsigned   char     count=0;      //���������count��Ϊ��ʱ�������м�ֵ
unsigned   char     pwm_level=10; //���塰pwm_level��Ϊ���ȵȼ���0-20��ֵԽ�󣬵�Խ��
unsigned   int      i;            //����ֵ
/*---��ʱ��T0��ʼ��---*/
void T0_INT(void)
{
  TMOD=0x11;
  TL0=(65535-50)%256;  //�趨T0��ֵ��50������ֵ��ʱ����50*2us=0.1ms
  TH0=(65535-50)/256;  //�趨T0��ֵ��50������ֵ��ʱ����50*2us=0.1ms
  IE=0x8A;             //������ʱ���ж�
  TR0=1;               //TR0=1������ʱ����TR0=0�رն�ʱ��
}
/*---T0�жϣ�Լ0.1ms/�Σ����ڲ���PWM����---*/
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
/*��������￪ʼ����*/
main()
{ 
  T0_INT();
  ledpoweroff();        //���е�LED�ϵ�
  ledpoweron();		    //���е�LED�ϵ�
  ledallon();           //���е�LED��
  for(i=0;i<100;i++)    //ѭ��100�Σ��÷�������һ��
  {
     BEEP=0;
     DelayMs(1);
	 BEEP=1; 
	 DelayMs(1); 
  }	
  DelayMs(1000);        //��ʱ1������
  ledalloff();          //�ر����е�LED��
  while(1)			    //��ѭ��
  {
     for(i=1;i<17;i++)  //ѭ��16�Σ����ڶԳƵ���LED��
       {
         ledon(i);
		 ledon(32-i);
		 DelayMs(10);
		 BEEP=~BEEP;
       }
	 DelayMs(500);
	 for(i=1;i<17;i++)  //ѭ��16�Σ����ڶԳƹر�LED��
       {
         ledoff(i);
		 ledoff(32-i);
		 DelayMs(10);
		 BEEP=~BEEP;
       }
	 DelayMs(500);		//�ȴ�0.5��
  }
  
}