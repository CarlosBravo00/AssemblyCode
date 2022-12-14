/*
 * main.c
 *
 * Created: 01/11/2017 08:47:35 p. m.
 *  Author: L00254193
 */

#include "sam.h"
#include "myprintf.h"
#include "my_i2c.h"

void UARTInit(void);

#define SLAVE_ADDR 0x68u
#define BUF_SIZE 8
#define SEC_ADDR 0x0u
char arrDays[7][20] = {"Mon", "Tue", "Wed", "Thu", "Fri", "Sat", "Sun"};

// Control variables for data transfer and reception
volatile uint32_t i;
uint8_t tx_buf[BUF_SIZE] = {SEC_ADDR, 0x00, 0x14, 0x15, 0x01, 0x14, 0x11, 0x22};
uint8_t rx_buf[BUF_SIZE];

int main(void)
{
    UARTInit();

    InitI2C();
    sendI2CDataArray(SLAVE_ADDR, tx_buf, BUF_SIZE);
    StopCond();
    char buff[31];
    buff[30] = '\0';
    char timeDay[2] = "AM";
    while (1)
    {
        SendI2CData(SLAVE_ADDR, SEC_ADDR);
        receiveI2CDataArray(SLAVE_ADDR, rx_buf, BUF_SIZE);
        StopCond();

        if (rx_buf[2] >= 0x12)
            timeDay[0] = 'P';
        mysnprintf(buff, sizeof buff, "%x/%x/%x %s %02x:%02x:%02x %s", rx_buf[4], rx_buf[5], rx_buf[6], arrDays[rx_buf[3]], rx_buf[2], rx_buf[1], rx_buf[0], timeDay);
        myprintf("\n%s", buff);
    }
    return 0;
}

void UARTInit(void)
{
    /* Initialize the SAM system */
    SystemInit();
    /* Switch to 8MHz clock (disable prescaler) */
    SYSCTRL->OSC8M.bit.PRESC = 0;

    /* port mux configuration*/
    PORT->Group[0].DIR.reg |= (1 << 10);            /* Pin 10 configured as output */
    PORT->Group[0].PINCFG[PIN_PA11].bit.PMUXEN = 1; /* Enabling peripheral functions */
    PORT->Group[0].PINCFG[PIN_PA10].bit.PMUXEN = 1; /* Enabling peripheral functions */

    /*PMUX: even = n/2, odd: (n-1)/2 */
    PORT->Group[0].PMUX[5].reg |= 0x02; /* Selecting peripheral function C */
    PORT->Group[0].PMUX[5].reg |= 0x20; /* Selecting peripheral function C */

    /* APBCMASK */
    // PM->APBCMASK.reg |= PM_APBCMASK_SERCOM0;			  /* SERCOM 0 enable*/
    PM->APBCMASK.reg |= PM_APBCMASK_SERCOM0;

    /*GCLK configuration for sercom0 module: using generic clock generator 0, ID for sercom0, enable GCLK*/

    GCLK->CLKCTRL.reg = GCLK_CLKCTRL_ID(SERCOM0_GCLK_ID_CORE) |
                        GCLK_CLKCTRL_CLKEN | GCLK_CLKCTRL_GEN(0);

    /* configure SERCOM0 module for UART as Standard Frame, 8 Bit size, No parity, BAUDRATE:9600*/

    SERCOM0->USART.CTRLA.reg =
        SERCOM_USART_CTRLA_DORD | SERCOM_USART_CTRLA_MODE_USART_INT_CLK |
        SERCOM_USART_CTRLA_RXPO(3 /*PAD3*/) | SERCOM_USART_CTRLA_TXPO(1 /*PAD2*/);

    uint64_t br = (uint64_t)65536 * (8000000 - 16 * 9600) / 8000000;

    SERCOM0->USART.CTRLB.reg = SERCOM_USART_CTRLB_RXEN | SERCOM_USART_CTRLB_TXEN | SERCOM_USART_CTRLB_CHSIZE(0 /*8 bits*/);

    SERCOM0->USART.BAUD.reg = (uint16_t)br;

    SERCOM0->USART.CTRLA.reg |= SERCOM_USART_CTRLA_ENABLE;
}