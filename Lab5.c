#include <bcm2835.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
 
#define MODE_READ 0
#define MODE_WRITE 1
 
#define MAX_LEN 32
 
char wbuf[MAX_LEN];
char buf[MAX_LEN];

char arrDays[7][20] = { "Mon", "Tue", "Wed", "Thu", "Fri", "Sat", "Sun" };

 
uint16_t clk_div = BCM2835_I2C_CLOCK_DIVIDER_148;
uint8_t slave_address = 0x00;
uint32_t len = 0;

uint8_t data;
 
int i;
uint8_t dataTemp;
uint8_t dataCLK;

char str[648];
char strTime[3][648];
char sendStr[1000];


int main(int argc, char **argv) {
    printf("Running ... \n");

    if (!bcm2835_init())
    {
      printf("bcm2835_init failed. Are you running as root??\n");
      return 1;
    }
    if (!bcm2835_i2c_begin())
    {
        printf("bcm2835_i2c_begin failed. Are you running as root??\n");
        return 1;
    }
    
    FILE* fp;  
    printf("Connected ... \n");
    int cont = 0;
    int contStr = 0;
    int result;
    while(1){     
        bcm2835_i2c_setClockDivider(256);
        bcm2835_i2c_setSlaveAddress(77);
        wbuf[0] = 0x0;
        dataTemp = bcm2835_i2c_write(wbuf, 1);
        if(dataTemp == 0){
            for (i=0; i<MAX_LEN; i++) buf[i] = 'n';
            bcm2835_i2c_read(buf, 1);
            if(buf[0] != 'n'){
              result = (unsigned char)buf[0];
              printf("Temperatura = %d\n", result);
              sprintf(str, "Temperatura = %d\n", result);
            } 
        }
        delay(500);
        cont++;
        if(cont >= 20 || result >= 30){
            cont = 0;
            bcm2835_i2c_setSlaveAddress(104);
            wbuf[0] = 0x0;
            dataTemp = bcm2835_i2c_write(wbuf, 1);
            if(dataTemp == 0){
                for (i=0; i<MAX_LEN; i++) buf[i] = 'n';
                bcm2835_i2c_read(buf, 7);
                char timeDay[2] = "AM";
                if(buf[2] >= 0x12) timeDay[0] = 'P';
                printf("%x/%x/%x %s %02x:%02x:%02x %s \n", buf[4], buf[5], buf[6], arrDays[buf[3]], buf[2], buf[1], buf[0], timeDay);
                sprintf(strTime[contStr], "%x/%x/%x %s %02x:%02x:%02x %s \n", buf[4], buf[5], buf[6], arrDays[buf[3]], buf[2], buf[1], buf[0], timeDay);
                contStr++;
                if(contStr == 3) contStr = 0;
            }
        }
        fp = fopen("output.txt", "w");
        sprintf(sendStr, "%sRecord 1: %sRecord 2: %sRecord 3: %s", str, strTime[0], strTime[1], strTime[2]);
        fprintf(fp, sendStr);
        fclose(fp);
    }
          
    return 0;
}


 
