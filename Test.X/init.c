/**
 * initializations of the dsPIC
 * timers, ports...
 */
 #include <p33Fxxxx.h>

/*function used to init every peripheral of the bluetooth card*/
void initPorts()
{
	//initialization of the remappable pins
	// Assign UART1 Transmit (U1TX) Function is Assigned to RP21 Output Pin bits
  RPOR10bits.RP21R = 0b00011;//RP21
  // Assign UART1 Receive (U1RX) to RP20
  RPINR18bits.U1RXR = 0b10100;//RP20

  //initialization of the Servo ports as outputs
  /*TRISBbits.TRISB2 = 0;
  TRISBbits.TRISB7 = 0;*/

  //initialization of the ports used for the allegro
  TRISBbits.TRISB3 = 0; //mode1 => output (same port for both modes)
  //TRISBbits.TRISB4 = 0; //mode2 => output
  LATBbits.LATB3 = 1; //slow decay : 1, fast decay : 0
  LATBbits.LATB4 = 1; //slow decay : 1, fast decay : 0

  TRISBbits.TRISB12 = 0; //phase2 => output
  TRISBbits.TRISB13 = 0; //enable2 => output

  TRISBbits.TRISB14 = 0; //phase1  => output
  TRISBbits.TRISB15 = 0; //enable2 => output

  TRISBbits.TRISB0 = 1; //sense1 => input
  TRISBbits.TRISB1 = 1; //sense2 => input


  //encoders
  RPINR14bits.QEA1R = 0b111;    //channel A encoder 1 => RP7  **5V tolerent**
  RPINR14bits.QEB1R = 0b1000;   //channel B encoder 1 => RP8  **5V tolerent**


  //two more pwm
  /*TRISBbits.TRISB10 = 0; //pwm3
  TRISCbits.TRISC6 = 0; //pwm4
  TRISAbits.TRISA0 = 1; //ADC => input
  TRISAbits.TRISA1 = 1;
  TRISCbits.TRISC1 = 1;
  TRISCbits.TRISC2 = 1;

  //GPIO outs
  TRISAbits.TRISA8 = 0;
  TRISAbits.TRISA2 = 0;
  TRISAbits.TRISA3 = 0;
  TRISAbits.TRISA4 = 0;

  //GPIO ins
  TRISAbits.TRISA10 = 1; //GPIO1
  TRISAbits.TRISA7 = 1;  //GPIO2
  TRISBbits.TRISB8 = 1;  //GPIO7
  TRISBbits.TRISB9 = 1;  //GPIO8
  //TRISBbits.TRISB10 = 1; //GPIO9(used by pwm module)
  TRISBbits.TRISB11 = 1; //GPIO10
  TRISCbits.TRISC7 = 1; //GPIO9 (new one)*/

}
