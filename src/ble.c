/***************************************************************************//**
 * @file
 * @brief BLE logic.
 * @resources https://docs.silabs.com/bluetooth/3.1/
 *
 * Date:        11-14-2021
 * Author:      Abijith Ananda Krishnan
 * Description: The file was created to keep the ble related functions - Isolation of functionality
 ******************************************************************************/

#include "ble.h"
#define INCLUDE_LOG_DEBUG 1
#include "src/log.h"
#include "stdio.h"
#include "lcd.h"
#include "math.h"
#include "sl_bt_api.h"
// BLE private data
ble_data_struct_t ble_data;
static uint8_t advertisingSetHandle = 0xFF; //add static
sl_status_t statusCode;
bd_addr server_address = SERVER_BT_ADDRESS;
//circular_buffer_t circular_buffer;
ble_data_struct_t* getBleDataPtr(){
  return(&ble_data);
};

void handle_ble_event(sl_bt_msg_t *evt)
{
  if(DEVICE_IS_BLE_SERVER){
    switch (SL_BT_MSG_ID(evt->header)) {

      // ******************************************************
       // Events common to both Servers and Clients
       // ******************************************************
       // --------------------------------------------------------
       // This event indicates the device has started and the radio is ready.
       // Do not call any stack API commands before receiving this boot event!
       // Including starting BT stack soft timers!
       // --------------------------------------------------------
      case sl_bt_evt_system_boot_id:
        //smoke detector
        ble_data.smokeDetectorIndicationEnable = false;
        //ble_data.htmIndicationEnable = false;
        ble_data.connectionOpenServer = false;
        //ble_data.inFlight = false;
        ble_data.isBonded = false;
        ble_data.datainflight = false;

        statusCode =   sl_bt_system_get_identity_address(&ble_data.serverAddress, &ble_data.serverAddressType);
        if (statusCode != SL_STATUS_OK) {
            LOG_ERROR("sl_bt_system_get_identity_address() returned != 0 status=0x%04x", (unsigned int) statusCode);
        }
        statusCode =   sl_bt_advertiser_create_set(&advertisingSetHandle);
        if (statusCode != SL_STATUS_OK) {
            LOG_ERROR("sl_bt_advertiser_create_set() returned != 0 status=0x%04x", (unsigned int) statusCode);
        }
        statusCode =   sl_bt_advertiser_set_timing(
            advertisingSetHandle, // advertising set handle
            400, // min. adv. interval (milliseconds * 1.6)
            400, // max. adv. interval (milliseconds * 1.6)
            0,   // adv. duration
            0);  // max. num. adv. events
        if (statusCode != SL_STATUS_OK) {
            LOG_ERROR("sl_bt_advertiser_set_timing() returned != 0 status=0x%04x", (unsigned int) statusCode);
        }
        statusCode =   sl_bt_advertiser_start(
            advertisingSetHandle,
            sl_bt_advertiser_general_discoverable,
            sl_bt_advertiser_connectable_scannable);
        if (statusCode != SL_STATUS_OK) {
            LOG_ERROR("sl_bt_advertiser_start() returned != 0 status=0x%04x", (unsigned int) statusCode);
        }

        displayInit();

        displayPrintf( DISPLAY_ROW_NAME, "Server" );

        displayPrintf( DISPLAY_ROW_BTADDR, "%X:%X:%X:%X:%X:%X",
                       ble_data.serverAddress.addr[0],
                       ble_data.serverAddress.addr[1],
                       ble_data.serverAddress.addr[2],
                       ble_data.serverAddress.addr[3],
                       ble_data.serverAddress.addr[4],
                       ble_data.serverAddress.addr[5] );

        displayPrintf(DISPLAY_ROW_CONNECTION, "Advertising" );
        displayPrintf(DISPLAY_ROW_ASSIGNMENT, "Course Project TEAM 2");
        //displayPrintf(DISPLAY_ROW_TEMPVALUE,"");
        displayPrintf( DISPLAY_ROW_PASSKEY, "");
        displayPrintf(DISPLAY_ROW_ACTION, "");
        displayPrintf(DISPLAY_ROW_9, "");


        //statusCode = sl_bt_sm_delete_bondings();
        //if (statusCode != SL_STATUS_OK) {
        //    LOG_ERROR("sl_bt_sm_delete_bondings() returned != 0 status=0x%04x", (unsigned int) statusCode);
        //}

        //Check whether should we call this in IRQ Handler or in the boot event?
        statusCode = sl_bt_sm_configure (0x0F,sm_io_capability_displayyesno);
        if (statusCode != SL_STATUS_OK) {
            LOG_ERROR("sl_bt_sm_configure() returned != 0 status=0x%04x", (unsigned int) statusCode);
        }
        break;

      case sl_bt_evt_connection_opened_id:
        ble_data.connectionOpenServer = true;
        displayPrintf(DISPLAY_ROW_CONNECTION, "Connected" );
        //displayPrintf(DISPLAY_ROW_TEMPVALUE,"");
        ble_data.connectionHandle = evt->data.evt_connection_opened.connection;
        statusCode =   sl_bt_connection_set_parameters(
            evt->data.evt_connection_opened.connection,//connectionHandle, //check on this connect
            60,
            60,
            300,
            4515,
            0,  //min_ce_length
            0xffff); //max_ce_length
        statusCode =   sl_bt_advertiser_stop(advertisingSetHandle);
        if (statusCode != SL_STATUS_OK) {
            LOG_ERROR("sl_bt_advertiser_stop() returned != 0 status=0x%04x", (unsigned int) statusCode);
        }
        break;

      case sl_bt_evt_connection_closed_id:
        displayPrintf( DISPLAY_ROW_CONNECTION, "Advertising" );
        //displayPrintf(DISPLAY_ROW_TEMPVALUE,"");
        displayPrintf( DISPLAY_ROW_PASSKEY, "");
        displayPrintf(DISPLAY_ROW_ACTION, "");
        displayPrintf(DISPLAY_ROW_9, "");
        gpioLed0SetOff();
        gpioLed1SetOff();
        ble_data.connectionOpenServer = false;
        statusCode = sl_bt_advertiser_start(
            advertisingSetHandle,
            sl_bt_advertiser_general_discoverable,
            sl_bt_advertiser_connectable_scannable);
        if (statusCode != SL_STATUS_OK) {
            LOG_ERROR("sl_bt_advertiser_start() returned != 0 status=0x%04x", (unsigned int) statusCode);
        }

        //statusCode = sl_bt_sm_delete_bondings();
        //if (statusCode != SL_STATUS_OK) {
        //    LOG_ERROR("sl_bt_sm_delete_bondings() returned != 0 status=0x%04x", (unsigned int) statusCode);
        //}
        break;

      case sl_bt_evt_system_external_signal_id:
          if(evt->data.evt_system_external_signal.extsignals & evtButtonPressed_PB0){
              statusCode = sl_bt_gatt_server_write_attribute_value(gattdb_button_state, 0, sizeof(btnPress) , (const uint8_t*) &btnPress[0]);
              displayPrintf(DISPLAY_ROW_9, "Button Pressed");
              if(!ble_data.isBonded && ble_data.passkey)
              {
                statusCode = sl_bt_sm_passkey_confirm(ble_data.connectionHandle,1);
              }
              else if(ble_data.isBonded){
                  statusCode = sl_bt_gatt_server_send_indication(ble_data.connectionHandle, gattdb_button_state, sizeof(btnPress) , (const uint8_t*) &btnPress[0]);
              }
          }
          else if(evt->data.evt_system_external_signal.extsignals & evtButtonReleased_PB0){
            displayPrintf(DISPLAY_ROW_9, "Button Released");
            displayPrintf( DISPLAY_ROW_PASSKEY, "");
            displayPrintf(DISPLAY_ROW_ACTION, "");
            statusCode = sl_bt_gatt_server_write_attribute_value(gattdb_button_state, 0, sizeof(btnRelease) , (const uint8_t*) &btnRelease[0]);
            if(ble_data.isBonded)
              statusCode = sl_bt_gatt_server_send_indication(ble_data.connectionHandle, gattdb_button_state, sizeof(btnRelease) , (const uint8_t*) &btnRelease[0]);
          }
        break;

      case sl_bt_evt_connection_parameters_id:
        LOG_INFO("Connection parameters : Connection=%d, Interval=%d, Latency=%d, Timeout=%d, Security Mode=%d",
                 (int) (evt->data.evt_connection_parameters.connection),
                 (int) (evt->data.evt_connection_parameters.interval*1.25),
                 (int) (evt->data.evt_connection_parameters.latency),
                 (int) (evt->data.evt_connection_parameters.timeout*10),
                 (int) (evt->data.evt_connection_parameters.security_mode));

        break;

      case sl_bt_evt_gatt_server_characteristic_status_id:
        //Abijith's edit
        //Add newly created smoke service
        //if indication sent, let led on and turn on indicationEnable = true


        /*if(evt->data.evt_gatt_server_characteristic_status.characteristic == gattdb_temperature_measurement){
            if(evt->data.evt_gatt_server_characteristic_status.status_flags == sl_bt_gatt_server_client_config){
                if(evt->data.evt_gatt_server_characteristic_status.client_config_flags == gatt_indication){
                    gpioLed0SetOn();
                    ble_data.htmIndicationEnable = true;
                }
                if(evt->data.evt_gatt_server_characteristic_status.client_config_flags == gatt_disable){
                    gpioLed0SetOff();
                    displayPrintf( DISPLAY_ROW_TEMPVALUE, "");
                    ble_data.htmIndicationEnable = false;
                }
            }

            //client verifies that it got the data
            if(evt->data.evt_gatt_server_characteristic_status.status_flags == sl_bt_gatt_server_confirmation){
                //note that there is no indication in flight
                ble_data.inFlight = false;
            }
        }*/

        if(evt->data.evt_gatt_server_characteristic_status.characteristic == gattdb_Smoke_level){
            if(evt->data.evt_gatt_server_characteristic_status.status_flags == sl_bt_gatt_server_client_config){
                if(evt->data.evt_gatt_server_characteristic_status.client_config_flags == gatt_indication){
                    gpioLed0SetOn();
                    ble_data.smokeDetectorIndicationEnable = true;
                }
                if(evt->data.evt_gatt_server_characteristic_status.client_config_flags == gatt_disable){
                    gpioLed0SetOff();
                    //displayPrintf( DISPLAY_ROW_TEMPVALUE, "");
                    ble_data.smokeDetectorIndicationEnable = false;
                }
            }

            //client verifies that it got the data
            if(evt->data.evt_gatt_server_characteristic_status.status_flags == sl_bt_gatt_server_confirmation){
                //note that there is no indication in flight
                //ble_data.inFlight = false;
            }
        }

        if(evt->data.evt_gatt_server_characteristic_status.characteristic == gattdb_button_state){
            //write of CCCD for htm
            if(evt->data.evt_gatt_server_characteristic_status.status_flags == sl_bt_gatt_server_client_config){
                if(evt->data.evt_gatt_server_characteristic_status.client_config_flags == gatt_indication){
                    gpioLed1SetOn();
                    ble_data.buttonStateIndicationEnable = true;
                }
                if(evt->data.evt_gatt_server_characteristic_status.client_config_flags == gatt_disable){
                    gpioLed1SetOff();
                    displayPrintf( DISPLAY_ROW_TEMPVALUE, "");
                    ble_data.buttonStateIndicationEnable = false;
                }
            }

            //client verifies that it got the data
            if(evt->data.evt_gatt_server_characteristic_status.status_flags == sl_bt_gatt_server_confirmation){
                //note that there is no indication in flight
                //ble_data.inFlight = false;
            }
        }
       break;

     case sl_bt_evt_sm_confirm_bonding_id:
       ble_data.connectionHandle = evt->data.evt_sm_confirm_bonding.connection;
       statusCode = sl_bt_sm_bonding_confirm(ble_data.connectionHandle,1);
       if (statusCode != SL_STATUS_OK) {
           LOG_ERROR("sl_bt_sm_bonding_confirm() returned != 0 status=0x%04x", (unsigned int) statusCode);
       }
       break;

     case sl_bt_evt_sm_confirm_passkey_id:
       ble_data.connectionHandle = evt->data.evt_sm_confirm_passkey.connection;
       ble_data.passkey = evt->data.evt_sm_confirm_passkey.passkey;
       displayPrintf( DISPLAY_ROW_PASSKEY, "Passkey %4lu", ble_data.passkey);
       displayPrintf(DISPLAY_ROW_ACTION, "Confirm with PB0");
       break;

     case sl_bt_evt_sm_bonded_id:
       ble_data.connectionHandle = evt->data.evt_sm_bonded.connection;
       displayPrintf( DISPLAY_ROW_CONNECTION, "Bonded" );
       ble_data.isBonded = true;
       break;

     default:
       break;

    }//switch
  }//if
  else{
      switch (SL_BT_MSG_ID(evt->header)) {
        case sl_bt_evt_system_boot_id:
          statusCode =   sl_bt_system_get_identity_address(&ble_data.clientAddress, &ble_data.clientAddressType);

          ble_data.serverAddress = server_address;
          ble_data.connectionOpenClient = false;
          ble_data.gattProcedureCompleted = false;

           statusCode = sl_bt_scanner_set_mode(0x01, 0x00);
           if (statusCode != SL_STATUS_OK) {
               LOG_ERROR("sl_bt_scanner_set_mode() returned != 0 status=0x%04x", (unsigned int) statusCode);
           }//if

           statusCode = sl_bt_scanner_set_timing(0x01,80,40);
           if (statusCode != SL_STATUS_OK) {
               LOG_ERROR("sl_bt_scanner_set_timing() returned != 0 status=0x%04x", (unsigned int) statusCode);
           }//if

           statusCode = sl_bt_connection_set_default_parameters(60,60,0,4,0,0xffff);

           statusCode = sl_bt_scanner_start(0x1,0x1);
           if (statusCode != SL_STATUS_OK) {
               LOG_ERROR("sl_bt_scanner_start() returned != 0 status=0x%04x", (unsigned int) statusCode);
           }//if

           displayInit();
           displayPrintf( DISPLAY_ROW_NAME, "Client" );
           displayPrintf( DISPLAY_ROW_BTADDR, "%X:%X:%X:%X:%X:%X",
                          ble_data.clientAddress.addr[0],
                          ble_data.clientAddress.addr[1],
                          ble_data.clientAddress.addr[2],
                          ble_data.clientAddress.addr[3],
                          ble_data.clientAddress.addr[4],
                          ble_data.clientAddress.addr[5] );
           displayPrintf( DISPLAY_ROW_CONNECTION, "Discovering" );
           displayPrintf( DISPLAY_ROW_ASSIGNMENT, "A9");

           statusCode = sl_bt_sm_delete_bondings();
           if (statusCode != SL_STATUS_OK) {
               LOG_ERROR("sl_bt_sm_delete_bondings() returned != 0 status=0x%04x", (unsigned int) statusCode);
           }

           statusCode = sl_bt_sm_configure (0x0F,sm_io_capability_displayyesno);
           if (statusCode != SL_STATUS_OK) {
               LOG_ERROR("sl_bt_sm_configure() returned != 0 status=0x%04x", (unsigned int) statusCode);
           }
           break;

        case sl_bt_evt_scanner_scan_report_id:
          if(evt->data.evt_scanner_scan_report.address.addr[0] == ble_data.serverAddress.addr[0] &&
             evt->data.evt_scanner_scan_report.address.addr[1] == ble_data.serverAddress.addr[1] &&
             evt->data.evt_scanner_scan_report.address.addr[2] == ble_data.serverAddress.addr[2] &&
             evt->data.evt_scanner_scan_report.address.addr[3] == ble_data.serverAddress.addr[3] &&
             evt->data.evt_scanner_scan_report.address.addr[4] == ble_data.serverAddress.addr[4] &&
             evt->data.evt_scanner_scan_report.address.addr[5] == ble_data.serverAddress.addr[5] ){

             displayPrintf(DISPLAY_ROW_CONNECTION, "Connected" );
             displayPrintf( DISPLAY_ROW_BTADDR2, "%X:%X:%X:%X:%X:%X",
                                       ble_data.serverAddress.addr[0],
                                       ble_data.serverAddress.addr[1],
                                       ble_data.serverAddress.addr[2],
                                       ble_data.serverAddress.addr[3],
                                       ble_data.serverAddress.addr[4],
                                       ble_data.serverAddress.addr[5] );
             statusCode = sl_bt_scanner_stop();
             if (statusCode != SL_STATUS_OK) {
                 LOG_ERROR("sl_bt_scanner_start() returned != 0 status=0x%04x", (unsigned int) statusCode);
             }//if

              statusCode = sl_bt_connection_open(ble_data.serverAddress,sl_bt_gap_public_address,sl_bt_gap_phy_1m,&ble_data.connectionHandleClient);
              if (statusCode != SL_STATUS_OK) {
                  LOG_ERROR("sl_bt_connection_open() returned != 0 status=0x%04x", (unsigned int) statusCode);
              }//if
          }//if
          break;

        case sl_bt_evt_connection_opened_id:
          ble_data.connectionHandleClient = evt->data.evt_connection_opened.connection;
          ble_data.connectionOpenClient = true;
          displayPrintf(DISPLAY_ROW_CONNECTION, "Handling Indications");
          break;

        case sl_bt_evt_gatt_procedure_completed_id:
          if(evt->data.evt_gatt_procedure_completed.result == 0x110F){
              statusCode = sl_bt_sm_increase_security(ble_data.connectionHandleClient);
              if (statusCode != SL_STATUS_OK) {
                  LOG_ERROR("sl_bt_sm_increase_security() returned != 0 status=0x%04x", (unsigned int) statusCode);
              }//if
          }
          else if(evt->data.evt_gatt_procedure_completed.result != 0){
              LOG_ERROR("sl_bt_scanner_start() returned != 0 status=0x%04x", (unsigned int) evt->data.evt_gatt_procedure_completed.result);
          }

          break;

        case sl_bt_evt_gatt_service_id:
          ble_data.connectionHandleClient = evt->data.evt_gatt_service.connection;
          ble_data.discoveredServiceHandle = evt->data.evt_gatt_service.service;
          break;

         case sl_bt_evt_gatt_characteristic_id:
           ble_data.connectionHandleClient = evt->data.evt_gatt_characteristic.connection;
           ble_data.discoveredCharacteristicHandle = evt->data.evt_gatt_characteristic.characteristic;
           break;

         case sl_bt_evt_gatt_characteristic_value_id:
           ble_data.connectionHandleClient = evt->data.evt_gatt_characteristic_value.connection;
           if( evt->data.evt_gatt_characteristic_value.characteristic == gattdb_temperature_measurement &&
               evt->data.evt_gatt_characteristic_value.att_opcode == sl_bt_gatt_handle_value_indication){
               ble_data.receivedTemperatureValue = gattFloat32ToInt(&evt->data.evt_gatt_characteristic_value.value.data[0]);
               displayPrintf(DISPLAY_ROW_TEMPVALUE, "Temp = %d C",ble_data.receivedTemperatureValue);
               statusCode = sl_bt_gatt_send_characteristic_confirmation(ble_data.connectionHandleClient);
               if (statusCode != SL_STATUS_OK) {
                   LOG_ERROR("sl_bt_gatt_send_characteristic_confirmation() returned != 0 status=0x%04x", (unsigned int) statusCode);
               }//if
           }

           if( evt->data.evt_gatt_characteristic_value.characteristic == gattdb_button_state &&
               evt->data.evt_gatt_characteristic_value.att_opcode == sl_bt_gatt_handle_value_indication){
               if(evt->data.evt_gatt_characteristic_value.value.data[0] == 1)
                 displayPrintf(DISPLAY_ROW_9, "Button Pressed");
               else
                 displayPrintf(DISPLAY_ROW_9, "Button Released");
               statusCode = sl_bt_gatt_send_characteristic_confirmation(ble_data.connectionHandleClient);
               if (statusCode != SL_STATUS_OK) {
                   LOG_ERROR("sl_bt_gatt_send_characteristic_confirmation() returned != 0 status=0x%04x", (unsigned int) statusCode);
               }//if
           }
           if( evt->data.evt_gatt_characteristic_value.characteristic == gattdb_button_state &&
               evt->data.evt_gatt_characteristic_value.att_opcode == sl_bt_gatt_read_response){
               if(evt->data.evt_gatt_characteristic_value.value.data[0] == 1)
                 displayPrintf(DISPLAY_ROW_9, "Button Pressed");
               else
                 displayPrintf(DISPLAY_ROW_9, "Button Released");
          }


          break;
         case sl_bt_evt_connection_closed_id:
           ble_data.connectionOpenClient = false;
           displayPrintf( DISPLAY_ROW_CONNECTION, "Discovering" );
           displayPrintf(DISPLAY_ROW_TEMPVALUE,"");
           displayPrintf( DISPLAY_ROW_BTADDR2, "");

           statusCode = sl_bt_scanner_start(1,sl_bt_scanner_discover_observation);
           if (statusCode != SL_STATUS_OK) {
               LOG_ERROR("sl_bt_scanner_start() returned != 0 status=0x%04x", (unsigned int) statusCode);
           }//if
           statusCode = sl_bt_sm_delete_bondings();
           if (statusCode != SL_STATUS_OK) {
               LOG_ERROR("sl_bt_sm_delete_bondings() returned != 0 status=0x%04x", (unsigned int) statusCode);
           }
           break;

         case sl_bt_evt_system_external_signal_id:
             if(evt->data.evt_system_external_signal.extsignals & evtButtonPressed_PB1){
                 bool btn0on = !GPIO_PinInGet(PB0_port, PB0_pin);
                 if(btn0on){
                     ble_data.buttonStateIndicationEnable = !ble_data.buttonStateIndicationEnable;
                     if(ble_data.buttonStateIndicationEnable){
                         statusCode = sl_bt_gatt_set_characteristic_notification(ble_data.connectionHandleClient,gattdb_button_state,sl_bt_gatt_disable);
                     }
                     else{
                         statusCode = sl_bt_gatt_set_characteristic_notification(ble_data.connectionHandleClient,gattdb_button_state,sl_bt_gatt_indication);
                     }
                 }
                 statusCode = sl_bt_gatt_read_characteristic_value(ble_data.connectionHandleClient,gattdb_button_state);

             }
             else if(evt->data.evt_system_external_signal.extsignals & evtButtonReleased_PB1){
             }

             if(evt->data.evt_system_external_signal.extsignals & evtButtonPressed_PB0){
               displayPrintf(DISPLAY_ROW_9, "Button Pressed");
               if(!ble_data.isBonded && ble_data.passkey) //change to boolean
               {
                 statusCode = sl_bt_sm_passkey_confirm(ble_data.connectionHandleClient,1);
                 if (statusCode != SL_STATUS_OK) {
                     LOG_ERROR("sl_bt_sm_passkey_confirm() returned != 0 status=0x%04x", (unsigned int) statusCode);
                 }
               }
             }
             else if(evt->data.evt_system_external_signal.extsignals & evtButtonReleased_PB0){
                 displayPrintf(DISPLAY_ROW_9, "Button Released");
                 displayPrintf( DISPLAY_ROW_PASSKEY, "");
                 displayPrintf(DISPLAY_ROW_ACTION, "");
             }
           break;

        case sl_bt_evt_sm_confirm_passkey_id:
          ble_data.connectionHandle = evt->data.evt_sm_confirm_passkey.connection;
          ble_data.passkey = evt->data.evt_sm_confirm_passkey.passkey;
          displayPrintf( DISPLAY_ROW_PASSKEY, "Passkey %4lu", ble_data.passkey);
          displayPrintf(DISPLAY_ROW_ACTION, "Confirm with PB0");
          break;

        case sl_bt_evt_sm_bonded_id:
          ble_data.connectionHandle = evt->data.evt_sm_bonded.connection;
          ble_data.BondingHandle = evt->data.evt_sm_bonded.bonding;
          displayPrintf( DISPLAY_ROW_CONNECTION, "Bonded" );
          displayPrintf( DISPLAY_ROW_PASSKEY, "");
          displayPrintf(DISPLAY_ROW_ACTION, "");
          ble_data.isBonded = true;
          break;

       default:
           break;
      }//switch
  }//else
}

