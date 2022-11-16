/*
 * GccApplication1.c
 *
 * Created: 11/8/2022 4:54:13 PM
 * Author : A01338896
 */

#include "sam.h"

#define PINCFG_CONFIG_VALUE 0b00000000
#define GENDIV_CONFIG_VALUE 0
#define GENCTRL_CONFIG_VALUE 0x10600
#define CLKCTRL_CONFIG_VALUE 0x401B
#define COUNT_CONFIG_VALUE 0
#define CTRLA_CONFIG_VALUE 0x400
#define CTRLBSET_CONFIG_VALUE 0
#define INTFLAG_CONFIG_VALUE 0x1
#define CTRLA_MASK_VALUE 0x2

#define VALUE_8BIT 0x80
#define VALUE_2BIT 0x1

void portConfig()
{
    // PORT configuration for general-purpose PIN
    PORT->Group[0].PINCFG[14].reg = PINCFG_CONFIG_VALUE;
    PORT->Group[0].DIRSET.reg = PORT_PA14;
}

void timerConfig()
{
    // Configure the POWER MANAGER to enable the TC3 module
    PM->APBCMASK.reg = PM->APBCMASK.reg | PM_APBCMASK_TC3;

    // Configure the GENERIC CLOCK CONTROL used by the TC3 module
    GCLK->GENDIV.reg = GENDIV_CONFIG_VALUE;
    GCLK->GENCTRL.reg = GENCTRL_CONFIG_VALUE;
    GCLK->CLKCTRL.reg = CLKCTRL_CONFIG_VALUE;

    TC3->COUNT16.COUNT.reg = COUNT_CONFIG_VALUE;
    TC3->COUNT16.CTRLA.reg = CTRLA_CONFIG_VALUE;
    TC3->COUNT16.CTRLBSET.reg = CTRLBSET_CONFIG_VALUE;
    TC3->COUNT16.INTFLAG.reg = INTFLAG_CONFIG_VALUE;

    TC3->COUNT16.CTRLA.reg = TC3->COUNT16.CTRLA.reg | CTRLA_MASK_VALUE;

    while (1)
    {
        if ((TC3->COUNT16.STATUS.reg & VALUE_8BIT) == 0)
        {
            break;
        }
    }
}

int main(void)
{
    /* Initialize the SAM system */
    SystemInit();
    // PORT configuration for general-purpose PIN
    portConfig();
    // TIMER configuration
    timerConfig();

    while (1)
    {
        if ((TC3->COUNT16.INTFLAG.reg & VALUE_2BIT) != 0)
        {
            PORT->Group[0].OUTTGL.reg = PORT_PA14;

            TC3->COUNT16.INTFLAG.reg = INTFLAG_CONFIG_VALUE;
            TC3->COUNT16.COUNT.reg = COUNT_CONFIG_VALUE;
        }
    }
}