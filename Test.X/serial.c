/**
 * Comp ort functions to communicate with the bluetooth module.
 */

#include <p33FJ16MC304.h>
#include "uart.h"
#include "serial.h"
#include "ALTypes.h"
#include "pll.h"

#define FBAUD  (115200)
#define FRAME_LENGTH (24)
#define DATA_LENGTH (16)


volatile int cnt = 0;



void initSerial(void)
{
	uInt16 baud = (unsigned int)(((float)FCY/(float)FBAUD)/(float)4+0.5)-1;

  U1MODEbits.UARTEN = 1; // Enable UART1

  U1MODEbits.USIDL = 1; // Continue op�ration when entering idle mode
  //U1MODEbits.ALTIO = 0; // Do not use alternate IO UART pins, use U1TX and U1RX
  U1MODEbits.WAKE = 1; // Enable wake up on start bit
  U1MODEbits.LPBACK = 0; // No loopback mode
  U1MODEbits.ABAUD = 0; // No auto baud, input captute from ICx
  U1MODEbits.URXINV = 0; // Idle state is "1"
  U1MODEbits.PDSEL = 0; // 8 bit data, no parity
  U1MODEbits.STSEL = 0; // 1 stop bit

  U1STAbits.UTXISEL0 = 0; // transmission interrupt when there is a byte transfered to the shift register
  U1STAbits.UTXISEL1 = 0; // transmission interrupt when there is a byte transfered to the shift register
  U1STAbits.UTXBRK = 0; // no break bit
  U1STAbits.UTXEN = 1; // UART transmitter enable
  U1STAbits.URXISEL = 0; // Interrupt when each caracter is received
  U1STAbits.ADDEN = 0; // No address mode (no 9 bits mode)

  U1MODEbits.BRGH = 1; // Speed / 4

  U1BRG = baud; // Set baud rate

	// Clear the interrupt flag
	IFS0bits.U1RXIF = 0;
	IFS0bits.U1TXIF = 0;

  // average interruption priority
  //_U1RXIP = UART_INTERRUPT_TX_U1TXIP;
  //_U1TXIP = UART_INTERRUPT_RX_U1RXIP;

  // Enable interruption
	IEC0bits.U1RXIE = 1;
	IEC0bits.U1TXIE = 1;

	//initialization of the frames that receive the data from Nao.
	initRcvFrame();
}

uInt16 checksum(uInt8* data)
{
  uInt16 checksum = 0x0000;
  int i;
  volatile uInt16 tmpX = 0x0000;
  for(i=4;i<20;i++) //parcours des data de la trame
  {
    checksum = checksum ^ data[i];
    tmpX = checksum & 0x8000;
    if(tmpX)
    {
      checksum<<= 1;
      checksum+=1;
    }
    else checksum<<=1;
  }
  return checksum;
}


volatile uInt8 length = 0;
volatile uInt8 bufIndex = 0;
volatile uInt8 serialTram[24];
volatile uInt8 send = 0;
volatile uInt8 read = 0;
volatile uInt8 rcvTram[24];
volatile uInt8 rcvData[16];
volatile uInt8 rcvbuff[24];

void initRcvFrame(void)
{
  int i;

  for(i=0;i<DATA_LENGTH;i++)
  {
    rcvData[i]=0;
  }
  for(i=0;i<FRAME_LENGTH;i++)
  {
    rcvTram[i]=0;
  }
}

int dumbCount = 0;
/*
* Function that builds the Frame to be sent
*
*/
void buildFrame(void)
{
  int i;
  uInt8 cs1;
  uInt8 cs2;
  uInt16 csGlobal;
  uInt16 temp;

  uInt16 adc;
  uInt16 adcTmp;

  //SOF
  serialTram[0] = 0x55; //SOF
  serialTram[1] = 0xFF;
  serialTram[2] = 0x22;
  serialTram[3] = 0x33;

  //EOF
  serialTram[22] = 0x99; //EOF
  serialTram[23] = 0xFF;

  serialTram[5] = dumbCount;
  dumbCount++;
  if(dumbCount>200) dumbCount = 0;


  //Mise des valeurs des ADC dans les 8 premiers octets
  //Mise des valeurs des GPIO en input dans le 9e

  //for(i=4;i<20;i++) serialTram[i] = 45+3*i;//code provisoire de remplissage
  //remplissage des valeurs de l'ADC
  //fillADC();

  //remplissage des valeurs des GPIO ins

  //fillGPIOin();

  //calcul du CRC
  if(send == 0)
  {
    csGlobal = checksum(serialTram);
    temp = (csGlobal & 0xff00);
    temp >>= 8;
    cs1 = temp;
    temp = (csGlobal & 0x00ff);
    cs2 = temp;
    serialTram[20] = cs1;
    serialTram[21] = cs2;
    length = 24;
    bufIndex = 0;
    send = 1;
    U1TXREG = serialTram[0];
  }
}

