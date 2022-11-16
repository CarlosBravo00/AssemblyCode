#ifndef MY_I2C_H_
#define MY_I2C_H_

#include "stdbool.h"

volatile uint32_t i;

/**
 * @brief initializes the configuration for the use of I2C
 */
void InitI2C()
{
    SYSCTRL->OSC8M.bit.PRESC = 0;

    /* port mux configuration */
    PORT->Group[0].PINCFG[PIN_PA22].reg = PORT_PINCFG_PMUXEN | PORT_PINCFG_INEN | PORT_PINCFG_PULLEN; /* SDA */
    PORT->Group[0].PINCFG[PIN_PA23].reg = PORT_PINCFG_PMUXEN | PORT_PINCFG_INEN | PORT_PINCFG_PULLEN; /* SCL */

    /* PMUX: even = n/2, odd: (n-1)/2 */
    PORT->Group[0].PMUX[11].reg |= 0x02u;
    PORT->Group[0].PMUX[11].reg |= 0x20u;

    /* APBCMASK */
    PM->APBCMASK.reg |= PM_APBCMASK_SERCOM3;

    /*GCLK configuration for sercom3 module*/
    GCLK->CLKCTRL.reg = GCLK_CLKCTRL_ID(SERCOM3_GCLK_ID_CORE) |
                        GCLK_CLKCTRL_ID(SERCOM3_GCLK_ID_SLOW) |
                        GCLK_CLKCTRL_GEN(4) |
                        GCLK_CLKCTRL_CLKEN;
    GCLK->GENCTRL.reg |= GCLK_GENCTRL_SRC_OSC8M | GCLK_GENCTRL_GENEN | GCLK_GENCTRL_ID(4);

    /* set configuration for SERCOM3 I2C module */
    SERCOM3->I2CM.CTRLB.reg = SERCOM_I2CM_CTRLB_SMEN; /* smart mode enable */
    while (SERCOM3->I2CM.SYNCBUSY.reg)
        ; // waiting loading

    /* calculate BAUDRATE */
    uint64_t tmp_baud = ((8000000 / 100000) - 10 - (8000000 * 250 / 1000000000)) / 2;
    SERCOM3->I2CM.BAUD.bit.BAUD = SERCOM_I2CM_BAUD_BAUD((uint32_t)tmp_baud);
    while (SERCOM3->I2CM.SYNCBUSY.reg)
        ; // waiting loading
    // value equals 0x22 or decimal 34

    SERCOM3->I2CM.CTRLA.reg = SERCOM_I2CM_CTRLA_ENABLE |          /* enable module */
                              SERCOM_I2CM_CTRLA_MODE_I2C_MASTER | /* i2c master mode */
                              SERCOM_I2CM_CTRLA_SDAHOLD(3);       /* SDA hold time to 600ns */
    while (SERCOM3->I2CM.SYNCBUSY.reg)
        ; /* waiting loading */

    SERCOM3->I2CM.STATUS.reg |= SERCOM_I2CM_STATUS_BUSSTATE(1); /* set to idle state */
    while (SERCOM3->I2CM.SYNCBUSY.reg)
        ; /* waiting loading */
}

/**
 * @brief writes the data located in the array to the RTC.
 * @param[in] SlAddr slave address.
 * @param[in] ptrData pointer to the 8-bit data array.
 * @param[in] Size number of elements in the array.
 */
void sendI2CDataArray(uint8_t SlAddr, uint8_t *ptrData, uint8_t Size)
{

    SERCOM3->I2CM.ADDR.reg = (SlAddr << 1) | 0;
    while (!SERCOM3->I2CM.INTFLAG.bit.MB)
        ;

    for (i = 0; i < Size; i++)
    {
        SERCOM3->I2CM.DATA.reg = ptrData[i];
        while (!SERCOM3->I2CM.INTFLAG.bit.MB)
        {
        };
    }
}

/**
 * @brief Sends data by serial communication with I2C protocol3
 * @param[in] SlAddr slave address.
 * @param[in] Data 8-bit data to be sent.
 */
void SendI2CData(uint8_t SlAddr, uint8_t Data)
{
    SERCOM3->I2CM.ADDR.reg = (SlAddr << 1) | 0; /* Sending slave address in write mode */

    while (SERCOM3->I2CM.INTFLAG.bit.MB == 0)
        ;                          /* MB = 1 if slave NACKS the address */
    SERCOM3->I2CM.DATA.reg = Data; /* Sending address (seconds) for internal pointer */

    while (SERCOM3->I2CM.INTFLAG.bit.MB == 0)
    {
    }; /* MB = 1 if slave NACKS the address */

    SERCOM3->I2CM.CTRLB.bit.CMD = 0x1; /* Sending repetead start condition */
}

/**
 * @brief Sends byte to generate stop condition.
 */
void StopCond()
{
    SERCOM3->I2CM.CTRLB.bit.CMD = 0x3;
}

/**
 * @brief Reads the data from the RTC and stores it in the Data array.
 * @param[in] SlAddr slave address.
 * @param[in] ptrData pointer to the 8-bit data array.
 * @param[in] Size number of elements in the array.
 */
void receiveI2CDataArray(uint8_t SlAddr, uint8_t *ptrData, uint8_t Size)
{
    SERCOM3->I2CM.ADDR.reg = (SlAddr << 1) | 1;
    while (SERCOM3->I2CM.INTFLAG.bit.SB == 0)
    {
    };

    for (i = 0; i < Size - 1; i++)
    {
        ptrData[i] = SERCOM3->I2CM.DATA.reg;
        while (SERCOM3->I2CM.INTFLAG.bit.SB == 0)
        {
        };
    }
}

#endif