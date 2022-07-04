/*
  gpio.c
 
   Created on: Dec 12, 2018
       Author: Dan Walkes
   Updated by Dave Sluiter Dec 31, 2020. Minor edits with #defines.

   March 17
   Dave Sluiter: Use this file to define functions that set up or control GPIOs.

   @resources https://siliconlabs.github.io/Gecko_SDK_Doc/efr32bg1/html/group__GPIO.html
 */



#include "gpio.h"
#define INCLUDE_LOG_DEBUG 1
#include "src/log.h"




// Set GPIO drive strengths and modes of operation
void gpioInit()
{

  // Student Edit:

  //Question 1: commented line 34,37,38,39 and uncommented line 33,35
  //Question 2: commented line 33,37,38,39 and uncommented line 34,35
  //Question 4: commented line 33,37,38,39 and uncommented line 34,35
  //Question 5: commented line 33, 37 and uncommented line 34, 35, 38, 39

	//GPIO_DriveStrengthSet(LED0_port, gpioDriveStrengthStrongAlternateStrong);
	GPIO_DriveStrengthSet(LED0_port, gpioDriveStrengthWeakAlternateWeak);
	GPIO_PinModeSet(LED0_port, LED0_pin, gpioModePushPull, false);

	//GPIO_DriveStrengthSet(LED1_port, gpioDriveStrengthStrongAlternateStrong);
	GPIO_DriveStrengthSet(LED1_port, gpioDriveStrengthWeakAlternateWeak);
	GPIO_PinModeSet(LED1_port, LED1_pin, gpioModePushPull, false);

	//configuring button for interrupts

    //setPB0AsInput();
    //configureButtonPB0();
    //NVIC_ClearPendingIRQ(GPIO_EVEN_IRQn);
    //NVIC_EnableIRQ(GPIO_EVEN_IRQn);

    //setPB1AsInput();
    //configureButtonPB1();
    //NVIC_ClearPendingIRQ(GPIO_ODD_IRQn);
    //NVIC_EnableIRQ(GPIO_ODD_IRQn);

  //configuring the Smoke Sensor pin
    GPIO_PinModeSet(SMOKE_DETECTOR_PORT, SMOKE_DETECTOR_PIN, gpioModeInput, false);

} // gpioInit()


void gpioLed0SetOn()
{
	GPIO_PinOutSet(LED0_port,LED0_pin);
}


void gpioLed0SetOff()
{
	GPIO_PinOutClear(LED0_port,LED0_pin); //LED0_port = gpioPortF //LED0_pin = 4
}


void gpioLed1SetOn()
{
	GPIO_PinOutSet(LED1_port,LED1_pin);
}


void gpioLed1SetOff()
{
	GPIO_PinOutClear(LED1_port,LED1_pin); //LED1_port = gpioPortF //LED1_pin = 5
}

void si7021TurnOn(){
  GPIO_PinOutSet(SENSOR_ENABLE_PORT,SENSOR_ENABLE_PIN);
}

void si7021TurnOff(){
  GPIO_PinOutClear(SENSOR_ENABLE_PORT,SENSOR_ENABLE_PIN);
}

//Smoke Sensor turn on and off
void smokeDetectorTurnOn(){
  GPIO_PinOutSet(SMOKE_DETECTOR_PORT, SMOKE_DETECTOR_PIN);
}

void smokeDetectorTurnOff(){
  GPIO_PinOutClear(SMOKE_DETECTOR_PORT, SMOKE_DETECTOR_PIN);
}

void gpioSetDisplayExtcomin(bool value){
  value == 1? GPIO_PinOutSet(DISP_EXTCOMIN_PORT,DISP_EXTCOMIN_PIN):GPIO_PinOutClear(DISP_EXTCOMIN_PORT,DISP_EXTCOMIN_PIN);
}

void configureButtonPB0(){
  GPIO_ExtIntConfig (PB0_port, PB0_pin, PB0_pin, true, true, true);
}

void setPB0AsInput(){
  GPIO_PinModeSet(PB0_port, PB0_pin, gpioModeInput, false);
}

void configureButtonPB1(){
  GPIO_ExtIntConfig (PB1_port, PB1_pin, PB1_pin, true, true, true);
}

void setPB1AsInput(){
  GPIO_PinModeSet(PB1_port, PB1_pin, gpioModeInput, false);
}


//Abijith's edit:
//Add functions to set set GPIO pin as input




