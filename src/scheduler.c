/***************************************************************************//**
 * @file
 * @brief Scheduler logic.
 * @resources https://siliconlabs.github.io/Gecko_SDK_Doc/efr32bg13/html/em__core_8h.html
 *
 * Date:        09-09-2021
 * Author:      Abijith Ananda Krishnan
 * Description: This code was created by me to use the defined functions to schedule
 * the temperature read and write operation
 *
 ******************************************************************************/

#include "scheduler.h"
#include "src/log.h"
#include "stdio.h"
#include "ble.h"
#define INCLUDE_LOG_DEBUG 1

uint32_t myEvents = 0;
//sl_status_t statusCode;
void schedulerSetUFEvent(void){

  CORE_DECLARE_IRQ_STATE;
  //declares a variable to hold the state of
  //NVIC interrupt enable register

  CORE_ENTER_CRITICAL();
  //shuts down all the interrupts in the NVIC
  //NVIC_pending bit is 0
  sl_bt_external_signal(evtUF); //reads - myEvents, sets the bit(or for setting, exor for clearing)
  //takingTemperatureSensorReading();
  //Read -Modify-Write
  CORE_EXIT_CRITICAL();
  //NVIC interrupts are enabled back
}

/*void schedulerSetCOMP1Event(void){

  CORE_DECLARE_IRQ_STATE;
  //declares a variable to hold the state of
  //NVIC interrupt enable register

  CORE_ENTER_CRITICAL();
  //shuts down all the interrupts in the NVIC
  //NVIC_pending bit is 0
  sl_bt_external_signal(evtCOMP1); //reads - myEvents, sets the bit(or for setting, exor for clearing)
  //takingTemperatureSensorReading();
  //Read -Modify-Write

  CORE_EXIT_CRITICAL();
  //NVIC interrupts are enabled back
}

void schedulerSetI2CEvent(void){

  CORE_DECLARE_IRQ_STATE;
  //declares a variable to hold the state of
  //NVIC interrupt enable register

  CORE_ENTER_CRITICAL();
  //shuts down all the interrupts in the NVIC
  //NVIC_pending bit is 0
  sl_bt_external_signal(evtI2CTransfer); //reads - myEvents, sets the bit(or for setting, exor for clearing)
  //takingTemperatureSensorReading();
  //Read -Modify-Write

  CORE_EXIT_CRITICAL();
  //NVIC interrupts are enabled back
}*/

void schedulerSetButtonPB0ClickEvent(){

  CORE_DECLARE_IRQ_STATE;
  //declares a variable to hold the state of
  //NVIC interrupt enable register

  CORE_ENTER_CRITICAL();
  //shuts down all the interrupts in the NVIC
  //NVIC_pending bit is 0
  if(GPIO_PinInGet(PB0_port, PB0_pin))
    sl_bt_external_signal(evtButtonReleased_PB0);
  else
    sl_bt_external_signal(evtButtonPressed_PB0);
  //takingTemperatureSensorReading();
  //Read -Modify-Write

  CORE_EXIT_CRITICAL();
  //NVIC interrupts are enabled back
}

void schedulerSetButtonPB1ClickEvent(){

  CORE_DECLARE_IRQ_STATE;
  //declares a variable to hold the state of
  //NVIC interrupt enable register

  CORE_ENTER_CRITICAL();
  //shuts down all the interrupts in the NVIC
  //NVIC_pending bit is 0
  if(GPIO_PinInGet(PB1_port, PB1_pin))
    sl_bt_external_signal(evtButtonReleased_PB1);
  else
    sl_bt_external_signal(evtButtonPressed_PB1);
  //takingTemperatureSensorReading();
  //Read -Modify-Write

  CORE_EXIT_CRITICAL();
  //NVIC interrupts are enabled back
}

void schedulerSetADCEvent(void){

  CORE_DECLARE_IRQ_STATE;
  //declares a variable to hold the state of
  //NVIC interrupt enable register

  CORE_ENTER_CRITICAL();
  //shuts down all the interrupts in the NVIC
  //NVIC_pending bit is 0
  sl_bt_external_signal(evtADC); //reads - myEvents, sets the bit(or for setting, exor for clearing)
  //takingTemperatureSensorReading();
  //Read -Modify-Write
  CORE_EXIT_CRITICAL();
  //NVIC interrupts are enabled back
}

