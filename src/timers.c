/***************************************************************************//**
 * @file
 * @brief Timer logic.
 * @resources https://siliconlabs.github.io/Gecko_SDK_Doc/efr32bg1/html/em__timer_8h.html
 *
 * Date:        09-09-2021
 * Author:      Abijith Ananda Krishnan
 * Description: This code was created by me to run the timer
 *
 ******************************************************************************/

#include "timers.h"
#define INCLUDE_LOG_DEBUG 1
#include "src/log.h"

void initLETIMER0()
{
  LETIMER_Init_TypeDef init;

  init.enable = false;
  init.debugRun = true; //disable to stop debugging
  //a switch in flipflop - runs in spite of being in debugging mode
  init.comp0Top = true;
  init.bufTop = false;
  init.out0Pol = 0;
  init.out1Pol = 0;
  init.ufoa0 = letimerUFOANone;
  init.ufoa1 = letimerUFOANone;
  init.repMode = letimerRepeatFree;
  init.topValue = comp0Value; //0xBB8
  LETIMER_Init(LETIMER0,&init);
  //declaring a variable of type struct in main memory

  LETIMER_IntEnable(LETIMER0,LETIMER_IEN_UF);

  LETIMER_Enable(LETIMER0,true);//enabling the timer

  //Abijith's edit:
  // Need REP0 != 0 to pulse on underflow
  //Check if necessary
  //LETIMER_RepeatSet(LETIMER0, 0, 1);

}

//avoiding the use of polled routine
//This function triggers the comp1
/*void timerWaitUs_irq(uint32_t us_wait){
  uint32_t ticks = ((ACTUAL_CLK_FREQ/PRESCALAR_VALUE)*us_wait)/1000000;
  uint32_t comp1 = LETIMER_CounterGet(LETIMER0) - ticks;
  LETIMER_CompareSet(LETIMER0,1,comp1);
  LETIMER_IntEnable(LETIMER0,LETIMER_IF_COMP1);
  LETIMER0->IEN |= LETIMER_IF_COMP1;
}*/

