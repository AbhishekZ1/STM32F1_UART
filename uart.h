unsigned long USART_BRR(unsigned short Urt, unsigned long BR);/// decide boudrate

void Enable_UART(unsigned short USART,unsigned long Boud_Rate);/// Enable Usart

char usart_rx(unsigned short urt);///recive function urt

void usart_tx(unsigned urt,char c);// Transmit char data

void usart_SendMsg(unsigned urt,char str[]);// Transmit String

void usart_msg(unsigned short urt,unsigned short urt_mgr[],char str[]); // send urt msg set and clear signal 

void UART_ISR(unsigned short urt,unsigned short urt_mgr[],char Str[]);// UART IRQ

void UART_TIMER_ISR(unsigned short urt1_mgr[],unsigned short urt2_mgr[],unsigned short urt3_mgr[]);// Timer urt irq


// clear message

/* 
	variables for uart manager
	0- count 
	1- signal
	2-Bridge
	3-Terminator should be on or of
	4-terminating char
	5-time cnst 
	6-time counter
*/



