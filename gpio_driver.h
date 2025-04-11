#define RCC_APB2EN   (*((volatile unsigned long*) 0x40021018))

#define GPIO_PORT_A  (*((volatile unsigned long*) 0x40010800))
#define GPIO_PORT_B  (*((volatile unsigned long*) 0x40010C00))
#define GPIO_PORT_C  (*((volatile unsigned long*) 0x40011000))


/// port number
# define PortA 1
# define PortB 2
# define PortC 3

/// direction 
# define IN 0 
# define out10 1
# define out2 2 
# define out50 3

/// Output option
# define O_GP_PP 0
# define O_GP_OD 1
# define O_AP_PP 2
# define O_AF_OD 3

/// input option 
# define I_GP_AI 0
# define I_GP_FI 1
# define I_GP_PP 2

// 
# define HIGH 1
# define LOW 0

void Gpio_init(unsigned short port , unsigned short pin , unsigned short dir, unsigned short dir_opt);
int Gpio_read(unsigned short port,unsigned short pin);
void Gpio_write(unsigned short  port, unsigned short pin , unsigned short value);
void Gpio_Toggle(unsigned short port, unsigned short pin);

