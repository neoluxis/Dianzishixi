#include <AT89X52.H>
#define  uint  unsigned int  //����һ�·�����
#define  uchar unsigned char //����һ�·�����
#define  keystart       P1_0 //���������ʼ������ť��
#define  SOUND_RESET    P1_6 //��������оƬ��λ��
#define  SOUND_DATA     P1_5 //��������оƬ���ݿ�
#define  SOUND_BUSY     P1_4 //��������оƬæµ��
#define  ledtest    		P3_4     //�������ָʾ�ƿ��ƿ�------------���1��ƽ�Ʋ��������0��ƽ����	        
#define  signal     		P2_0     //���������ź������--------------���������źŵ�ƽ�ߵͱ仯
#define  keymodel   		P1_3     //�������ģʽ���ð��������------��������0��ƽ���ɿ�����1��ƽ
#define  ledmodle   		P1_7     //���幤��ģʽָʾ�ƿ��ƿ�--------���1��ƽ�Ʋ��������0��ƽ����������ָʾ����ģʽ  
#define  baiwei     		P2_1     //�����λ������------------------��λ�����������ƶˣ����0��ƽ��Ӧ�İ�λ���������1��ƽ��Ӧ�İ�λ����
#define  shiwei     		P2_4     //����ʮλ������------------------ʮλ�����������ƶˣ����0��ƽ��Ӧ��ʮλ���������1��ƽ��Ӧ��ʮλ����
#define  gewei      		P2_7     //�����λ������------------------��λ�����������ƶˣ����0��ƽ��Ӧ�ĸ�λ���������1��ƽ��Ӧ�ĸ�λ����
uint     heartrate=888;         
uchar    ge,shi,bai;	    
int calu_flag = 0;
int time = 0;
int num = 0;
uint  i=0;                
uchar display_period=5;	  
int speak_flag = 0;
int flag = 0;
int model = 1;
int judge = 0;
int clear = 1;
int key_up1 = 1;
int key_up2 = 1;
int k = -1;
int open_task = 0;
int one_task = 0;
int two_task = 0;
int open = 1;
int task = 0;
int one_heartrate = 0;
int two_heartrate = 0;
int stop_flag = 0;
int task_speak_flag = 0;
int task2_speak_flag = 0;
int time_record = 0;
int last_task = 0;
int task5 = 0;
int j = 0;
int task4 = 0;
code uchar datab[10]={0xa0,0xaf,0x98,0x8a,0x87,0xc2,0xc0,0xae,0x80,0x86};
//                      0    1    2    3    4    5    6    7    8    9 
code uchar datab1[10]={0x20,0x2f,0x18,0x0a,0x07,0x42,0x40,0x2e,0x00,0x06};
//                      0    1    2    3    4    5    6    7    8    9 
code uchar my_xuehao[10] = {2,2,0,1,4,0,0,2,1,6};
void delay1ms(uint count);        //���뼶��ʱ�����Ǻ�׼��   
void sound_reset(void);			  //��λ����оƬ
void speek(unsigned char num);	  //������ַ��Ӧ������
void speekone(void);			  //����һ��������
void speekheartrate(void);	      //��������ֵ
void mcuint(void);		    //��Ƭ����ʼ������
void measure_slow(void);
void measure_fast(void);
void display_sound(void);
void display_id(void)
{
	if(j>=3)
	{
		heartrate = heartrate%100;
	}
	heartrate = my_xuehao[j]+heartrate*10;
	speek(my_xuehao[j]);
	j++;
	delay1ms(100);
}
void key_scan(void)
{
	if(keymodel==0 && key_up1==1)
	{
		delay1ms(10);
		key_up1=0;
		if(keymodel==0)   
		{
			ledmodle=!ledmodle;
			heartrate = 0;
			task += 1;
			one_task = 0;
		  ledtest = 1;	
			if(task == 7)
			{
				task = 2;
				stop_flag = 0;
				two_heartrate = 0;
				one_heartrate = 0;
				heartrate = 0;
				task_speak_flag = 0;
				task2_speak_flag = 0;
				open = 1;
				task4 = 0;
			}
		}
	}
	else if(keymodel==1)	key_up1=1;
}

