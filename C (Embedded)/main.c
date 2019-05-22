//*****************************************************************************
//
// Copyright (C) 2014 Texas Instruments Incorporated - http://www.ti.com/
//
//
//  Redistribution and use in source and binary forms, with or without
//  modification, are permitted provided that the following conditions
//  are met:
//
//    Redistributions of source code must retain the above copyright
//    notice, this list of conditions and the following disclaimer.
//
//    Redistributions in binary form must reproduce the above copyright
//    notice, this list of conditions and the following disclaimer in the
//    documentation and/or other materials provided with the
//    distribution.
//
//    Neither the name of Texas Instruments Incorporated nor the names of
//    its contributors may be used to endorse or promote products derived
//    from this software without specific prior written permission.
//
//  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
//  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
//  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
//  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
//  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
//  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
//  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
//  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
//  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
//  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
//  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//
//*****************************************************************************

//*****************************************************************************
//
// Application Name     - SPI Demo
// Application Overview - The demo application focuses on showing the required
//                        initialization sequence to enable the CC3200 SPI
//                        module in full duplex 4-wire master and slave mode(s).
// Application Details  -
// http://processors.wiki.ti.com/index.php/CC32xx_SPI_Demo
// or
// docs\examples\CC32xx_SPI_Demo.pdf
//
//*****************************************************************************


//*****************************************************************************
//
//! \addtogroup SPI_Demo
//! @{
//
//*****************************************************************************

// Standard includes
#include <string.h>
#include <stdio.h>
// Driverlib includes
#include "hw_types.h"
#include "hw_uart.h"
#include "hw_ints.h"
#include "hw_memmap.h"
#include "hw_common_reg.h"
#include "hw_ints.h"
#include "spi.h"
#include "rom.h"
#include "rom_map.h"
//#include "rom_map.c"
#include "utils.h"
#include "prcm.h"
#include "uart.h"
#include "interrupt.h"
#include "timer.h"
#include "gpio.h"
#include "udma.h"
#include "udma_if.h"
#include "timer_if.h"
#include "timer_if.c"

#include "uart_if.h"
#include "gpio_if.h"
#include "i2c_if.h"
// Common interface includes
#include "uart_if.h"
#include "pin_mux_config.h"

//adafruit files
#include "Adafruit_GFX.h"
#include "Adafruit_SSD1351.h"
#include "test.h"
#include "math.h"
#define APPLICATION_VERSION     "1.1.1"
//*****************************************************************************
//
// Application Master/Slave mode selector macro
//
// MASTER_MODE = 1 : Application in master mode
// MASTER_MODE = 0 : Application in slave mode
//
//*****************************************************************************
#define MASTER_MODE      1//set as master

#define SPI_IF_BIT_RATE  100000
#define TR_BUFF_SIZE     100


#define IR_PIN 0x40
#define IR_BASE GPIOA0_BASE
//*****************************************************************************
//                 GLOBAL VARIABLES -- Start
//*****************************************************************************

volatile char messageOutBuffer[52];
volatile char messageInBuffer[52];
volatile int messageInBufferIndex=0;
volatile int messageOutBufferIndex;
volatile char currentOutChar;
volatile int letterOffset;
volatile int timeOfLastButtonPress;
volatile int timerCounter;
volatile int last;
volatile int current;
volatile int interruptCounter;
volatile int timeWhenLastButtonPressed = 0;
volatile static tBoolean bRxDone;
volatile int samples[820];  // buffer to store samples
int finalSamples[410];
volatile int new_dig;
unsigned long firstByte,secondByte;
volatile int sampleIndex;
int x_cursorTx = 0;
int y_cursorTx = 0;
int x_cursorRx = 0;
int y_cursorRx = 70;
int sampleFlag = 1;
char tmp;
int power_all[8];       // array to store calculated power of 8 frequencies
int coeff[8];           // array to store the calculated coefficients
unsigned char g_ucRxBuff[2];
int characterConfirmed = 1;
char lastButton;
#if defined(ccs)
extern void (* const g_pfnVectors[])(void);
#endif
#if defined(ewarm)
extern uVectorEntry __vector_table;
#endif
//*****************************************************************************
//                 GLOBAL VARIABLES -- End
//*****************************************************************************
//*****************************************************************************
//
//! Board Initialization & Configuration
//!
//! \param  None
//!
//! \return None
//
//*****************************************************************************
static void
BoardInit(void)
{
/* In case of TI-RTOS vector table is initialize by OS itself */
#ifndef USE_TIRTOS
  //
  // Set vector table base
  //
#if defined(ccs)
    MAP_IntVTableBaseSet((unsigned long)&g_pfnVectors[0]);
#endif
#if defined(ewarm)
    MAP_IntVTableBaseSet((unsigned long)&__vector_table);
#endif
#endif
    //
    // Enable Processor
    //
    MAP_IntMasterEnable();
    MAP_IntEnable(FAULT_SYSTICK);

    PRCMCC3200MCUInit();
}


