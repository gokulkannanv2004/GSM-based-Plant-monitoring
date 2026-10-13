#define LCD 0xff<<23
#define RS  1<<18
#define E   1<<19
void INIT(void);
void COMM(unsigned char);
void DATA(unsigned char);
void STR(unsigned char*);
void SHIFT(unsigned char);
void INT(signed int);
void FLOAT(float);
void TITLE(unsigned char* s){
	while(*s){
		COMM(0x80);
		STR(s++);
		delay_millisecond(500);
	}
}
void INIT(void)
{
	PINSEL1|=0;
	IODIR1|=LCD|RS|E;
	COMM(0x01);
	COMM(0x02);
	COMM(0x0c);
	COMM(0x38);
}
void COMM(unsigned char cmd)
{
	IOCLR1=LCD;
	IOSET1=cmd<<23;
	IOCLR1=RS;
	IOSET1=E;
	delay_millisecond(2);
	IOCLR1=E;
}
void DATA(unsigned char data)
{
	IOCLR1=LCD;
	IOSET1=data<<23;
	IOSET1=RS;
	IOSET1=E;
	delay_millisecond(5);
	IOCLR1=E;
}
void STR(unsigned char* str)
{
	while(*str)
	{
		DATA(*str);
		str++;
	}
}
void SHIFT(unsigned char s)
{
	unsigned char i=0;
	while(i<s)
	{
		COMM(0x18);
		delay_millisecond(500);
		i++;
	}
}
void INT(signed int n)
{
	unsigned int arr[5];
	signed int i=0;
	if(n==0)
		DATA('0');
	else
	{
		if(n<0)
		{
		DATA('-');
		n=-n;
	  }
  }
	while(n>0)
	{
	arr[i]=n%10;
	n=n/10;
	i++;
	}
	for(i=i-1;i>=0;i--)
	DATA(arr[i]+48);
}
void FLOAT(float f)
{
	unsigned int temp;
	temp=f;
	INT(temp);
	DATA('.');
	temp=(f-temp)*100;
	INT(temp);
}