void key1_scan(void)
{
	if(keystart==0 && key_up2==1)
	{
		delay1ms(10);
		key_up2=0;
		if(keystart==0)   
		{
			heartrate = 0;
			open = open * k;
		}
	}
	else if(keystart==1)	key_up2=1;
}
void main(void)
{ 
	display_sound();
	mcuint();
  while(1)
	{
		key_scan();
		switch (task)
		{
			case 0:	
					if(open_task == 0)
						{
							speek(26);
							open_task = 1;
						}
					if(two_task == 0 && open_task ==1)
					 {
							delay1ms(600);
							heartrate=0; 
							two_task=1;
					 }
					 if(two_task == 1 && open_task ==1)
					 {
							display_id();
					 }
					 if(j >=10)
					 {
							task = 1;
						  heartrate = 0;
							i = 0;
					 }
					 break;
							
			case 2:	
						measure_slow();
						if(flag == 1 && speak_flag == 0)
						{
							speekheartrate();
							speak_flag = 1;
						}
						break;
			case 3:	
						measure_fast();
						if(flag == 1 && speak_flag == 0)
						{
							speekheartrate();
							speak_flag = 1;
						}
						break;						
			case 4:	
						if(task4 == 0)
						{
							open = 1;
							task4 = 1;
							heartrate = 0;
							TR1 = 1;
						}
						key1_scan();
						if(open == -1)
						{
							ledtest=0;	//��������ָʾ��
							time_record = 1;
						}
						if(open == -1 && task_speak_flag == 0)
						{
							speekone();
							task_speak_flag = 1;
						}
						if(open == 1)
						{
							task_speak_flag = 0;
							time_record = 0;
							heartrate = 0;
						}
						if(heartrate >= 999)
						{
							heartrate = 0;
						}
						break;	
			case 5:	//+
						if(signal == 1 && calu_flag == 0)
						{
							one_heartrate++;
							heartrate = one_heartrate;
							calu_flag = 1;
						}
						if(signal == 0 && calu_flag == 1)
						{
							calu_flag = 0;
						}
						break;	
			case 6:	//+
						if(signal == 1 && calu_flag == 0 && stop_flag == 0)
						{
							two_heartrate++;
							heartrate = two_heartrate;
							calu_flag = 1;
						}
						if(signal == 0 && calu_flag == 1)
						{
							calu_flag = 0;
						}
						key1_scan();
						if(open == -1)
						{
							ledtest=0;	//��������ָʾ��
							stop_flag = 1;
							if(task2_speak_flag == 0)
							{
								heartrate = two_heartrate+one_heartrate;
								speekone();
								speekheartrate();
								task2_speak_flag = 1;
							}
						}
						break;	
		}
	}
}

void mcuint(void)
 {
    P0=0xFF;                            //ʹ��Ƭ���ϵ��P0�ڶ����1
		P1=0xFF;                            //ʹ��Ƭ���ϵ��P1�ڶ����1
		P2=0xFF;			                //ʹ��Ƭ���ϵ��P2�ڶ����1
    P3=0xFF;				            //ʹ��Ƭ���ϵ��P3�ڶ����1
    TMOD=0x11;	   			            //�趨��ʱ��T0��T1�Ĺ���ģʽΪ16λ��ʱ��
    TL0=(65536-display_period*500)%256; //�趨��ʱ��T0�ĵ�8λ��ֵ---T0����ˢ���������ʾ
    TH0=(65536-display_period*500)/256; //�趨��ʱ��T0�ĸ�8λ��ֵ---T0����ˢ���������ʾ
    TL1=(65536-100*500)%256;	        //�趨��ʱ��T1�ĵ�8λ��ֵ---100Ϊ100���룬1�μ�ʱ100���룬600�ξ���1����
    TH1=(65536-100*500)/256;	        //�趨��ʱ��T1�ĸ�8λ��ֵ
    IE=0x8A;				            //�����жϡ���ʱ��T0�жϡ���ʱ��T1�ж�
    IP=0x08;				            //�趨�ж����ȼ�����ʱ��T1�ж�����
    TR0=1;					            //������ʱ��T0������ܿ�ʼ��ʱˢ����ʾ
	  TR1=1;
 }