long int
goertzel (int sample[], long int coeff, int N)
//---------------------------------------------------------------//
{
//initialize variables to be used in the function
  int Q, Q_prev, Q_prev2, i;
  long prod1, prod2, prod3, power;

  Q_prev = 0;           //set delay element1 Q_prev as zero
  Q_prev2 = 0;          //set delay element2 Q_prev2 as zero
  power = 0;            //set power as zero

  for (i = 0; i < N; i++)   // loop N times and calculate Q, Q_prev, Q_prev2 at each iteration
    {
      Q = (sample[i]) + ((coeff * Q_prev) >> 14) - (Q_prev2);   // >>14 used as the coeff was used in Q15 format
      Q_prev2 = Q_prev;     // shuffle delay elements
      Q_prev = Q;
    }

  //calculate the three products used to calculate power
  prod1 = ((long) Q_prev * Q_prev);
  prod2 = ((long) Q_prev2 * Q_prev2);
  prod3 = ((long) Q_prev * coeff) >> 14;
  prod3 = (prod3 * Q_prev2);

  power = ((prod1 + prod2 - prod3)) >> 8;   //calculate power using the three products and scale the result down

  return power;
}

//-------Post-test function---------------------------------------//
int
post_test (void)
//---------------------------------------------------------------//
{
//initialize variables to be used in the function
  int i, row, col, max_power;

  char row_col[4][4] =      // array with the order of the digits in the DTMF system
  {
    {'1', '2', '3', 'A'},
    {'4', '5', '6', 'B'},
    {'7', '8', '9', 'C'},
    {'*', '0', '#', 'D'}
  };

// find the maximum power in the row frequencies and the row number

  max_power = 0;                //initialize max_power=0

  for (i = 0; i < 4; i++)       //loop 4 times from 0>3 (the indecies of the rows)
    {
      if (power_all[i] > max_power) //if power of the current row frequency > max_power
    {
      max_power = power_all[i]; //set max_power as the current row frequency
      row = i;      //update row number
    }
    }


// find the maximum power in the column frequencies and the column number

  max_power = 0;        //initialize max_power=0

  for (i = 4; i < 8; i++)   //loop 4 times from 4>7 (the indecies of the columns)
    {
      if (power_all[i] > max_power) //if power of the current column frequency > max_power
    {
      max_power = power_all[i]; //set max_power as the current column frequency
      col = i;      //update column number
    }
    }


  if (power_all[col] < 45000 /*&& power_all[row] == 0*/)   //if the maximum powers equal zero > this means no signal or inter-digit pause
    new_dig = 1;        //set new_dig to 1 to display the next decoded digit
  //if(power_all[col]>25000)
    //  Report("Too high\n\r");
  //Report("%d   %d\n\r",power_all[col],power_all[row]);

  if (/*(*/power_all[col] > 45000 /*&& power_all[row] > 6000)*/ && (new_dig == 1))   // check if maximum powers of row & column exceed certain threshold AND new_dig flag is set to 1
    {
      //Write to OLED Display
      //write_lcd (1, row_col[row][col - 4]); // display the digit on the LCD
      //dis_7seg (8, row_col[row][col - 4]);  // display the digit on 7-seg
       new_dig = 0;// set new_dig to 0 to avoid displaying the same digit again.
       return row_col[row][col - 4];

    }
  return 63;
}
void displayTimerInt(void){
    Timer_IF_InterruptClear(TIMERA1_BASE);
    timerCounter++;
}
//Take adc sample at interrupt
void interrupt16Mhz(void){
    Timer_IF_InterruptClear(TIMERA0_BASE);
    GPIOPinWrite(GPIOA0_BASE, 0x40,0);//write chip select low
    MAP_SPITransfer(GSPI_BASE,0,g_ucRxBuff,2,
                SPI_CS_ENABLE|SPI_CS_DISABLE);//do spi data read
    GPIOPinWrite(GPIOA0_BASE, 0x40,0xFF);//write chip select high
    samples[sampleIndex] = g_ucRxBuff[0];//load into 2 buffer location since 16bit from spi read
    samples[sampleIndex+1] = g_ucRxBuff[1];
    sampleIndex+=2;

    if(sampleIndex >= 819)
        sampleFlag = 1;

}

