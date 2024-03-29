//===============================================================
// FILE:   DeviceInit_18Nov2018.c
//
// DESC:   Peripheral Initialization for F2802x
// 
// Version:     1.2
//
// Modified by: DNR 18Nov2018 for use with SYS/BIOS
//===============================================================

#include "Peripheral_Headers/F2802x_Device.h"
#include "Peripheral_Headers/F2802x_Sci.h"


//function prototypes:
extern void DelayUs(Uint16);
void scia_txmit(int a);
void scia_msg(char *msg);
void sci_init(void);

void DeviceInit(void);

#define CPU_FREQ    60E6        // Default = 15 MHz. Change to 60E6 for 60 MHz devices
#define LSPCLK_FREQ CPU_FREQ/4
#define SCI_FREQ    100E3
#define SCI_PRD     (LSPCLK_FREQ/(SCI_FREQ*8))-1

//---------------------------------------------------------------
//  Configure Device for target Application Here
//---------------------------------------------------------------
void DeviceInit(void)
{
   EALLOW; // temporarily unprotect registers

// LOW SPEED CLOCKS prescale register settings
   SysCtrlRegs.LOSPCP.all = 0x0002; // Sysclk / 4 (15 MHz)
   //SysCtrlRegs.LOSPCP.bit.LSPCLK = 0; // Low speed clock = SYSCLKOUT/1
   SysCtrlRegs.XCLK.bit.XCLKOUTDIV = 2;
      	
// PERIPHERAL CLOCK ENABLES 
//---------------------------------------------------
// If you are not using a peripheral you may want to switch
// the clock off to save power, i.e., set to =0 
// 
// Note: not all peripherals are available on all 280x derivates.
// Refer to the datasheet for your particular device. 

   SysCtrlRegs.PCLKCR0.bit.ADCENCLK = 0;    // ADC
   //------------------------------------------------
   SysCtrlRegs.PCLKCR3.bit.COMP1ENCLK = 0;	// COMP1
   SysCtrlRegs.PCLKCR3.bit.COMP2ENCLK = 0;	// COMP2
   //------------------------------------------------
   SysCtrlRegs.PCLKCR0.bit.I2CAENCLK = 0;   // I2C
   //------------------------------------------------
   SysCtrlRegs.PCLKCR0.bit.SPIAENCLK = 0;	// SPI-A
   //------------------------------------------------
   SysCtrlRegs.PCLKCR0.bit.SCIAENCLK = 1;  	// SCI-A LSPCLK low-speed
   //------------------------------------------------
   SysCtrlRegs.PCLKCR1.bit.ECAP1ENCLK = 0;	//eCAP1
   //------------------------------------------------
   SysCtrlRegs.PCLKCR1.bit.EPWM1ENCLK = 0;  // ePWM1
   SysCtrlRegs.PCLKCR1.bit.EPWM2ENCLK = 0;  // ePWM2
   SysCtrlRegs.PCLKCR1.bit.EPWM3ENCLK = 0;  // ePWM3
   SysCtrlRegs.PCLKCR1.bit.EPWM4ENCLK = 0;  // ePWM4
   //------------------------------------------------
   SysCtrlRegs.PCLKCR0.bit.TBCLKSYNC = 0;   // Enable TBCLK
   //------------------------------------------------
                  
                                     
//---------------------------------------------------------------
// GPIO (GENERAL PURPOSE I/O) CONFIG
//---------------------------------------------------------------
//-----------------------
// QUICK NOTES on USAGE:
//-----------------------
// If GpioCtrlRegs.GP?MUX?bit.GPIO?= 1, 2, or 3 (i.e., Non GPIO func), then leave rest of lines commented
// If GpioCtrlRegs.GP?MUX?bit.GPIO?= 0 (i.e., GPIO func), then:
//	1) uncomment GpioCtrlRegs.GP?DIR.bit.GPIO? = ? and choose pin to be IN or OUT
//	2) If IN, can leave next two lines commented
//	3) If OUT, uncomment line with ..GPACLEAR.. to force pin LOW or
//       uncomment line with ..GPASET.. to force pin HIGH or
//---------------------------------------------------------------
//---------------------------------------------------------------
//  GPIO-00 - PIN FUNCTION = Normally Open pushbutton PIN1 column 4 on keypad (pulled-down)blue LED D2 (rightmost on LaunchPad)
	GpioCtrlRegs.GPAMUX1.bit.GPIO0 = 0; // 0=GPIO,  1=EPWM1A,  2=Resv,  3=Resv
	GpioCtrlRegs.GPADIR.bit.GPIO0 = 1; // 1=OUTput,  0=INput
//	GpioDataRegs.GPACLEAR.bit.GPIO0 = 1; // uncomment if --> Set Low initially
	GpioDataRegs.GPASET.bit.GPIO0 = 1; // uncomment if --> Set High initially
//---------------------------------------------------------------
//  GPIO-01 - PIN FUNCTION = Normally Open pushbutton PIN2 column 3 on keypad (pulled-down)blue LED D4
	GpioCtrlRegs.GPAMUX1.bit.GPIO1 = 0; // 0=GPIO,  1=EPWM1B,  2=EMU0,  3=COMP1OUT
	GpioCtrlRegs.GPADIR.bit.GPIO1 = 1; // 1=OUTput,  0=INput
//	GpioDataRegs.GPACLEAR.bit.GPIO1 = 1; // uncomment if --> Set Low initially
	GpioDataRegs.GPASET.bit.GPIO1 = 1; // uncomment if --> Set High initially
	//GpioCtrlRegs.GPAPUD.bit.GPIO1 = 1; //disable internal pull-up resistor
//---------------------------------------------------------------
//  GPIO-02 - PIN FUNCTION = Normally Open pushbutton PIN3 column 2 on keypad (pulled-down)blue LED D3
	GpioCtrlRegs.GPAMUX1.bit.GPIO2 = 0; // 0=GPIO,  1=EPWM2A,  2=Resv,  3=Resv
	GpioCtrlRegs.GPADIR.bit.GPIO2 = 1; // 1=OUTput,  0=INput
//	GpioDataRegs.GPACLEAR.bit.GPIO2 = 1; // uncomment if --> Set Low initially
	GpioDataRegs.GPASET.bit.GPIO2 = 1; // uncomment if --> Set High initially
	//GpioCtrlRegs.GPAPUD.bit.GPIO2 = 1; //disable internal pull-up resistor
//---------------------------------------------------------------
//  GPIO-03 - PIN FUNCTION = Normally Open pushbutton PIN4 column 1 on keypad (pulled-down)blue LED D5 (leftmost on LaunchPad)
	GpioCtrlRegs.GPAMUX1.bit.GPIO3 = 0; // 0=GPIO,  1=EPWM2B,  2=Resv,  3=COMP2OUT
	GpioCtrlRegs.GPADIR.bit.GPIO3 = 1; // 1=OUTput,  0=INput
//	GpioDataRegs.GPACLEAR.bit.GPIO3 = 1; // uncomment if --> Set Low initially
	GpioDataRegs.GPASET.bit.GPIO3 = 1; // uncomment if --> Set High initially
	//GpioCtrlRegs.GPAPUD.bit.GPIO3 = 1; //disable internal pull-up resistor
//---------------------------------------------------------------
//  GPIO-04 - PIN FUNCTION = Normally Open pushbutton PIN5 row 4 on keypad (pulled-down)--Spare--
	GpioCtrlRegs.GPAMUX1.bit.GPIO4 = 0; // 0=GPIO,  1=EPWM3A, 2=Resv, 	3=Resv
	GpioCtrlRegs.GPADIR.bit.GPIO4 = 0; // 1=OUTput,  0=INput
	GpioDataRegs.GPACLEAR.bit.GPIO4 = 1; // uncomment if --> Set Low initially
//	GpioDataRegs.GPASET.bit.GPIO4 = 1; // uncomment if --> Set High initially
	GpioCtrlRegs.GPAPUD.bit.GPIO4 = 0; //disable internal pull-up resistor
    //GpioIntRegs.GPIOXINT1SEL.bit.GPIOSEL = 4;
    //XIntruptRegs.XINT1CR.bit.POLARITY = 1;
    //XIntruptRegs.XINT1CR.bit.ENABLE = 1;
//---------------------------------------------------------------
//  GPIO-05 - PIN FUNCTION = Normally Open pushbutton PIN6 row 3 on keypad (pulled-down) --Spare--
	GpioCtrlRegs.GPAMUX1.bit.GPIO5 = 0; // 0=GPIO,  1=EPWM3B,  2=Resv,  3=ECAP1
	GpioCtrlRegs.GPADIR.bit.GPIO5 = 0; // 1=OUTput,  0=INput
	GpioDataRegs.GPACLEAR.bit.GPIO5 = 1; // uncomment if --> Set Low initially
//	GpioDataRegs.GPASET.bit.GPIO5 = 1; // uncomment if --> Set High initially
	GpioCtrlRegs.GPAPUD.bit.GPIO5 = 0; //disable internal pull-up resistor
    //GpioIntRegs.GPIOXINT1SEL.bit.GPIOSEL = 5;
    //XIntruptRegs.XINT1CR.bit.POLARITY = 1;
    //XIntruptRegs.XINT1CR.bit.ENABLE = 1;
//---------------------------------------------------------------
//  GPIO-06 - PIN FUNCTION = --Spare--
	GpioCtrlRegs.GPAMUX1.bit.GPIO6 = 0; // 0=GPIO,  1=EPWM4A,  2=SYNCI,  3=SYNCO
	GpioCtrlRegs.GPADIR.bit.GPIO6 = 0; // 1=OUTput,  0=INput
	GpioDataRegs.GPACLEAR.bit.GPIO6 = 1; // uncomment if --> Set Low initially
//	GpioDataRegs.GPASET.bit.GPIO6 = 1; // uncomment if --> Set High initially
	GpioCtrlRegs.GPAPUD.bit.GPIO6 = 0; //disable internal pull-up resistor
    /*GpioIntRegs.GPIOXINT2SEL.bit.GPIOSEL = 6;
    XIntruptRegs.XINT2CR.bit.POLARITY = 0;
    XIntruptRegs.XINT2CR.bit.ENABLE = 1;*/
//---------------------------------------------------------------
//  GPIO-07 - PIN FUNCTION = --Spare--
	GpioCtrlRegs.GPAMUX1.bit.GPIO7 = 0; // 0=GPIO,  1=EPWM4B,  2=SCIRX-A,  3=Resv
	GpioCtrlRegs.GPADIR.bit.GPIO7 = 0; // 1=OUTput,  0=INput
	GpioDataRegs.GPACLEAR.bit.GPIO7 = 1; // uncomment if --> Set Low initially
//	GpioDataRegs.GPASET.bit.GPIO7 = 1; // uncomment if --> Set High initially
	GpioCtrlRegs.GPAPUD.bit.GPIO7 = 0; //disable internal pull-up resistor
	//GpioIntRegs.GPIOXINT1SEL.bit.GPIOSEL = 7;
    //XIntruptRegs.XINT1CR.bit.POLARITY = 0;
    //XIntruptRegs.XINT1CR.bit.ENABLE = 1;
//---------------------------------------------------------------
//  GPIO-08 - GPIO-11 Do Not Exist
//---------------------------------------------------------------
//  GPIO-12 - PIN FUNCTION = Normally Open pushbutton S3 on LaunchPad (pulled-down) --Spare--
	GpioCtrlRegs.GPAMUX1.bit.GPIO12 = 0; // 0=GPIO,  1=TZ1,  2=SCITX-A,  3=Resv
	GpioCtrlRegs.GPADIR.bit.GPIO12 = 1; // 1=OUTput,  0=INput
//	GpioDataRegs.GPACLEAR.bit.GPIO12 = 1;	// uncomment if --> Set Low initially
//	GpioDataRegs.GPASET.bit.GPIO12 = 1; // uncomment if --> Set High initially
	//GpioCtrlRegs.GPAPUD.bit.GPIO12 = 1; //Disable pull-up for GPIO12 (SCITXDA)
	//GpioIntRegs.GPIOXINT1SEL.bit.GPIOSEL = 12;
//---------------------------------------------------------------
//  GPIO-13 - GPIO-15 = Do Not Exist
//---------------------------------------------------------------
//---------------------------------------------------------------

//  GPIO-16 - PIN FUNCTION = Normally Open pushbutton PIN7 row 2 on keypad (pulled-down)--Spare--
	GpioCtrlRegs.GPAMUX2.bit.GPIO16 = 0; // 0=GPIO,  1=SPISIMO-A,  2=Resv,  3=TZ2
	GpioCtrlRegs.GPADIR.bit.GPIO16 = 0; // 1=OUTput,  0=INput 
//	GpioDataRegs.GPACLEAR.bit.GPIO16 = 1;	// uncomment if --> Set Low initially
//	GpioDataRegs.GPASET.bit.GPIO16 = 1; // uncomment if --> Set High initially
//	GpioCtrlRegs.GPAPUD.bit.GPIO16 = 1; //disable internal pull-up resistor
    /*GpioIntRegs.GPIOXINT1SEL.bit.GPIOSEL = 16;
    XIntruptRegs.XINT1CR.bit.POLARITY = 1;
    XIntruptRegs.XINT1CR.bit.ENABLE = 1;*/
//---------------------------------------------------------------
//  GPIO-17 - PIN FUNCTION = Normally Open pushbutton PIN8 row 1 on keypad (pulled-down) --Spare--
	GpioCtrlRegs.GPAMUX2.bit.GPIO17 = 0; // 0=GPIO,  1=SPISOMI-A,  2=Resv,  3=TZ3
	GpioCtrlRegs.GPADIR.bit.GPIO17 = 0; // 1=OUTput,  0=INput 
//	GpioDataRegs.GPACLEAR.bit.GPIO17 = 1;	// uncomment if --> Set Low initially
//	GpioDataRegs.GPASET.bit.GPIO17 = 1; // uncomment if --> Set High initially
//	GpioCtrlRegs.GPAPUD.bit.GPIO17 = 1; //disable internal pull-up resistor
//	GpioIntRegs.GPIOXINT1SEL.bit.GPIOSEL = 17;
	//XIntruptRegs.XINT1CR.bit.POLARITY = 1;
	//XIntruptRegs.XINT1CR.bit.ENABLE = 1;
//---------------------------------------------------------------
//  GPIO-18 - PIN FUNCTION = --Spare--
	GpioCtrlRegs.GPAMUX2.bit.GPIO18 = 2; // 0=GPIO,  1=SPICLK-A,  2=SCITX-A,  3=XCLKOUT
	GpioCtrlRegs.GPADIR.bit.GPIO18 = 0; // 1=OUTput,  0=INput
//	GpioDataRegs.GPACLEAR.bit.GPIO18 = 1;	// uncomment if --> Set Low initially
//	GpioDataRegs.GPASET.bit.GPIO18 = 1; // uncomment if --> Set High initially
	GpioCtrlRegs.GPAPUD.bit.GPIO12 = 1; //Disable pull-up for GPIO18 (SCITXDA)
//---------------------------------------------------------------
//  GPIO-19 - PIN FUNCTION = --Spare--
	GpioCtrlRegs.GPAMUX2.bit.GPIO19 = 0; // 0=GPIO,  1=SPISTE-A,  2=SCIRX-A,  3=ECAP1
	GpioCtrlRegs.GPADIR.bit.GPIO19 = 0; // 1=OUTput,  0=INput
	GpioDataRegs.GPACLEAR.bit.GPIO19 = 1;	// uncomment if --> Set Low initially
//	GpioDataRegs.GPASET.bit.GPIO19 = 1; // uncomment if --> Set High initially

/*	GpioCtrlRegs.GPAPUD.bit.GPIO19 = 1; //disable internal pull-up resistor
	GpioIntRegs.GPIOXINT1SEL.bit.GPIOSEL = 19;
	XIntruptRegs.XINT1CR.bit.POLARITY = 1;
	XIntruptRegs.XINT1CR.bit.ENABLE = 1;*/
//---------------------------------------------------------------
//  GPIO-20 - GPIO-27 = Do Not Exist
//---------------------------------------------------------------
//  GPIO-28 - PIN FUNCTION = --Spare-- (can connect to SCIRX on LaunchPad)
	GpioCtrlRegs.GPAMUX2.bit.GPIO28 = 1; // 0=GPIO,  1=SCIRX-A,  2=I2C-SDA,  3=TZ2
	GpioCtrlRegs.GPADIR.bit.GPIO28 = 0; // 1=OUTput,  0=INput
//	GpioDataRegs.GPACLEAR.bit.GPIO28 = 1;	// uncomment if --> Set Low initially
//	GpioDataRegs.GPASET.bit.GPIO28 = 1; // uncomment if --> Set High initially
	GpioCtrlRegs.GPAPUD.bit.GPIO28 = 0;    // Enable pull-up for GPIO28 (SCIRXDA)
	GpioCtrlRegs.GPAQSEL2.bit.GPIO28 = 3;  // Asynch input GPIO28 (SCIRXDA)
//---------------------------------------------------------------
//  GPIO-29 - PIN FUNCTION = --Spare-- (can connect to SCITX on LaunchPad)
	GpioCtrlRegs.GPAMUX2.bit.GPIO29 = 1; // 0=GPIO,  1=SCITXD-A,  2=I2C-SCL,  3=TZ3
	GpioCtrlRegs.GPADIR.bit.GPIO29 = 1; // 1=OUTput,  0=INput
//	GpioDataRegs.GPACLEAR.bit.GPIO29 = 1;	// uncomment if --> Set Low initially
//	GpioDataRegs.GPASET.bit.GPIO29 = 1; // uncomment if --> Set High initially
	GpioCtrlRegs.GPAPUD.bit.GPIO29 = 1;       // Disable pull-up for GPIO29 (SCITXDA)
//---------------------------------------------------------------
//  GPIO-30 - GPIO-31 = Do Not Exist
//---------------------------------------------------------------
//--------------------------------------------------------------

//  GPIO-32 - PIN FUNCTION = --Spare--
	GpioCtrlRegs.GPBMUX1.bit.GPIO32 = 0; // 0=GPIO,  1=I2C-SDA,  2=SYNCI,  3=ADCSOCA
	GpioCtrlRegs.GPBDIR.bit.GPIO32 = 0; // 1=OUTput,  0=INput 
//	GpioDataRegs.GPBCLEAR.bit.GPIO32 = 1;	// uncomment if --> Set Low initially
//	GpioDataRegs.GPBSET.bit.GPIO32 = 1; // uncomment if --> Set High initially
//---------------------------------------------------------------
//  GPIO-33 - PIN FUNCTION = --Spare--
	GpioCtrlRegs.GPBMUX1.bit.GPIO33 = 0; // 0=GPIO,  1=I2C-SCL,  2=SYNCO,  3=ADCSOCB
	GpioCtrlRegs.GPBDIR.bit.GPIO33 = 0; // 1=OUTput,  0=INput 
//	GpioDataRegs.GPBCLEAR.bit.GPIO33 = 1;	// uncomment if --> Set Low initially
//	GpioDataRegs.GPBSET.bit.GPIO33 = 1; // uncomment if --> Set High initially
//---------------------------------------------------------------
//  GPIO-34 - PIN FUNCTION = switch S1.1 on LaunchPad
	GpioCtrlRegs.GPBMUX1.bit.GPIO34 = 0; // 0=GPIO,  1=COMP2OUT,  2=EMU1,  3=Resv
	GpioCtrlRegs.GPBDIR.bit.GPIO34 = 0; // 1=OUTput,  0=INput 
//	GpioDataRegs.GPBCLEAR.bit.GPIO34 = 1; // uncomment if --> Set Low initially
//	GpioDataRegs.GPBSET.bit.GPIO34 = 1; // uncomment if --> Set High initially
//---------------------------------------------------------------
//  GPIO-35 - GPIO-38 = Used for JTAG Port
//---------------------------------------------------------------
//---------------------------------------------------------------

/*
	//---------------------------------------------------------------
	// INITIALIZE A-D
	//---------------------------------------------------------------
	//input channel = junction temperature sensor, SOC0, software triggering

	    //simultaneously power up ADC's analog circuitry, bandgap, and reference buffer:
	    AdcRegs.ADCCTL1.all = 0x00e0;
	    //bit 7     ADCPWDN (ADC power down): 0=powered down, 1=powered up
	    //bit 6     ADCBGPWD (ADC bandgap power down): 0=powered down, 1=powered up
	    //bit 5     ADCREFPWD (ADC reference power down): 0=powered down, 1=powered up

	    //generate INT pulse on end of conversion:
	    AdcRegs.ADCCTL1.bit.INTPULSEPOS = 1;

	    //enable ADC:
	    AdcRegs.ADCCTL1.bit.ADCENABLE = 1;

	    //wait 1 ms after power-up before using the ADC:
	    DelayUs(1000);

	    //configure to sample on-chip temperature sensor:
	    AdcRegs.ADCCTL1.bit.TEMPCONV = 1; //connect A5 to temp sensor
	    AdcRegs.ADCSOC0CTL.bit.CHSEL = 5; //set SOC0 to sample A5
	    AdcRegs.ADCSOC0CTL.bit.ACQPS = 0x6; //set SOC0 window to 7 ADCCLKs
	    AdcRegs.INTSEL1N2.bit.INT1SEL = 0; //connect interrupt ADCINT1 to EOC0
	    AdcRegs.INTSEL1N2.bit.INT1E = 1; //enable interrupt ADCINT1
*/

	EDIS;   // restore protection of registers
} // end DeviceInit()
//---------------------------------------------------------------
//INITIALIZE SCIoi
//---------------------------------------------------------------
void sci_init(void)
{
    EALLOW; // temporarily unprotect registers
    SciaRegs.SCICTL1.all =0x0003;  // enable TX, RX, internal SCICLK,
                                   // Disable RX ERR, SLEEP, TXWAKE
    SciaRegs.SCICCR.bit.SCICHAR = 8; // 8 bits data
    SciaRegs.SCICCR.bit.LOOPBKENA = 0; // disable Loopback
    SciaRegs.SCICCR.bit.PARITYENA = 0; // disable Parity
    SciaRegs.SCICCR.bit.STOPBITS = 0; // 1 stop bit
    SciaRegs.SCILBAUD = 195; // Baud Rate = LSPCLK/((BRR + 1)*8) = 9600

    SciaRegs.SCICTL2.bit.TXINTENA =1;
    SciaRegs.SCICTL2.bit.RXBKINTENA =1;
    SciaRegs.SCIHBAUD = 0x0000;
    SciaRegs.SCICCR.bit.LOOPBKENA =1; // Enable loop back
    SciaRegs.SCIFFTX.all=0xC022;
    SciaRegs.SCIFFRX.all=0x0022;
    SciaRegs.SCIFFCT.all=0x00;

    SciaRegs.SCICTL1.all =0x0023;     // Relinquish SCI from Reset
    SciaRegs.SCIFFTX.bit.TXFIFOXRESET=1;
    SciaRegs.SCIFFRX.bit.RXFIFORESET=1;

    EDIS;   // restore protection of registers
}





//===============================================================
// End of file
//===============================================================
