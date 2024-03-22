#define uchar unsigned char
#define uint unsigned int

void DelayUs2x(unsigned char t);
void DelayMs(unsigned int t);

void ledon(unsigned char i);
void ledoff(unsigned char i);
void ledallon(void);
void ledalloff(void);
void ledpoweron(void);
void ledpoweroff(void);
void T0_INT(void);
