/*
   gpio.h
  
    Created on: Dec 12, 2018
        Author: Dan Walkes

    Updated by Dave Sluiter Sept 7, 2020. moved #defines from .c to .h file.
    Updated by Dave Sluiter Dec 31, 2020. Minor edits with #defines.

    @resources https://www.silabs.com/documents/public/user-guides/ug279-brd4104a-user-guide.pdf - Page 16
    In the above resources, I understood that that it was pin 4 and 5 under Port F
    but was not sure about how to code in the specific port

    @resources https://siliconlabs.force.com/community/s/article/using-bluetooth-to-control-leds-on-a-wstk-development-board-5?language=en_US
    With the above resource, I figured out how to code in the port.
 */

#ifndef SRC_GPIO_H_
#define SRC_GPIO_H_
#include <stdbool.h>
#include "em_gpio.h"
#include <string.h>
#include "ble_device_type.h"


// Student Edit: Define these, 0's are placeholder values.
// See the radio board user guide at https://www.silabs.com/documents/login/user-guides/ug279-brd4104a-user-guide.pdf
// and GPIO documentation at https://siliconlabs.github.io/Gecko_SDK_Doc/efm32g/html/group__GPIO.html
// to determine the correct values for these.



#define	LED0_port  gpioPortF // change to correct ports and pins
#define LED0_pin   4
#define LED1_port  gpioPortF
#define LED1_pin   5
#define SENSOR_ENABLE_PORT gpioPortD// to set the port for sensor enable and also pin
#define SENSOR_ENABLE_PIN 15
#define DISP_EXTCOMIN_PORT gpioPortD //
#define DISP_EXTCOMIN_PIN 13
#define PB0_port gpioPortF
#define PB0_pin 6
#define PB1_port gpioPortF
#define PB1_pin 7
//#define SENSOR_I2C_SCL_PORT gpioPortC
//#define SENSOR_I2C_SCL_PIN 10
//#define SENSOR_I2C_SDA_PORT gpioPortC
//#define SENSOR_I2C_SDA_PIN 11

//Abijith's edit:
//Add GPIO port and pin for Smoke detector
#define SMOKE_DETECTOR_PORT gpioPortC
#define SMOKE_DETECTOR_PIN  9
//Expansion header pin 10




// Function prototypes
void gpioInit();
void gpioLed0SetOn();
void gpioLed0SetOff();
void gpioLed1SetOn();
void gpioLed1SetOff();
void si7021TurnOn();
void si7021TurnOff();
void gpioSetDisplayExtcomin(bool value);
void configureButtonPB0();
void setPB0AsInput();
void configureButtonPB1();
void setPB1AsInput();

//Abijith's edit:
void smokeDetectorTurnOn(void);
void smokeDetectorTurnOff(void);
#endif /* SRC_GPIO_H_ */
