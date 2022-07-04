/***************************************************************************//**
 * @file
 * @brief Scheduler logic.
 * @resources https://siliconlabs.github.io/Gecko_SDK_Doc/efr32bg13/html/em__core_8h.html
 *
 * Date:        09-09-2021
 * Author:      Abijith Ananda Krishnan
 * Description: This code was created by me to define the functions to schedule
 * the temperature read and write operation
 *
 ******************************************************************************/

#ifndef __myScheduler
#define __myScheduler

#include "timers.h"
#include "app.h"
#include "sl_bt_api.h"
#include "gpio.h"
#include "lcd.h"
#include "ble.h"
#include "smoke_detector.h"

typedef enum {
  evtUF          = 1,
  evtADC         = 2,
  evtSmokeSensorTurnOff = 4,
  /*evtCOMP1       = 2,
  evtI2CTransfer = 4,*/
  evtButtonReleased_PB0 = 8,
  evtButtonPressed_PB0 = 16,
  evtButtonReleased_PB1 = 32,
  evtButtonPressed_PB1 = 64,
}my_eventNum_t;

/*typedef enum uint32_t {
  Idle = 0,
  Si7021PowerOn = 1,
  waitTimer10point8 = 2,
  cmdToWrite = 3,
  Si7021PowerOff = 4
}State_t;*/

typedef enum uint32_t{
  IdleSensor          = 0,
  SmokeSensorPowerOn  = 1,
  SmokeSensorPowerOff = 2,
}Smoke_State_t;

typedef enum {
  DiscoverServiceState_Temperature = 0,
  DiscoverCharacteristicState_Temperature = 1,
  SetNotificationState_Temperature = 2,
  DiscoverServiceState_Button = 3,
  DiscoverCharacteristicState_Button = 4,
  SetNotificationState_Button = 5,
  ProcedureComplete = 6,
  CloseEvent = 7
}Discovery_State_t;

typedef struct {
    uint8_t data[20];
    uint8_t len;
} uuid_info;

void schedulerSetUFEvent(void);
//void schedulerSetCOMP1Event(void);
//void schedulerSetI2CEvent(void);
void schedulerSetADCEvent(void);
void schedulerSetButtonPB0ClickEvent();
void schedulerSetButtonPB1ClickEvent();
//uint32_t getNextEvent(void);
//void temperature_state_machine(sl_bt_msg_t *evt);
void smoke_detector_state_machine(sl_bt_msg_t *evt);
void discovery_state_machine(sl_bt_msg_t *evt);

#endif //
