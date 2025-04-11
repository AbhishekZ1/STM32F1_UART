#include "stm32f10x.h" 
#include "gpio_driver.h"
#include "uart.h"
#include "systick_timer.h"

/// Enable usart
/// set boudrate
/// Rx
/// Tx
/// Send msg string
/// Enable usart
/// UART IRQ
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

void Enable_UART(unsigned short USART,unsigned long Boud_Rate)
	 { RCC->APB2ENR |=1; // enabled alternate function APB2
		 unsigned long Br = USART_BRR(USART,Boud_Rate);
	 	if (USART==1)
			{
				__disable_irq();
				
				RCC->APB2ENR |=0X4000; // enable uart 1..
				// pin A9 and pin A10 are Tx and Rx for UART 1 pin Declaration
				Gpio_init(PortA,10,IN,I_GP_PP); // declare pin A10 as input push pull
				Gpio_init(PortA,9,out50,O_AP_PP); //declare pin A9 as output (Tx) for usart 
				
				USART1->BRR = Br;// setting Bodrate as 9600bps,
				
				USART1->CR1 |= 0x4; // Enable Reciver 
				USART1->CR1 |=0x8; // Enable Transmitter
				USART1->CR1 |=0x2000; //Enable UART
				
				USART1->CR1 |=0x20; // Enable Intrrupt data is ready to read
				NVIC_EnableIRQ(USART1_IRQn);
				
				__enable_irq();
			
			}
		else if (USART==2)
			{ 
				__disable_irq();
				
				RCC->APB1ENR |= 0X20000; // Enable USART 2
				Gpio_init(PortA,3,IN,I_GP_PP); // declare pin A10 as input push pull
				Gpio_init(PortA,2,out50,O_AP_PP); //declare pin A9 as output (Tx) for usart 
				
				USART2->BRR = Br;// setting Bodrate as 9600bps,
				
				USART2->CR1 |= 0x4; // Enable Reciver 
				USART2->CR1 |=0x8; // Enable Transmitter
				USART2->CR1 |=0x2000; //Enable UART
				
				USART2->CR1 |=0x20; // Enable Intrrupt data is ready to read
				NVIC_EnableIRQ(USART2_IRQn);
				
				__enable_irq();

			}
		else if (USART==3)
			{
				__disable_irq();
				
				RCC->APB1ENR |= 0X40000; // Enable USART 3
				Gpio_init(PortB,11,IN,I_GP_PP); // declare pin A10 as input push pull
				Gpio_init(PortB,10,out50,O_AP_PP); //declare pin A9 as output (Tx) for usart 
				
				USART3->BRR = Br;// setting Bodrate as 9600bps,
				
				USART3->CR1 |= 0x4; // Enable Reciver 
				USART3->CR1 |=0x8; // Enable Transmitter
				USART3->CR1 |=0x2000; //Enable UART
				
				USART3->CR3 |=0x20; // Enable Intrrupt data is ready to read
				NVIC_EnableIRQ(USART3_IRQn);
				__enable_irq();
			
			}

	 }
/// set boudrate
unsigned long USART_BRR(unsigned short Urt, unsigned long BR)
	{
			unsigned long div;
			unsigned long dec;
			unsigned long final;
			double frac;
			double frac2;
		
			if (Urt == 1)
			{
					div = 108000000;  // 108 MHz for USART1
					frac = 108000000.00;
			}
			else // For USART2 and USART3
			{
					div = 54000000;   // 54 MHz for USART2 & USART3
					frac = 54000000.00;
			}
			div = div / (BR * 16);   // Mantissa calculation
			frac = 16 * ((frac / (BR * 16)) - div); // Fraction calculation
			dec = (unsigned long)frac; // Integer part of fraction
			frac2 = 100 * (frac - dec); // Decimal part to check for rounding
			// Rounding logic
			if (frac2 > 50)
			{
					dec++;
					if (dec == 16)  // If fraction overflows, increment mantissa
					{
							dec = 0;
							div++;
					}
			}
			// Construct USART_BRR value
			final = (div << 4) | dec;
			return final;
	}
