/***************************************************************************//**
 * @file
 * @brief Core application logic.
 *******************************************************************************
 * # License
 * <b>Copyright 2020 Silicon Laboratories Inc. www.silabs.com</b>
 *******************************************************************************
 *
 * SPDX-License-Identifier: Zlib
 *
 * The licensor of this software is Silicon Laboratories Inc.
 *
 * This software is provided 'as-is', without any express or implied
 * warranty. In no event will the authors be held liable for any damages
 * arising from the use of this software.
 *
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it
 * freely, subject to the following restrictions:
 *
 * 1. The origin of this software must not be misrepresented; you must not
 *    claim that you wrote the original software. If you use this software
 *    in a product, an acknowledgment in the product documentation would be
 *    appreciated but is not required.
 * 2. Altered source versions must be plainly marked as such, and must not be
 *    misrepresented as being the original software.
 * 3. This notice may not be removed or altered from any source distribution.
 *
 * Date:        08-07-2021
 * Author:      Dave Sluiter
 * Description: This code was created by the Silicon Labs application wizard
 *              and started as "Bluetooth - SoC Empty".
 *              It is to be used only for ECEN 5823 "IoT Embedded Firmware".
 *              The MSLA referenced above is in effect.
 *
 ******************************************************************************/


#include "app.h"

// Include logging for this file
#define INCLUDE_LOG_DEBUG 1
#include "src/log.h"
//use the same for every .c file to use log functions



/*****************************************************************************
 * Application Power Manager callbacks
 *****************************************************************************/
#if defined(SL_CATALOG_POWER_MANAGER_PRESENT)



bool app_is_ok_to_sleep(void)
{

  return APP_IS_OK_TO_SLEEP;

} // app_is_ok_to_sleep()



sl_power_manager_on_isr_exit_t app_sleep_on_isr_exit(void)
{

  return APP_SLEEP_ON_ISR_EXIT;

} // app_sleep_on_isr_exit()



#endif // defined(SL_CATALOG_POWER_MANAGER_PRESENT)




/**************************************************************************//**
 * Application Init.
 *****************************************************************************/
SL_WEAK void app_init(void)
{
  // Abijith's changes
  // Put your application 1-time init code here
  // This is called once during start-up.
  // Don't call any Bluetooth API functions until after the boot event.


  // Student Edit: Add a call to gpioInit() here
  //refer lecture 5
  if(LOWEST_ENERGY_MODE == 1){
      sl_power_manager_add_em_requirement(SL_POWER_MANAGER_EM1);
  }
  else if(LOWEST_ENERGY_MODE == 2){
      sl_power_manager_add_em_requirement(SL_POWER_MANAGER_EM2);
  }

  gpioInit();
  toOscillate();
  initLETIMER0();

  // Enable LETIMER0 interrupts
  NVIC_ClearPendingIRQ(LETIMER0_IRQn);
  NVIC_EnableIRQ(LETIMER0_IRQn);
  //Abijith's edit:
  //initialize ADC from adc.c
  initADC();

  // Enable ADC interrupts
  NVIC_ClearPendingIRQ(ADC0_IRQn);
  NVIC_EnableIRQ(ADC0_IRQn);
}


/*****************************************************************************
 * delayApprox(), private to this file.
 * A value of 3500000 is ~ 1 second. After assignment 1 you can delete or
 * comment out this function. Wait loops are a bad idea in general.
 * We'll discuss how to do this a better way in the next assignment.
 *****************************************************************************/
//static void delayApprox(int delay)
//{
//  volatile int i;

//  for (i = 0; i < delay; ) {
//      i=i+1;
//  }

//} // delayApprox()




/**************************************************************************//**
 * Application Process Action.
 *****************************************************************************/
SL_WEAK void app_process_action(void)
{

}

/**************************************************************************//**
 * Bluetooth stack event handler.
 * This overrides the dummy weak implementation.
 *
 * @param[in] evt Event coming from the Bluetooth stack.
 *
 * The code here will process events from the Bluetooth stack. This is the only
 * opportunity we will get to act on an event.
 *****************************************************************************/

void sl_bt_on_event(sl_bt_msg_t *evt)
{

 // You may want to save some values from certain BLE events that your
 // new state machine can examine.
 handle_ble_event(evt); // put this code in ble.c/.h
#if DEVICE_IS_BLE_SERVER
 // SERVER
 // sequence through states driven by events
 //temperature_state_machine(evt); // put this code in scheduler.c/.h

 //Abijith's edit:
 //Comment out temperature State Machine
 //Adding Smoke detector state machine

 smoke_detector_state_machine(evt); // put this code in scheduler.c/.h

#else
 //CLIENT
 // sequence through service and characteristic discovery
 discovery_state_machine(evt); // put this code in src/scheduler.c/.h
#endif

} // sl_bt_on_event()
