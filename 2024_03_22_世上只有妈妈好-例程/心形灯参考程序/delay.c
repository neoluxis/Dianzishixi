#include <system.h>
/*****************************
    ����7us
*****************************/
void DelayUs2x(unsigned char t)
{   
   while(--t);
}

/****************************
     ����1ms
*****************************/
void DelayMs(unsigned int t)
{    
  while(t--)
  {
     DelayUs2x(245);
     DelayUs2x(245);
  }
}