void delay1ms(uint count)
{ 
     int m,n;
     for(m=0;m<count;m++)
	   for(n=0;n<59;n++);
}

void timer0() interrupt 1
 {
    TL0=0x3C;
    TH0=0xF6;
		ge=heartrate%10;
		bai=heartrate/100;	    
		shi=(heartrate/10)%10;	 
		if(task == 4)
		{
			P0=datab[ge];		
			gewei=0;            
			delay1ms(1);
			gewei=1;		

			P0=datab1[shi];		
			shiwei=0;          
			delay1ms(1);
			shiwei=1;			
		 
			P0=datab[bai];		
			baiwei=0;            
			delay1ms(1);
			baiwei=1;		
		}
		if(task == 5 || task == 6)
		{
			P0=datab[ge];		
			gewei=0;            
			delay1ms(1);
			gewei=1;		

			P0=datab[shi];		
			shiwei=0;          
			delay1ms(1);
			shiwei=1;			
		 
			P0=0xfe;		
			baiwei=0;            
			delay1ms(1);
			baiwei=1;	
		}
		if(task != 5 && task != 6 && task != 4)
		{
			P0=datab[ge];		
			gewei=0;            
			delay1ms(1);
			gewei=1;		

			P0=datab[shi];		
			shiwei=0;          
			delay1ms(1);
			shiwei=1;			
		 
			P0=datab[bai];		
			baiwei=0;            
			delay1ms(1);
			baiwei=1;		
		}
	
 } 
 
void timer1() interrupt 3
{
	if(open == -1 && time_record == 1)
	{
		time++;
		heartrate++;
	}
	if(one_task == 1)
	{
		i++;
		if(signal == 1 && judge == 0 && flag == 0 && task == 2)
		{
			heartrate++;
			judge = 1;
		}
		if(signal == 1 && judge == 0 && flag == 0 && task == 3)
		{
			heartrate += 6;
			judge = 1;
		}
		if(signal == 1 && judge == 0 && flag == 0 && task != 3 && task != 2)
		{
			heartrate += 6;
			judge = 1;
		}
		if(signal == 0 && judge == 1 && flag == 0)
		{
			judge = 0;
		}
		if(flag == 1)
		{
			TR1 = 0;
			ledtest=1;	
			one_task = 0;
		}
		if(i==600 && task == 2)      
		{
		 i=0;	            
		 flag=1;        
		}				
		if(i==40 && task == 3)      
		{
		 i=0;	            
		 flag=1;        
		}	
	}
	
}
		
void measure_slow(void)
{
	if(keystart ==0 )
	{
		flag = 0;
		TL1=0xB0;
		TH1=0x3C;
		ledtest=0;	//��������ָʾ��
		speak_flag = 0;
		one_task = 1;
		TR1 = 1;
	}	   
}
void measure_fast(void)
{
	if(keystart==0)
	{
		flag = 0;
		ledtest=0;	//��������ָʾ��
		speak_flag = 0;
		one_task = 1;
		TR1 = 1;
	}	 
}
void sound_reset(void)
{
   SOUND_RESET=1;
   delay1ms(2);
   SOUND_RESET=0;
   delay1ms(2);
}