void schedulerSetSmokeSensorOffEvent(void){
   CORE_DECLARE_IRQ_STATE;
   //declares a variable to hold the state of
   //NVIC interrupt enable register

   CORE_ENTER_CRITICAL();
   //shuts down all the interrupts in the NVIC
   //NVIC_pending bit is 0
   sl_bt_external_signal(evtSmokeSensorTurnOff); //reads - myEvents, sets the bit(or for setting, exor for clearing)
   //takingTemperatureSensorReading();
   //Read -Modify-Write

   CORE_EXIT_CRITICAL();
   //NVIC interrupts are enabled back
}

/*uint32_t getNextEvent(void){

  uint32_t theEvent=0;

  CORE_DECLARE_IRQ_STATE;
  CORE_ENTER_CRITICAL();
  //select one event to return to the caller
  //this is how we apply priority
  if(myEvents & evtUF){
      theEvent = evtUF;
      myEvents ^= evtUF; //to clear, please do exor
  }
  else if(myEvents & evtCOMP1){
      theEvent = evtCOMP1;
      myEvents ^= evtCOMP1;
  }
  else if(myEvents & evtI2CTransfer){
      theEvent = evtI2CTransfer;
      myEvents ^= evtI2CTransfer;
  }
  else if(myEvents & evtADC){
        theEvent = evtADC;
        myEvents ^= evtADC;
    }
  //add else if for more options
  //clear event in data structure
  CORE_EXIT_CRITICAL();
  return theEvent;
}*/



//Abijith's edit:
//Create new State Machine for Smoke detector
//Idle               - Turn on Smoke detector
//SmokeSensorTurnOn  - Take value from pin
//SmokeSensorTurnOff - Turn off Smoke detector
//AnalogToPPM        - Convert it to PPM with formula

void  smoke_detector_state_machine(sl_bt_msg_t *evt){
  ble_data_struct_t *ble_data = getBleDataPtr();
  if((SL_BT_MSG_ID(evt->header) != sl_bt_evt_system_external_signal_id) || (!(*ble_data).smokeDetectorIndicationEnable) || (!(*ble_data).connectionOpenServer)){
      return;
  }
  sl_status_t statusCode;
  Smoke_State_t currentState;
  static Smoke_State_t nextState      = IdleSensor;

  currentState                  = nextState;

  switch(currentState){
    case IdleSensor:{
      nextState                  = IdleSensor;
      if(evt->data.evt_system_external_signal.extsignals & evtUF){
         smokeDetectorTurnOn();
         //do ADC interrupt
         //ADC_IntEnable(ADC0, ADC_IEN_SINGLE);
         //ADC_Start(ADC0, adcStartSingle);
         //schedulerSetADCEvent();
         printf("ToSmoke Sensor Power On");
         nextState              = SmokeSensorPowerOn;
      }
      else{
          printf("Transition from 1 to 2 Failed");
      }
      break;
    }
    case SmokeSensorPowerOn:{
      nextState                  = SmokeSensorPowerOn;
      if(evt->data.evt_system_external_signal.extsignals ^ evtADC){
          printf("If entered for state 2");
          sl_power_manager_add_em_requirement(SL_POWER_MANAGER_EM1);
          //gets the value and conversion to PPM is complete and send indication
          takeSmokeDetectorReading();
          //schedulerSetSmokeSensorOffEvent();
          printf("ToSmoke Sensor Power Off");
          nextState              = SmokeSensorPowerOff;
      }
      /*else{
          printf("Transition from 2 to 3 Failed");
      }*/
      break;
    }
    case SmokeSensorPowerOff:{
      nextState                  = SmokeSensorPowerOff;
      if(evt->data.evt_system_external_signal.extsignals & evtSmokeSensorTurnOff){
          sl_power_manager_remove_em_requirement(SL_POWER_MANAGER_EM1);
          smokeDetectorTurnOff();
          statusCode = sl_bt_gatt_server_write_attribute_value(
              gattdb_Smoke_level,// handle from gatt_db.h
                    0, // offset
                    sizeof(ble_data->MQ9bvalues), // length
                    &ble_data->MQ9bvalues// pointer to buffer where data is
                    );
          if(statusCode!=SL_STATUS_OK){
              LOG_INFO("Attribute Not Written");
          }
          else{
             statusCode = sl_bt_gatt_server_send_indication(ble_data->connectionHandle,
                                                gattdb_Smoke_level,
                                                sizeof(ble_data->MQ9bvalues),
                                                &ble_data->MQ9bvalues);
             if(statusCode!=SL_STATUS_OK){
                 LOG_INFO("Indications failed");
             }
             else{
                 ble_data->datainflight = true;
             }
          }
          nextState              = IdleSensor;
          printf("Idle Sensor");
      }
      else{
          printf("Transition from 3 to 1 failed");
      }
      break;
    }
  }
}



