void delay_millisecond(unsigned int ms)
{
	T0PR=15000-1;
	T0TCR=0x1;
	while(T0TC<ms);
	T0TCR=0X3;
	T0TCR=0X0;
}
void delay_second(unsigned int s)
{
	T0PR=15000000-1;
	T0TCR=0x1;
	while(T0TC<s);
	T0TCR=0X3;
	T0TCR=0X0;
}
