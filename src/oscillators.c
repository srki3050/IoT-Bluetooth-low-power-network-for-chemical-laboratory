/***************************************************************************//**
 * @file
 * @brief Ocillator logic.
 * @resources https://siliconlabs.github.io/Gecko_SDK_Doc/efr32bg1/html/group__CMU.html
 *
 * Date:        11-14-2021
 * Author:      Abijith Ananda Krishnan
 * Description: This code was created by me to set the peripheral APIs of the
 *              oscillator.
 ******************************************************************************/

#include <stdbool.h>
#include "em_cmu.h"
#include <string.h>
#include "oscillators.h"
#include "app.h"

void toOscillate()
{
#if (LOWEST_ENERGY_MODE == 0 || LOWEST_ENERGY_MODE == 1 || LOWEST_ENERGY_MODE == 2)

      CMU_OscillatorEnable(cmuOsc_LFXO,true,true);
      CMU_ClockSelectSet (cmuClock_LFA, cmuSelect_LFXO);
      CMU_ClockEnable(cmuClock_LFA,true);

      CMU_ClockDivSet(cmuClock_LETIMER0, cmuClkDiv_4); //sets the multiplexer mentioned in lecture 5 clock diagram
      CMU_ClockEnable(cmuClock_LETIMER0,true);

      //Abijith's edit:
      // Enable ADC0 clock and HFPER clock
      CMU_ClockEnable(cmuClock_HFPER, true);
      CMU_ClockEnable(cmuClock_ADC0, true);

      //For LETIMER0
      //ASK Professor regarding this
      //CMU_ClockEnable(cmuClock_HFLE, true);

#else

    CMU_OscillatorEnable(cmuOsc_ULFRCO,true,true);
    CMU_ClockSelectSet (cmuClock_LFA, cmuSelect_ULFRCO);
    CMU_ClockEnable(cmuClock_LFA,true);

    CMU_ClockDivSet(cmuClock_LETIMER0, cmuClkDiv_1); //sets the multiplexer mentioned in lecture 5 clock diagram
    CMU_ClockEnable(cmuClock_LETIMER0,true);

    //Abijith's edit:
    // Enable ADC0 clock and HFPER clock
    CMU_ClockEnable(cmuClock_HFPER, true);
    CMU_ClockEnable(cmuClock_ADC0, true);

    //For LETIMER0
    //CMU_ClockEnable(cmuClock_HFLE, true);

#endif

} // toOscillate()
