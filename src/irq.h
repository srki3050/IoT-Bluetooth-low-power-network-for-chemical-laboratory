/***************************************************************************//**
 * @file
 * @brief Interrupt logic.
 * @resources https://siliconlabs.github.io/Gecko_SDK_Doc/efr32bg1/html/em__timer_8h.html
 *
 * Date:        09-09-2021
 * Author:      Abijith Ananda Krishnan
 * Description: This code was created by me to initialise the timer dependent
 *              variables
 *
 ******************************************************************************/

#ifndef __myIRQ
#define __myIRQ

#include "gpio.h"
#include "timers.h"
#include "scheduler.h"
#include "sl_power_manager.h"

uint32_t letimerMilliseconds();

#endif
