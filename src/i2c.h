/***************************************************************************//**
 * @file
 * @brief I2C logic.
 * @resources https://siliconlabs.github.io/Gecko_SDK_Doc/efr32bg13/html/em__core_8h.html
 *
 * Date:        09-09-2021
 * Author:      Abijith Ananda Krishnan
 * Description: This code was created by me to use the defined functions to schedule
 * the temperature read and write operation
 *
 ******************************************************************************/

#include "gpio.h"
#include "log.h"
#include "em_i2c.h"
#include "sl_i2cspm.h"
#include "timers.h"
#include "scheduler.h"
#include "ble.h"

void myI2CINIT();
void takeTemperatureReading();
void readTemperatureReading();
void convertReadTempToC(void);