/*void fillADC(void) //function that fills the ADC values in the data frame
{
  uInt16 adc;
  uInt16 adcTmp;
  uInt8 i;

  for(i = 0; i < ADC_NB; i++)
  {
    adc = getADC(i);
    adcTmp = (adc & 0xff00) >> 8;
    serialTram[i * 2 + 4] = adcTmp;
    adcTmp = adc & 0x00ff;
    serialTram[i * 2 + 5] = adcTmp;
  }
}*/

/*volatile uInt8 gpio = 0;

void fillGPIOin(void)
{
  gpio = 0;

  if(PORTAbits.RA10)
    gpio |= 1<<0;
  if(PORTAbits.RA7)
    gpio |= 1<<1;
  if(PORTBbits.RB8)
    gpio |= 1<<2;
  if(PORTBbits.RB9)
    gpio |= 1<<3;
  if(PORTBbits.RB11)
    gpio |= 1<<4;
  if(PORTCbits.RC7)
    gpio |= 1<<5;

  serialTram[GPIO_IN] = gpio;
}
*/

volatile uInt8 fillNext = 0;

void readFrame()
{
  uInt16 cs = 0;
  uInt16 i,j;
  uInt16 tmpX = 0;

  if(fillNext == 1)
  {
    rcvTram[0] = 0x55;
    rcvTram[1] = 0xFF;
    rcvTram[2] = 0x22;
    rcvTram[3] = 0x33;
    cnt = 4;
    fillNext = 0;
  }


  if ( cnt == 1 && rcvTram[cnt-1] != 0x55){		// Detect SOF first byt
    cnt = 0;}

  if ( cnt == 2 && rcvTram[cnt-1] != 0xFF){		// Detect SOF second byte
    cnt = 0;}

  if ( cnt == 3 && rcvTram[cnt-1] != 0x22){		// Detect SOF third byte
    cnt = 0;}

  if ( cnt == 4 && rcvTram[cnt-1] != 0x33){		// Detect SOF fourth byte
    cnt = 0;}

  if ( cnt > 24 -3 && rcvTram[cnt-1] == 0xFF && rcvTram[cnt-2] == 0x99 )	// Detect EOF : if counter match frame length byte (globalFrame[2]) and last bytes values are 0x0A 0x0A (end of sensor) or 0x99 0xFF (end of frame), then break
  {
    //verify checksum
    cs = 0;
    for(i=4;i<20;i++)
    {
      cs ^= rcvTram[i];
      tmpX = cs & 0x8000;
        if(tmpX)
        {
          cs <<= 1;
          cs += 1;
        }
        else
        {
          cs <<= 1;
        }
    }
    if(cs == rcvTram[20] * 256 + rcvTram[21])
    {
      j = 0;
      for(i = 4; i < 20; i++)
      {
        //we get only the data in the frame
        rcvData[j] = rcvTram[i];
        j++;
      }
    }
    cnt=0;
  }

   if ( cnt > 24 -5 && rcvTram[cnt-1] == 0x33 && rcvTram[cnt-2] == 0x22 && rcvTram[cnt-3] == 0xFF && rcvTram[cnt-4] == 0x55 )	// Detect EOF : if counter match frame length byte (globalFrame[2]) and last bytes values are 0x0A 0x0A (end of sensor) or 0x99 0xFF (end of frame), then break
  {
    fillNext = 1;
  }

  if(cnt>24) cnt=0;
}

uInt16 getSerialUInt16(uInt8 buffPosition)
{
  return (((uInt16)(rcvData[buffPosition]) << 8) +(uInt16)(rcvData[buffPosition + 1]));
}

uInt8 getSerialUInt8(uInt8 buffPosition)
{
  return rcvData[buffPosition];
}

//interrupt definitions
//RX interrupt
void __attribute__((__interrupt__, __no_auto_psv__)) _U1RXInterrupt(void)
{
  LATCbits.LATC7 = 1;

	// Clear the interrupt flag
	IFS0bits.U1RXIF = 0;

  while(U1STAbits.URXDA)
  {
    rcvTram[cnt] = U1RXREG;

  	//increment the frame reception counter
  	cnt++;
  }

}


//Tx interrupt
void __attribute__((__interrupt__, __no_auto_psv__)) _U1TXInterrupt(void)
{
  LATCbits.LATC7 = 1;
  IFS0bits.U1TXIF = 0;
	// Send message next byte
	if (length)
	{
		if (bufIndex==0)
			bufIndex++;

		if (bufIndex<length)
		{
   	 //Send new byte, if there is one ..
  		U1TXREG = serialTram[bufIndex];
			bufIndex++;

		}
		else
		{
		  length = 0;
		  send = 0;
		}
	}
}

void serialTask()
{
  buildFrame();
  readFrame();
}