/*void temperature_state_machine(sl_bt_msg_t *evt){

  ble_data_struct_t *ble_data = getBleDataPtr();
  if((SL_BT_MSG_ID(evt->header) != sl_bt_evt_system_external_signal_id) || (!(*ble_data).htmIndicationEnable) || (!(*ble_data).connectionOpenServer)){
      return;
  }
           State_t currentState;
           static State_t nextState      = Idle;

           currentState                  = nextState;

           switch(currentState){

             case Idle:{
               nextState                  = Idle;
               if(evt->data.evt_system_external_signal.extsignals & evtUF){
                   si7021TurnOn();
                   timerWaitUs_irq(80000);
                   nextState              = Si7021PowerOn;
               }
               break;
             }
             case Si7021PowerOn:{
               nextState                  = Si7021PowerOn;
               if(evt->data.evt_system_external_signal.extsignals & evtCOMP1){
                   sl_power_manager_add_em_requirement(SL_POWER_MANAGER_EM1);
                   takeTemperatureReading();
                   nextState              = waitTimer10point8;
               }
               break;
             }
             case waitTimer10point8:{
               nextState                  = waitTimer10point8;
               if(evt->data.evt_system_external_signal.extsignals & evtI2CTransfer){
                   sl_power_manager_remove_em_requirement(SL_POWER_MANAGER_EM1);
                   timerWaitUs_irq(10800);
                   nextState              = cmdToWrite;
               }
               break;
             }
             case cmdToWrite:{
               nextState                   = cmdToWrite;
               if(evt->data.evt_system_external_signal.extsignals & evtCOMP1){
                   sl_power_manager_add_em_requirement(SL_POWER_MANAGER_EM1);
                   readTemperatureReading();
                   nextState               = Si7021PowerOff;
               }
               break;
             }
             case Si7021PowerOff:{
               nextState                  = Si7021PowerOff;
               if(evt->data.evt_system_external_signal.extsignals & evtI2CTransfer){
                   sl_power_manager_remove_em_requirement(SL_POWER_MANAGER_EM1);
                   //si7021TurnOff();
                   convertReadTempToC();
                   nextState              = Idle;
               }
               break;
             }
             default:{
               break;
             }

           } // switch
    //} // if
} // temperature_state_machine()*/