void printCharTop(char character){


    if(character == 30){//delete a character
        x_cursorTx -= 6;
        fillRect(x_cursorTx,y_cursorTx, 6, 8, BLACK);

        x_cursorTx -=6;
    }
    else if(character == 31){//button pressed =1, wipe screen
        messageOutBufferIndex = 0;
        fillScreen(BLACK);
        x_cursorTx = 0;
        y_cursorTx = 0;
    }
    else
        drawChar(x_cursorTx,y_cursorTx,character,WHITE,BLACK,1);

}

void printCharBottom(char character){
    drawChar(x_cursorRx,y_cursorRx,character,WHITE,BLACK,1);

    x_cursorRx += 6;
    if(x_cursorRx >= 124){
        x_cursorRx = 0;
        y_cursorRx += 8;
    }

}
volatile unsigned char UARTDataBuffer[128];
volatile unsigned char UARTData;
volatile unsigned int UARTDataCount = 0;
unsigned long intStatus;
volatile int UARTDataFlag =0;
char UART_STATUS;
static void UARTRxIntHandler()
{
        Report("UART Interrupt\n\r");
      //MAP_TimerDisable(TIMERA0_BASE,TIMER_A);
      UART_STATUS = UARTIntStatus(UARTA1_BASE, true);

      if((UART_STATUS & UART_INT_RX) && MAP_UARTCharsAvail(UARTA1_BASE))
      {

        //clear the receive interrupt
        MAP_UARTIntClear(UARTA1_BASE, UART_INT_RX);
        //receive data here
        UARTDataBuffer[UARTDataCount] = (unsigned char)MAP_UARTCharGetNonBlocking(UARTA1_BASE);
        UARTDataCount++;
        UARTDataFlag = 1;
        //printCharBottom(UARTData);
       }
}

