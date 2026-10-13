#include"names.h"
unsigned char mess[30];
void uart_config(void);
void uart_str(unsigned char *);
void uart_tx(unsigned char);
unsigned char rx(void);
void dummy(void);
void message(void);
int main()
{
 IODIR0|=IN1|IN2;
 INIT();
 COMM(0x80);
 STR("GSM based remote plant monitoring");
 SHIFT(33);
 uart_config();
 uart_str("AT");
 uart_tx('\r');
 uart_tx('\n');
 delay_second(1);
 uart_str("AT+CMGD=1,4\r\n");//to delete the all the stored messages
 delay_second(90);//to wait for user input
 COMM(0x01);
 uart_str("AT+CMGF=1\r\n");
 delay_second(1);
 uart_str("AT+CMGR=1\r\n");
 delay_second(1);
 message();
 COMM(0x80);
 if((strstr((char*)mess,"STATUS")!=0))
 {
	STR("STATUS");
  uart_str("AT\r\n");
  delay_second(1);
  //uart_str("AT+CMGF=1\r\n");
  //delay_second(1);
  uart_str("AT+CMGS=\"+918531076655\"");
  uart_tx('\r');
   uart_tx('\n');
  delay_second(1);
  COMM(0x01);
  if(((IOPIN0>>soil)&1)==0)//wet
  {
   uart_str("WET");
   uart_tx('\r');
     uart_tx('\n');
   uart_tx(26);
   STR("WET");
  }
  else//dry
  {
   uart_str("DRY");
   uart_tx(26);
   STR("DRY");
  }
 delay_second(90);
 uart_str("AT+CMGR=2");
 uart_tx('\r');
 uart_tx('\n');
 delay_second(1);
 message();
 //k=strstr((char *)mess,"PUMP ON");
 COMM(0x01);
 if((strstr((char *)mess,"PUMP ON"))!=0)
 {
  STR("PUMP ON");
  IOSET0|=IN1;
  IOCLR0|=IN2;
 }
  else
 {
  STR("PUMP OFF");
 }
 
//uart_str("AT+CMGD=1,4");  // clear all messages
//uart_tx('\r');
//uart_tx('\n');
//delay_second(1);

}
}
//*******************************************main program ended****************************************************************//
void uart_config(void)
{
 PINSEL0|=0x5;
 U0LCR=0x83;
 U0DLL=97;
 U0DLM=0;
 U0LCR=0x03;
}
void uart_tx(unsigned char txbyte)
{
 while(((U0LSR>>5)&1)==0);
 U0THR=txbyte;
}
unsigned char rx(void)
{
 while((U0LSR&1)==0);
 return U0RBR;
}
void message(void)
{
  unsigned char s;
	int j=0;
	do
 {
  s=rx();
 // mess[j++]=s;
 }while(s!='@');

 do
 {
 s=rx();
 mess[j++]=s;
 }while(s!='#');

 mess[j]='\0';
}
void uart_str(unsigned char *str)
{
 while(*str)
 uart_tx(*str++);
}
