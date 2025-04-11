# include "gpio_driver.h"
#include "stm32f10x.h" 
#include "systick_timer.h"
#include "uart.h"

/// UART1 variables
char UART1_msg[250];
unsigned short UART1_cnt=0;
unsigned short UART1_bdg=0;
unsigned short UART1_sgnl=0;
unsigned short UART1_manager[7]={0,0,0,0,0,0,0};

/// Uart2 variables 
char UART2_msg[250];
unsigned short UART2_cnt=0;
unsigned short UART2_bdg=0;
unsigned short UART2_sgnl=0;
unsigned short UART2_manager[7]={0,0,0,0,0,0,0};

/// Uart3 variables 
char UART3_msg[250];
unsigned short UART3_cnt=0;
unsigned short UART3_bdg=0;
unsigned short UART3_sgnl=0;
unsigned short UART3_manager[7]={0,0,0,0,0,0,0};
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
char urt1_msg[30];
char urt2_msg[30];
int signal=1;

int main()
	{
		 Enable_UART(1,9600);
		 Enable_UART(2,9600);
			
		 delay(100);
		 UART2_manager[2]=1;
		 UART1_manager[2]=2;
			
		 usart_SendMsg(1,"Hi from uart1");
		 usart_SendMsg(2,"Hi from uart2");

		// Gpio_init(PortC,13,out50,O_GP_PP);
			
		 while (1)
			{
				
		  }
	}

void USART1_IRQHandler()
	{
		UART_ISR(1,UART1_manager,urt1_msg);
	}

void USART2_IRQHandler()
	{
    UART_ISR(2,UART2_manager,urt2_msg);
	}

void USART3_IRQHandler()
	{
		
	}