/*void temperatureIndicate(uint32_t temperature_in_c){

  // -------------------------------------------------------------------//
  //Update our local GATT DB and send indication if enabled for the characteristic
  // -------------------------------------------------------------------//
  uint8_t   htm_temperature_buffer[5];

  // Stores the temperature data in the Health Thermometer (HTM) format.// format of the buffer is: flags_byte + 4-bytes of IEEE-11073 32-bitfloat

  uint8_t   *p = htm_temperature_buffer; // Pointer to HTM temperature buffer needed for converting values to bitstream.
  uint32_t  htm_temperature_flt;         // Stores the temperature data read from the sensor in the IEEE-11073 32-bit float format
  uint8_t   flags = 0x00;

  // HTM flags set as 0 for Celsius, no time stamp and no temperature type.
  // "bitstream" refers to the order of bytes and bits sent. byte[0] is sent first, followed by byte[1]...

  UINT8_TO_BITSTREAM(p, flags);

  // put the flags byte in first, "convert" is a strong word, it places the byte into the buffer
  // Convert sensor data to IEEE-11073 32-bit floating point format.

  htm_temperature_flt = UINT32_TO_FLOAT(temperature_in_c*1000, -3);

  // Convert temperature to bitstream and place it in the htm_temperature_buffer

  UINT32_TO_BITSTREAM(p, htm_temperature_flt);

  //-------------------------------// Write our local GATT DB// -------------------------------

  statusCode = sl_bt_gatt_server_write_attribute_value(
          gattdb_temperature_measurement,// handle from gatt_db.h
          0, // offset
          5, // length
          &htm_temperature_buffer[0]// pointer to buffer where data is
          );



  if (statusCode != SL_STATUS_OK) {
      LOG_ERROR("sl_bt_gatt_server_write_attribute_value() returned != 0 status=0x%04x", (unsigned int) statusCode);
  }


  if(ble_data.htmIndicationEnable && ble_data.connectionOpenServer){
      statusCode = sl_bt_gatt_server_send_indication(ble_data.connectionHandle, gattdb_temperature_measurement, sizeof(htm_temperature_buffer), &htm_temperature_buffer[0]);
      if (statusCode != SL_STATUS_OK) {
            LOG_ERROR("sl_bt_gatt_server_send_indication() returned != 0 status=0x%04x", (unsigned int) statusCode);
      }

      ble_data.inFlight = true;
  }

}*/


//Abijith's edit:
//Add function to send indication
