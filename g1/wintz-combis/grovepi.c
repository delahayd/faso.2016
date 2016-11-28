// grovepi.c

#include "grovepi.h"

int fd;													
char *fileName = "/dev/i2c-1";								
int  address = 0x04;									
unsigned char w_buf[5],ptr,r_buf[32];	
unsigned long reg_addr=0;    

#define dbg 0
int init(void)
{
}

//Write a register
int write_block(char cmd,char v1,char v2,char v3)
{			
}

//write a byte to the GrovePi
int write_byte(char b)
{
}

//Read 1 byte of data
char read_byte(void)
{
}

//Read a 32 byte block of data from the GrovePi
char read_block(void)
{
}

void pi_sleep(int t) 
{
}

// Read analog value from Pin
int analogRead(int pin)
{
}

//Write a digital value to a pin
int digitalWrite(int pin,int value)
{
}

//Set the mode of a pin
//mode
//	1: 	output
//	0:	input
int pinMode(int pin,int mode)
{
}

//Read a digital value from a pin
int digitalRead(int pin)
{
}

//Write a PWM value to a pin
int analogWrite(int pin,int value)
{
}