// Recive Function
char usart_rx(unsigned short urt)
	{
		 char c;
			if (urt == 1)
			{
			 while ((USART1->SR & 0x20) == 0) // Wait until data is ready to read
			 {}
				c= USART1->DR; // DR has recived data
			}
			else if (urt == 2)
			{
				while ((USART2->SR & 0x20) == 0)
			 {}
				c= USART2->DR;
			}
			else if (urt == 3)
			{
				while ((USART3->SR & 0x20) == 0)
			 {}
				c= USART3->DR;
			}
			return c;
	}
	
/// Transmit Function
void usart_tx(unsigned urt,char c)
	{
		 if(urt == 1)
		 {
		    while(( USART1->SR &(1<<6))==0x00)
         {}
	       USART1->DR= c;
		 }
		 else if(urt == 2)
		 {
		    while(( USART2->SR &(1<<6))==0x00)
         {}
	       USART2->DR= c;
		 }
		 else if(urt == 3)
		 {
		    while(( USART3->SR &(1<<6))==0x00)
         {}
	       USART3->DR= c;
		 }
	}
	
void usart_SendMsg(unsigned urt,char str[])
	{
    int i =0;
    while (str[i]!='\0')
		{
		  usart_tx(urt,str[i]);
			i++;
		}
	}
	/// clear char string



	
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
/// Sends msg  
void UART_ISR(unsigned short urt,unsigned short urt_mgr[],char Str[])
	{
		if (urt_mgr[2] == 0) /// If there is no bridge
			{
				Str[urt_mgr[0]]= usart_rx(urt);
				
				 if (urt_mgr[3]==1)// Terminatior is on 
					 { 
							if (Str[urt_mgr[0]]==urt_mgr[4]) /// if there is terminator charctar
								{
									urt_mgr[0] = 0;
									urt_mgr[1]=1;
								}
						else
								{
								 urt_mgr[0] = urt_mgr[0]+1;
								}
					 }
					else /// if tthere is no terminator and there is timer inttrupt
					{ 
						urt_mgr[0]++;
						urt_mgr[6]=urt_mgr[5];
						systick_init_timer();
						
					}
			 
			}
		else /// If there is bridge 
			{
			 usart_tx(urt_mgr[2],usart_rx(urt));
			}
			
	}
	
///
void UART_TIMER_ISR(unsigned short urt1_mgr[],unsigned short urt2_mgr[],unsigned short urt3_mgr[])
	{
		if (urt1_mgr[0]!=0)
			{
				if (urt1_mgr[6]==0)
					{
					 urt1_mgr[0]=0;
					 urt1_mgr[1]=1;
					 systick_init_timer();
					}
				else
					{
						urt1_mgr[6]--;
					}
			
			}
		if (urt2_mgr[0]!=0)
			{
				if (urt2_mgr[6]==0)
					{
					 urt2_mgr[0]=0;
					 urt2_mgr[1]=1;
					 systick_init_timer();
					}
				else
					{
						urt2_mgr[6]--;
					}
			
			}
		if (urt3_mgr[0]!=0)
			{
				if (urt3_mgr[6]==0)
					{
					 urt3_mgr[0]=0;
					 urt3_mgr[1]=1;
					 systick_init_timer();
					}
				else
				{
					urt3_mgr[6]--;
				}
			}
	}	
 // send urt msg set and clear signal 
void usart_msg(unsigned short urt,unsigned short urt_mgr[],char str[])
	{
		usart_SendMsg(urt,str);
		unsigned timeout= 720000;
		while ((urt_mgr[1]== 0) &(timeout!=0))
			{ 
			 timeout--;
			}
		urt_mgr[1]=0;

	}
	