void speek(unsigned char num)
{
  unsigned char i=0;
  while(SOUND_BUSY==0);
  sound_reset();
  if((num>=0)&&(num<=9))
  {
    for(i=0;i<num+2;i++)
    {
      SOUND_DATA=1;
      delay1ms(1);
      SOUND_DATA=0;
			delay1ms(1);
    }
  }
  else
  {
    for(i=0;i<num;i++)
    {
      SOUND_DATA=1;
      delay1ms(1);
      SOUND_DATA=0;
			delay1ms(1);
    }
  }
}

void speekone(void)
{
  while(SOUND_BUSY==0);
  speek(33);
}

void speekheartrate(void)
{
  speek(bai);
  delay1ms(100); 
  speek(shi);
  delay1ms(100);
  speek(ge);
  delay1ms(100);
}
void display_sound(void)
{ 
  P0=0x00;
  gewei=0;
  shiwei=0;
  baiwei=0;
  speek(26);   //��������
  speek(28);   //������
  gewei=1;
  shiwei=1;
  baiwei=1;
  speek(2);    //2
  for(i=0;i<250;i++)
  {
    P0=datab[2];
	  gewei=0;
	  delay1ms(1);
	  gewei=1;
  }
  speek(0);    //0
  for(i=0;i<250;i++)
  {
    P0=datab[0];
	gewei=0;
	delay1ms(1);
	gewei=1;

	P0=datab[2];
	shiwei=0;
	delay1ms(1);
	shiwei=1;
  }
  speek(2);    //2
   for(i=0;i<250;i++)
  {
    P0=datab[2];
	gewei=0;
	delay1ms(1);
	gewei=1;

	P0=datab[0];
	shiwei=0;
	delay1ms(1);
	shiwei=1;

	P0=datab[2];
	baiwei=0;
	delay1ms(1);
	baiwei=1;
  }
  speek(4);    //4
   for(i=0;i<250;i++)
  {
    P0=datab[4];
	gewei=0;
	delay1ms(1);
	gewei=1;

	P0=datab[2];
	shiwei=0;
	delay1ms(1);
	shiwei=1;

	P0=datab[0];
	baiwei=0;
	delay1ms(1);
	baiwei=1;
  }
  speek(17);   //��
  speek(4);    //4
  for(i=0;i<250;i++)
  {
    P0=0x07;
	gewei=0;
	delay1ms(1);
	gewei=1;
  }
  speek(18);   //��
  speek(2);    //2
   for(i=0;i<250;i++)
  {
    P0=datab[2];
	gewei=0;
	delay1ms(1);
	gewei=1;

	P0=0x07;
	shiwei=0;
	delay1ms(1);
	shiwei=1;
  }
  speek(19);   //��
  speek(20);   //����
  speek(2);    //2
  speek(23);   //����ʱ�̱���ʱ��
  speek(29);   //����
  speek(9);    //9
  for(i=0;i<250;i++)
  {
    P0=0x02;
	gewei=0;
	delay1ms(1);
	gewei=1;
  }
  speek(14);   //��
  speek(3);    //3
   for(i=0;i<250;i++)
  {
    P0=datab[3];
	gewei=0;
	delay1ms(1);
	gewei=1;

	P0=0x02;
	shiwei=0;
	delay1ms(1);
	shiwei=1;
  }
  speek(12);   //ʮ
  for(i=0;i<250;i++)
  {
    P0=datab[0];
	gewei=0;
	delay1ms(1);
	gewei=1;

	P0=datab[3];
	shiwei=0;
	delay1ms(1);
	shiwei=1;

	P0=0x02;
	baiwei=0;
	delay1ms(1);
	baiwei=1;
  }
  speek(15);   //��
  for(i=0;i<500;i++)
  {
    P0=datab[0];
	gewei=0;
	delay1ms(1);
	gewei=1;

	P0=datab[3];
	shiwei=0;
	delay1ms(1);
	shiwei=1;

	P0=0x02;
	baiwei=0;
	delay1ms(1);
	baiwei=1;
  }
}
