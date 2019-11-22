/* 
 *  28x specific Idle example.
 *  
 *  This example:
 * 
 *  1) prints "Hello world" in main()
 *  
 *  2) prints the current value of a counter from
 *     within an Idle function each time an
 *     a timer interrupt goes off.
 * 
 *  All output is routed to a log buffer which can be viewed
 *  using the RTA "Raw Logs" viewer. After loading and running
 *  the application, launch the Tools->RTA->Raw Logs tool to
 *  view the logs.
 */
#define xdc__strict //gets rid of #303-D typedef warning re Uint16, Uint32
#define getTempSlope (*(int (*)(void))0x3d7e80)
#define getTempOffset (*(int (*)(void))0x3d7e83)


#include <xdc/std.h>
//#include <xdc/runtime/Log.h>
#include <ti/sysbios/BIOS.h>
#include "Peripheral_Headers/F2802x_Device.h"
#include "Peripheral_Headers/F2802x_SysCtrl.h"
#include <ti/sysbios/knl/Swi.h>

int16 Col4, Col3, Col2, Col1, Row4, Row3, Row2, Row1;
#define Col4  GpioDataRegs.GPADAT.bit.GPIO0
#define Col3  GpioDataRegs.GPADAT.bit.GPIO1
#define Col2  GpioDataRegs.GPADAT.bit.GPIO2
#define Col1  GpioDataRegs.GPADAT.bit.GPIO3
#define Row4  GpioDataRegs.GPADAT.bit.GPIO4
#define Row3  GpioDataRegs.GPADAT.bit.GPIO5
#define Row2  GpioDataRegs.GPADAT.bit.GPIO6
#define Row1  GpioDataRegs.GPADAT.bit.GPIO7
#define Flag  GpioDataRegs.GPADAT.bit.GPIO19
#define HIGH 1
#define LOW 0

//function prototypes:
extern void DeviceInit(void);
//void update(unsigned char);
//void rowCheck(void);

unsigned char key = 0;

/* Swi handle defined in swi.cfg */
extern const Swi_Handle swiGetKey;

/* Flag used by idle function to check if interrupt occurred */
volatile Bool isrFlag = FALSE;

/* Counter incremented by timer interrupt */
volatile UInt tickCount = 0;

//declare global variables:
int16 temp_slope;
int16 temp_offset;
int16 temp_reading;
int32 temp_celsius;
int16 pbcount = 0; //counts pushbutton pushes
int16 flag = 0, flagcheck = 0;
int16 row1Check, row2Check, row3Check, row4Check;
int16 col1Check, col2Check, col3Check, col4Check;
int16 state = 1;

/*
 *  ======== main ========
 */
Int main()
{
    /*
     * Print "Hello world" to a log buffer. 
     */
    //Log_info0("Hello world\n");

    /* 
     * Start BIOS
     * Perform a few final initializations and then
     * fall into a loop that continually calls the
     * installed Idle functions.
     */
    //Gpio_select();
    DeviceInit(); //initialize peripherals
    //temp_slope = getTempSlope();
    //temp_offset = getTempOffset();

    BIOS_start();    /* does not return */
    return(0);
}

/*void Gpio_select(void)
{
    EALLOW;
    GpioCtrlRegs.GPAMUX1.all = 0x00000000;  // All GPIO
    GpioCtrlRegs.GPAMUX2.all = 0x00000000;  // All GPIO

    GpioCtrlRegs.GPADIR.all = 0x000000FF;   // outputs
    GpioCtrlRegs.GPBDIR.all = 0x0000000F;   // All outputs
    EDIS;

    GpioDataRegs.GPADAT.all = 0x00000000;
    GpioDataRegs.GPBDAT.all = 0x00000000;
}*/
/*
 *  ======== myTickFxn ========
 *  Timer Tick function that increments a counter, and sets the isrFlag.
 */
Void myTickFxn(UArg arg) 
{
    tickCount += 1;    /* increment the counter */
    //SysctrlRegs.LPMCR0.bit.LPM = 1;
    if (tickCount >= 4294967000)
    {
        tickCount = 0;
    }
    Swi_post(swiGetKey);
    isrFlag = TRUE;    /* tell background that new data is available */
}

/*void myScan(UArg arg)
{
    isrFlag = TRUE;
}*/
/*
 *  ======== myIdleFxn ========
 *  Background idle function that is called repeatedly 
 *  from within BIOS_start() thread.
 */