//*****************************************************************************
//
//! Main function for spi demo application
//!
//! \param none
//!
//! \return None.
//
//*****************************************************************************
void main()
{

    //
    // Initialize Board configurations
    //
    BoardInit();

    //
    // Muxing UART and SPI lines.
    //
    PinMuxConfig();
    //{ 697, 770, 852, 941, 1209, 1336, 1477, 1633 };
    coeff[0] = 31548;
    coeff[1] = 31281;
    coeff[2] = 30951;
    coeff[3] = 30556;
    coeff[4] = 29143;
    coeff[5] = 28360;
    coeff[6] = 27408;
    coeff[7] = 26257;
    //
    // Enable the SPI module clock
    //
    //
    // Reset SPI/
    //
    MAP_SPIReset(GSPI_BASE);
    MAP_PRCMPeripheralReset(PRCM_GSPI);
    //
    // Configure SPI interface
    // Use an SPI transfer rate of 400kbits/sec
    //
    MAP_SPIConfigSetExpClk(GSPI_BASE,MAP_PRCMPeripheralClockGet(PRCM_GSPI),
                     400000,SPI_MODE_MASTER,SPI_SUB_MODE_0,
                     (SPI_SW_CTRL_CS |
                     SPI_4PIN_MODE |
                     SPI_TURBO_OFF |
                     SPI_CS_ACTIVELOW |
                     SPI_WL_8));

    MAP_SPIEnable(GSPI_BASE);
    //
    // Enable SPI for communication
    //


    //Oled initialize
    Adafruit_Init();
    fillScreen(RED);
    //
    // Initialising the Terminal.
    //
    InitTerm();

    //
    // Clearing the Terminal.
    //
    ClearTerm();
    bRxDone = false;
    //Setup Uart

    //UDMAInit();
    MAP_UARTConfigSetExpClk(UARTA1_BASE,MAP_PRCMPeripheralClockGet(PRCM_UARTA1),
                      /*UART_BAUD_RATE*/9600, (UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE |
                       UART_CONFIG_PAR_NONE));

    MAP_UARTFIFODisable(UARTA1_BASE);
    MAP_UARTIntRegister(UARTA1_BASE, UARTRxIntHandler);
    MAP_UARTIntEnable(UARTA1_BASE, UART_INT_RX|UART_INT_RT);

    //Setup Timer for waveform
    Timer_IF_Init(PRCM_TIMERA0,TIMERA0_BASE,TIMER_CFG_PERIODIC,TIMER_A,0);
    Timer_IF_IntSetup(TIMERA0_BASE,TIMER_A,interrupt16Mhz);
    TimerLoadSet(TIMERA0_BASE,TIMER_A,MILLISECONDS_TO_TICKS(/*100*/.0625));
    //MAP_TimerEnable(TIMERA0_BASE,TIMER_A);
    //setup timer for display

    Timer_IF_Init(PRCM_TIMERA1,TIMERA1_BASE,TIMER_CFG_PERIODIC,TIMER_A,0);
    Timer_IF_IntSetup(TIMERA1_BASE,TIMER_A,displayTimerInt);
    TimerLoadSet(TIMERA1_BASE,TIMER_A,MILLISECONDS_TO_TICKS(.5));
    MAP_TimerEnable(TIMERA1_BASE,TIMER_A);

    //
    // Display the Banner
    //
    Message("\n\n\n\r");
    Message("\t\t********************************************\n\r");
    Message("\t\t        LAB 4 Microphone Receiver With ADC  \n\r");
    Message("\t\t********************************************\n\r");
    Message("\n\n\n\r");
    timerCounter = 0;
    current = 0;
    last = 0;
    interruptCounter = 0;
    messageOutBufferIndex = 0;
    letterOffset = 0;
    timeOfLastButtonPress = 0;
    messageOutBufferIndex = 0;
    //int buffer = 0;
    int buttonPressed;
    sampleIndex = 0;
    int i,j;
    fillScreen(BLACK);
    sampleFlag = 0;
    MAP_TimerEnable(TIMERA0_BASE,TIMER_A);

    while(1){
        if(UARTDataFlag==1){
            fillRect(0,64,128,64,BLACK);
            for(i =1;i<UARTDataCount;i++)
                printCharBottom(UARTDataBuffer[i]);
            UARTDataCount = 0;
            UARTDataFlag = 0;
            x_cursorRx = 0;
            UARTDataCount = 0;//may need to remove
            MAP_TimerEnable(TIMERA0_BASE,TIMER_A);
        }
        if(sampleFlag == 1){//sample flag full
              MAP_TimerDisable(TIMERA0_BASE,TIMER_A);
              sampleIndex = 0;
              sampleFlag = 0;
              j =0;
              for(i = 0; i <= 409;i++){
                  finalSamples[i] = (((samples[j] << 8)|samples[j+1]) & 0x1FF8)>>3;
                  //Report("%d\n\r",finalSamples[i]);
                  j+=2;
              }
              for (i = 0; i < 8; i++){
                    power_all[i] = goertzel (finalSamples, coeff[i], 410);   // call goertzel to calculate the power at each frequency and store it in the power_all array
                    buttonPressed = post_test ();        // call post test function to validate the data and display the pressed digit if applicable
                    //printCharTop((char)buttonPressed);
                    if(buttonPressed != 63){//Actual Button pressed
                       Report("%c\r\n",buttonPressed);
                       //convert to a button

                       timeWhenLastButtonPressed = timerCounter;
                       if(timerCounter-timeOfLastButtonPress > 2400){//Confirm a Letter
                                   letterOffset = 0;
                                   //x_cursorTx += 6;
                                   x_cursorTx += 6;
                                       if(x_cursorTx >= 124){
                                           x_cursorTx =0;
                                           y_cursorTx += 8;
                                       }
                                   if(currentOutChar != 30){
                                       messageOutBuffer[messageOutBufferIndex] = currentOutChar;
                                       messageOutBufferIndex++;
                                   }
                                   characterConfirmed = 1;
                               }//end of confirm a letter
                       timeOfLastButtonPress = timerCounter;
                       if(characterConfirmed == 1 || buttonPressed == lastButton){
                       if(buttonPressed == 50){//ABC
                           if(letterOffset ==3)
                                 letterOffset = 0;
                           //drawChar(x_cursorTx,y_cursorTx,97+letterOffset,WHITE,BLACK,1);
                           printCharTop(97+letterOffset);
                           currentOutChar = 97+letterOffset;
                           lastButton = '2';

                       }
                       else if(buttonPressed == '3'){//DEF
                           if(letterOffset ==3)
                                 letterOffset = 0;
                           //drawChar(x_cursorTx,y_cursorTx,100+letterOffset,WHITE,BLACK,1);
                           printCharTop(100+letterOffset);
                           currentOutChar = 100+letterOffset;
                           lastButton = '3';
                       }
                       else if(buttonPressed == '4'){//GHI
                           if(letterOffset ==3)
                                 letterOffset = 0;
                           //drawChar(x_cursorTx,y_cursorTx,103+letterOffset,WHITE,BLACK,1);
                           printCharTop(103+letterOffset);
                           currentOutChar = 103+letterOffset;
                           lastButton = '4';
                       }
                       else if(buttonPressed == '5'){//JKL
                           if(letterOffset ==3)
                                 letterOffset = 0;
                           //drawChar(x_cursorTx,y_cursorTx,106+letterOffset,WHITE,BLACK,1);
                           printCharTop(106+letterOffset);
                           currentOutChar = 106+letterOffset;
                           lastButton = '5';
                       }
                       else if(buttonPressed == '6'){//MNO
                           if(letterOffset ==3)
                                letterOffset = 0;
                           //drawChar(x_cursorTx,y_cursorTx,109+letterOffset,WHITE,BLACK,1);
                           printCharTop(109+letterOffset);
                           currentOutChar = 109+letterOffset;
                           lastButton = '6';
                       }
                       else if(buttonPressed == '7'){//PQRS
                           if(letterOffset ==4)
                                letterOffset = 0;
                           //drawChar(x_cursorTx,y_cursorTx,112+letterOffset,WHITE,BLACK,1);
                           printCharTop(112+letterOffset);
                           currentOutChar = 112+letterOffset;
                           lastButton = '7';
                       }
                       else if(buttonPressed == '8'){//TUV
                           if(letterOffset ==3)
                                letterOffset = 0;
                           //drawChar(x_cursorTx,y_cursorTx,116+letterOffset,WHITE,BLACK,1);
                           printCharTop(116+letterOffset);
                           currentOutChar = 116+letterOffset;
                           lastButton = '8';
                       }
                       else if(buttonPressed == '9'){//WXYZ
                           if(letterOffset ==4)
                               letterOffset = 0;
                           //drawChar(x_cursorTx,y_cursorTx,119+letterOffset,WHITE,BLACK,1);
                           printCharTop(119+letterOffset);
                           currentOutChar = 119+letterOffset;
                           lastButton = '9';
                       }
                       else if(buttonPressed == '0'){//SPACE
                           //drawChar(x_cursorTx,y_cursorTx,94,WHITE,BLACK,1);
                           printCharTop(32);
                           currentOutChar = 32;
                           lastButton = '0';
                       }
                       else if(buttonPressed == '*'){//MUTE(delete)
                           printCharTop(30);
                           currentOutChar = 30;
                           //subtract 1 from current buffer location
                           messageOutBufferIndex-=1;
                           lastButton = '*';
                       }
                       else if(buttonPressed =='#'){//Send
                           int i;
                           lastButton = '#';
                           for (i = 0; i < messageOutBufferIndex; i++) {
                              Report("%c\n\r",messageOutBuffer[i]);
                          }
                           MAP_TimerDisable(TIMERA0_BASE,TIMER_A);
                           for (i = 0; i < messageOutBufferIndex; i++) {
                               MAP_UARTCharPut(UARTA1_BASE,messageOutBuffer[i]);
                           }
                           //Report("\n\r");
                           //clear the top half of the oled display
                           fillRect(0, 0, 127, 63, BLACK);
                           x_cursorTx = 0;
                           y_cursorTx = 0;
                           messageOutBufferIndex = 0;


                       }
                       else if(buttonPressed ==1){//clear screen
                           printCharTop(31);
                       }
                       letterOffset++;
                       }
                    }//end of actual button pressed
              }
              if(lastButton != '#'){
              MAP_TimerEnable(TIMERA0_BASE,TIMER_A);
              lastButton = 'c';
              }
        }
    }
}
