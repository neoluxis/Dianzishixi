#include <system.h>
/*****************************
    ´óÖÂ7us
*****************************/
void DelayUs2x(unsigned char t)
{   
   while(--t);
}

/****************************
     ´óÖÂ1ms
*****************************/
void DelayMs(unsigned int t)
{    
  while(t--)
  {
     DelayUs2x(245);
     DelayUs2x(245);
  }
}