void discovery_state_machine(sl_bt_msg_t *evt){
  ble_data_struct_t *ble_data = getBleDataPtr();
  Discovery_State_t currentState;
  sl_status_t statusCode;

  //https://www.tutorialspoint.com/cprogramming/c_structures.htm#:~:text=C%20-%20Structures%201%20Defining%20a%20Structure.%20To,Pointers%20to%20Structures.%20...%205%20Bit%20Fields.%20
  static uuid_info htmService =
  {
      .data = {0x09, 0x18},
      .len = 2
  };

  static uuid_info htmCharacteristic =
  {
      .data = {0x1C, 0x2A},
      .len = 2
  };

  static uuid_info btnService =
  {
      .data = { 0x89, 0x62, 0x13, 0x2d, 0x2a, 0x65, 0xec, 0x87, 0x3e, 0x43, 0xc8, 0x38, 0x01, 0x00, 0x00, 0x00 },
      .len = 16
  };

  static uuid_info btnCharacteristic =
  {
      .data = { 0x89, 0x62, 0x13, 0x2d, 0x2a, 0x65, 0xec, 0x87, 0x3e, 0x43, 0xc8, 0x38, 0x02, 0x00, 0x00, 0x00 },
      .len = 16
  };

  static Discovery_State_t nextState      = DiscoverServiceState_Temperature;

  currentState                  = nextState;

             switch(currentState){
               case DiscoverServiceState_Temperature:

                if(ble_data->connectionOpenClient){
                    ble_data->connectionHandleClient_Open = ble_data->connectionHandleClient;
                    statusCode = sl_bt_gatt_discover_primary_services_by_uuid(ble_data->connectionHandleClient, htmService.len, &htmService.data[0]);
                    if (statusCode != SL_STATUS_OK) {
                        printf("sl_bt_gatt_discover_primary_services_by_uuid() returned != 0 status=0x%04x", (unsigned int) statusCode);
                    }//if
                    nextState              = DiscoverCharacteristicState_Temperature;
                }
                break;

              case DiscoverCharacteristicState_Temperature:

                if(ble_data->connectionOpenClient && SL_BT_MSG_ID(evt->header) == sl_bt_evt_gatt_procedure_completed_id){
                  ble_data->connectionHandleClient_Service = ble_data->connectionHandleClient;
                  statusCode = sl_bt_gatt_discover_characteristics_by_uuid(ble_data->connectionHandleClient, ble_data->discoveredServiceHandle, htmCharacteristic.len, &htmCharacteristic.data[0]);
                  if (statusCode != SL_STATUS_OK) {
                      printf("sl_bt_gatt_discover_characteristics_by_uuid() returned != 0 status=0x%04x", (unsigned int) statusCode);
                  }
                  nextState              = SetNotificationState_Temperature;
                }
                break;

              case SetNotificationState_Temperature:

                if(ble_data->connectionOpenClient && SL_BT_MSG_ID(evt->header) == sl_bt_evt_gatt_procedure_completed_id){
                  ble_data->connectionHandleClient_Characteristic = ble_data->connectionHandleClient;
                  statusCode = sl_bt_gatt_set_characteristic_notification(ble_data->connectionHandleClient, ble_data->discoveredCharacteristicHandle, sl_bt_gatt_indication);
                  if (statusCode != SL_STATUS_OK) {
                      printf("sl_bt_gatt_set_characteristic_notification() returned != 0 status=0x%04x", (unsigned int) statusCode);
                  }
                  nextState              = DiscoverServiceState_Button;
                }
                break;

               case DiscoverServiceState_Button:

                  if(ble_data->connectionOpenClient && SL_BT_MSG_ID(evt->header) == sl_bt_evt_gatt_procedure_completed_id){
                      statusCode = sl_bt_gatt_discover_primary_services_by_uuid(ble_data->connectionHandleClient_Open, btnService.len, &btnService.data[0]);
                      if (statusCode != SL_STATUS_OK) {
                          printf("sl_bt_gatt_discover_primary_services_by_uuid() returned != 0 status=0x%04x", (unsigned int) statusCode);
                      }//if
                      nextState              = DiscoverCharacteristicState_Button;
                  }
                 break;

               case DiscoverCharacteristicState_Button:

                  if(ble_data->connectionOpenClient && SL_BT_MSG_ID(evt->header) == sl_bt_evt_gatt_procedure_completed_id){
                    statusCode = sl_bt_gatt_discover_characteristics_by_uuid(ble_data->connectionHandleClient_Service, ble_data->discoveredServiceHandle, btnCharacteristic.len, &btnCharacteristic.data[0]);
                    if (statusCode != SL_STATUS_OK) {
                        printf("sl_bt_gatt_discover_characteristics_by_uuid() returned != 0 status=0x%04x", (unsigned int) statusCode);
                    }
                    nextState              = SetNotificationState_Button;
                  }
                  break;

               case SetNotificationState_Button:

                  if(ble_data->connectionOpenClient && SL_BT_MSG_ID(evt->header) == sl_bt_evt_gatt_procedure_completed_id){
                    statusCode = sl_bt_gatt_set_characteristic_notification(ble_data->connectionHandleClient_Characteristic, gattdb_button_state, sl_bt_gatt_indication);
                    if (statusCode != SL_STATUS_OK) {
                        printf("sl_bt_gatt_set_characteristic_notification() returned != 0 status=0x%04x", (unsigned int) statusCode);
                    }
                    nextState              = ProcedureComplete;
                  }
                  break;

               case ProcedureComplete:

                 if (SL_BT_MSG_ID(evt->header) == sl_bt_evt_gatt_procedure_completed_id) {
                     nextState = CloseEvent;
                 }
                 break;

               case CloseEvent:

                 if (SL_BT_MSG_ID(evt->header) == sl_bt_evt_connection_closed_id) {
                     nextState = DiscoverServiceState_Temperature;
                 }
                 break;
             }
}//discovery_state_machine()