Void myIdleFxn(Void) 
{
    if (isrFlag == TRUE) {
        isrFlag = FALSE;
        //GpioDataRegs.GPATOGGLE.bit.GPIO0 = 1;
        //read ADC value from temperature sensor:
        /*AdcRegs.ADCSOCFRC1.all = 0x1; //start conversion via software
        while(AdcRegs.ADCINTFLG.bit.ADCINT1 == 0)
            {
            ; //wait for interrupt flag to be set
            }
        AdcRegs.ADCINTFLGCLR.bit.ADCINT1 = 1; //clear interrupt flag

        temp_reading = AdcResult.ADCRESULT0; //get reading

        temp_celsius = (int32)(temp_reading - temp_offset) * (int32)temp_slope;*/

        // cycle through the 4x4 keypad columns

        /*if (state == 1)
        {
            GpioDataRegs.GPASET.bit.GPIO3 = 1; // Set GPIO3 pin
            GpioDataRegs.GPACLEAR.bit.GPIO0 = 1; //Clear GPIO0 pin
            rowCheck();
            state = 2;
        }
        else if (state == 2)
        {
            GpioDataRegs.GPASET.bit.GPIO0 = 1; // Set GPIO0 pin
            GpioDataRegs.GPACLEAR.bit.GPIO1 = 1; //Clear GPIO1 pin
            rowCheck();
            state = 3;
        }
        else if (state == 3)
        {
            GpioDataRegs.GPASET.bit.GPIO1 = 1; // Set GPIO1 pin
            GpioDataRegs.GPACLEAR.bit.GPIO2 = 1; //Clear GPIO2 pin
            rowCheck();
            state = 4;
        }
        else
        {
            GpioDataRegs.GPASET.bit.GPIO2 = 1; // Set GPIO2 pin
            GpioDataRegs.GPACLEAR.bit.GPIO3 = 1; //Clear GPIO3 pin
            rowCheck();
            state = 1;
        }*/

        /*row1Check = Row1;
        row2Check = Row2;
        row3Check = Row3;
        row4Check = Row4;
        col1Check = Col1;
        col2Check = Col2;
        col3Check = Col3;
        col4Check = Col4;*/

/*        if ((Row4 & Row3 & Row2 & Row1) == 0)
        {
            EALLOW;
            //GpioDataRegs.GPATOGGLE.bit.GPIO19 = 1;
            GpioDataRegs.GPASET.bit.GPIO19 = 1;
            EDIS;
        }
        flag = Flag;
        flagcheck = Row4 & Row3 & Row2 & Row1;*/


        /*
         * Print the current value of tickCount to a log buffer. 
         */
        //Log_info1("Tick Count = %d\n", tickCount);
    }
}


/*'
Columns 1 2 3 4
"+---+---+---+---+"
"| 1 | 2 | 3 | A | Row 1
"+---+---+---+---+
"| 4 | 5 | 6 | B | Row 2
"+---+---+---+---+
"| 7 | 8 | 9 | C | Row 3
"+---+---+---+---+
"| * | 0 | # | D | Row 4
"+---+---+---+---+" */

void myPBFxn(void)
{
    pbcount++;
    //Swi_post(swi0);
/*    if (Col1 == 0) || Col2 == 0 || Col3 == 0 || Col4 == 0)
    {

    }*/
}

void KeyGetC(void)
{

    if (state == 1)
       {
           GpioDataRegs.GPASET.bit.GPIO3 = 1; // Set GPIO3 pin
           GpioDataRegs.GPACLEAR.bit.GPIO0 = 1; //Clear GPIO0 pin
           //rowCheck();
           state = 2;
       }
       else if (state == 2)
       {
           GpioDataRegs.GPASET.bit.GPIO0 = 1; // Set GPIO0 pin
           GpioDataRegs.GPACLEAR.bit.GPIO1 = 1; //Clear GPIO1 pin
           //rowCheck();
           state = 3;
       }
       else if (state == 3)
       {
           GpioDataRegs.GPASET.bit.GPIO1 = 1; // Set GPIO1 pin
           GpioDataRegs.GPACLEAR.bit.GPIO2 = 1; //Clear GPIO2 pin
           //rowCheck();
           state = 4;
       }
       else
       {
           GpioDataRegs.GPASET.bit.GPIO2 = 1; // Set GPIO2 pin
           GpioDataRegs.GPACLEAR.bit.GPIO3 = 1; //Clear GPIO3 pin
           //rowCheck();
           state = 1;
       }
    //tickCount = 0;
    int col;
    int row;
    int findCol[] = {Col1, Col2, Col3, Col4};
    int findRow[] = {Row1, Row2, Row3, Row4};

    const char Keypad [4][4] =
    {
       {'1', '2', '3', 'A'},
       {'4', '5', '6', 'B'},
       {'7', '8', '9', 'C'},
       {'*', '0', '#', 'D'}
    };

    if ((Row4 == 1) && (Row3 == 1) && (Row2 == 1) && (Row1 == 1))
    {
        ; // do nothing
    }
    else
    {
        for (col = 0; col < 4; col++)
        {
            if (findCol[col] == 0)
            {
                for (row = 0; row < 4; row++)
               {
                   if (findRow[row] == 0)
                   {
                       key = Keypad[row][col];
                       tickCount = 0;
                   }
               }
            }
        }

    }
}

/*
void rowCheck()
{
    int row;
    int findRow[] = {Row1, Row2, Row3, Row4};
    if ((Row1 & Row2 & Row3 & Row4) == 0)
    {
        // Find which row was low
        for (row = 0; row < 4; row++)
        {
            if (findRow[row] == 0)
            {
                break;
            }
        }

        if (row == 0)
        {
            EALLOW;
            GpioIntRegs.GPIOXINT1SEL.bit.GPIOSEL = 7;
            XIntruptRegs.XINT1CR.bit.POLARITY = 0;
            XIntruptRegs.XINT1CR.bit.ENABLE = 1;
            EDIS;
        }
        else if (row == 1)
        {
            GpioIntRegs.GPIOXINT1SEL.bit.GPIOSEL = 6;
            XIntruptRegs.XINT1CR.bit.POLARITY = 0;
            XIntruptRegs.XINT1CR.bit.ENABLE = 1;
        }
        else if (row == 2)
        {
            GpioIntRegs.GPIOXINT1SEL.bit.GPIOSEL = 5;
            XIntruptRegs.XINT1CR.bit.POLARITY = 0;
            XIntruptRegs.XINT1CR.bit.ENABLE = 1;
        }
        else if (row == 3)
        {
            GpioIntRegs.GPIOXINT1SEL.bit.GPIOSEL = 4;
            XIntruptRegs.XINT1CR.bit.POLARITY = 0;
            XIntruptRegs.XINT1CR.bit.ENABLE = 1;
        }
    }
}
*/