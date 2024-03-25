
//uart


#define RCGCUART (*((volatile int *) 0x400FE618))
#define GPIO_PORTA_DEN (*((volatile int *) 0x4000451C))
#define GPIO_PORTA_DIR   (*((volatile int *) 0x40004400))
#define GPIO_PORTA_AFSEL (*((volatile int *) 0x40004420))
#define GPIO_PORTA_PCTL (*((volatile int *) 0x4000452C))
#define PORT_A_PIN_DATA_LIGHT  (*((volatile int *) 0x40004010))
#define PORT_A_PIN_DATA_BUTTON (*((volatile int *) 0x40004080))


#define GPIO_PORTA_IS (*((volatile int *) 0x40004404))
#define GPIO_PORTA_IBE (*((volatile int *) 0x40004408))
#define GPIO_PORTA_IEV (*((volatile int *) 0x4000440C))
#define GPIO_PORTA_ICR (*((volatile int *) 0x4000441C))
#define GPIO_PORTA_IM (*((volatile int *) 0x40004410))
#define NVIC (*((volatile int *) 0xE000E100))
#define GPIOMIS (*((volatile int *) 0x40004418))



//timer registers
#define RCGCTIMER (*((volatile int *) 0x400FE604))
#define GPTMCTL (*((volatile int *) 0x4003000C))
#define GPTMCFG (*((volatile int *) 0x40030000))
#define GPTMTAMR (*((volatile int *) 0x40030004))
#define GPTMIMR (*((volatile int *) 0x40030018))
#define GPTMICR (*((volatile int *) 0x40030024))
#define GPTMRIS (*((volatile int *) 0x4003001C))
#define GPTMTAILR (*((volatile int *) 0x40030028))
#define GPTMTAPR (*((volatile int *) 0x40030038))
#define ENO (*((volatile int *) 0xE000E100))
#define GPTMMIS (*((volatile int *) 0x40030020))
#define NVIC (*((volatile int *) 0xE000E100))


#define UART_INT (*((volatile int *) 0x4000C024))
#define UART_FRAC (*((volatile int *) 0x4000C028))
#define UART_CTL (*((volatile int *) 0x4000C030))
#define UART_LCRH (*((volatile int *) 0x4000C02C))
#define UART_FR (*((volatile int *) 0x4000C018))
#define UART_TDR (*((volatile int *) 0x4000C000))


#define GPIO_PORTA_PIN 0x03
#define GPIO_PORTA_PIN_2 0x04 //light pin
#define GPIO_PORTA_PIN_5 0x20 //button pin
#define GPIO_PORTA_PINS 0x24


#define UARTEN_RX 0x301
#define BIT8_NOPARITRY_1STOP_NOFIFO 0x60


#define SYSCTL_RCGCGPIO_R   (*((volatile int *) 0x400FE608))
#define SYSCTL_RCGC_GPIO_BD 0x01

#define LED_ON2   0x04
#define LED_OFF2  0x00


#define PORT_E_DIR (*((volatile int *) 0x40024400))
#define PORT_D_DIR (*((volatile int *) 0x40007400))
#define PORT_E_DEN (*((volatile int *) 0x4002451C))
#define PORT_D_DEN (*((volatile int *) 0x4000751C))
#define PORT_E_PDR (*((volatile int *) 0x40024514))
#define PORT_E_DATA (*((volatile int *) 0x40024078))
#define PORT_D_DATA (*((volatile int *) 0x4000703C))
#define PORT_D_PDR (*((volatile int *) 0x40007514))



unsigned int i = 0;
void Delay(unsigned int);
char UART_Rx ();
void UART_Tx (char data);
int main(void)
{
    //SYSCTL_RCGCGPIO_R |= SYSCTL_RCGC_GPIO_BD;
    SYSCTL_RCGCGPIO_R |= 0x19;
    GPIO_PORTA_DEN |= GPIO_PORTA_PINS;
    GPIO_PORTA_DIR |= GPIO_PORTA_PIN_2;
    GPIO_PORTA_PCTL &= ~GPIO_PORTA_PIN_2;
    GPIO_PORTA_AFSEL &= ~GPIO_PORTA_PIN_2;



    //enabling the UART and system clocks
       RCGCUART = 0x01;
       SYSCTL_RCGCGPIO_R |= SYSCTL_RCGC_GPIO_BD;


       //configuring the GPIO ports for the UART
       GPIO_PORTA_AFSEL |= GPIO_PORTA_PIN;
       GPIO_PORTA_DEN |= GPIO_PORTA_PIN;
       GPIO_PORTA_PCTL |= 0x00000011;



       //Configuring the UART registers(BAUD rate, parameters for LCRH and enabling the UART)
       UART_CTL = 0x00;
       UART_INT = 0x068;
       UART_FRAC = 0x0B;
       UART_LCRH = BIT8_NOPARITRY_1STOP_NOFIFO;
       UART_CTL = UARTEN_RX;



    //enabling RCGC registers
    RCGCTIMER |= (1<<0);
    GPTMCTL &= ~(1<<0);
    GPTMCFG |= 0x04;
    GPTMTAMR |= 0x02;
    GPTMTAMR &= ~(1<<4);
    GPTMTAILR = 65317;
    GPTMTAPR = 245;
    GPTMICR |= (1<<0);
    GPTMCTL |= (1<<0);

    GPTMIMR |= (1<<0);
    ENO |= (1<<19);


    GPIO_PORTA_IS &= ~(1<<5);
        GPIO_PORTA_IBE &= ~(1<<5);
        GPIO_PORTA_IEV &= ~(1<<5);
        GPIO_PORTA_ICR |= (1<<5);
        GPIO_PORTA_IM|=(1<<5);
        NVIC |= (1<<0);


        //keypad
        PORT_E_DIR |= 0x1E;

        PORT_E_DEN |= 0x1E;

        PORT_D_DEN |= 0x0F;
        PORT_D_DIR &= ~(0x0F);
        PORT_D_PDR |= 0x0F;

        char symbol [4][4] = {{ '1', '4',  '7', '*'},
                              { '2', '5',  '8', '0'},
                              { '3', '6',  '9', '#'},
                              { 'A', 'B',  'C', 'D'}};


    while(1)
    {
        int i , j;
                        for(i = 0; i < 4; i++)
                        {
                          PORT_E_DATA = (1U << (i+1));


                          for(j = 0; j < 4; j++)
                          {

                            if(((PORT_D_DATA & 0xFF)) & ((1U << (j)))){

                                UART_Tx(symbol[i][j]);
                            }
                          }

                        }

    }













    //configuring the GPIO ports of the pins for the light and the button
}

void PortAHandler(void){
   if(GPIOMIS & 0x20){
        char c = '$';
        UART_Tx(c);

    }
    GPIO_PORTA_ICR |= (1<<5);
}

void TIMER0A_Handler(void){
    if(GPTMMIS && 0x01){
        if(i%2==0){
            PORT_A_PIN_DATA_LIGHT  |= LED_ON2;
            i++;
        }else{
            PORT_A_PIN_DATA_LIGHT  &= ~LED_ON2;
            i++;
        }


    }
    GPTMICR |= (1<<0);
}

void UART_Tx (char data) {
    while((UART_FR & 0x20));
    UART_TDR = data;
}

char UART_Rx () {
    char data;
    while((UART_FR & 0x10));
    data = UART_TDR;
    return ((unsigned char) data);
}
