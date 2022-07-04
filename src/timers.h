/***************************************************************************//**
 * @file
 * @brief Timer logic.
 * @resources https://siliconlabs.github.io/Gecko_SDK_Doc/efr32bg1/html/em__timer_8h.html
 *
 * Date:        11-14-2021
 * Author:      Abijith Ananda Krishnan
 * Description: This code was created by me to initialise the timer dependent
 *              variables
 *
 ******************************************************************************/

#ifndef __myTimers
#define __myTimers

#include "em_letimer.h"
#include "app.h"
#include "stdlib.h"
#include "sl_power_manager.h"

#define LETIMER_PERIOD_MS   5000  //previously 2250 for A2
//Can be 1 minute duration too, kept 5 seconds for current scenario

#if LOWEST_ENERGY_MODE != 3
  #define ACTUAL_CLK_FREQ     32768 //change to 1000 when EM3, else 32768
  #define PRESCALAR_VALUE        4
#else
  #define ACTUAL_CLK_FREQ     1000
  #define PRESCALAR_VALUE        1
#endif

#define comp0Value          (LETIMER_PERIOD_MS*(ACTUAL_CLK_FREQ/PRESCALAR_VALUE))/1000 //40960 ticks

void initLETIMER0();
//Interrupt based better than polling
void timerWaitUs_irq(uint32_t us_wait);
#endif
