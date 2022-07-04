/***************************************************************************//**
 * @file
 * @brief BLE logic.
 * @resources https://docs.silabs.com/bluetooth/3.1/
 *
 * Date:        08-10-2021
 * Author:      Abijith Ananda Krishnan
 * Description: The file was created to keep the ble related functions - Isolation functionality
 ******************************************************************************/

#ifndef SRC_BLE_H
#define SRC_BLE_H

#include "stdbool.h"
#include "sl_bt_api.h"
#include "gatt_db.h"
#include "sl_bgapi.h"
#include "sl_status.h"
#include "ble_device_type.h"

/*#define UINT8_TO_BITSTREAM(p, n) { *(p)++ = (uint8_t)(n); }
#define UINT32_TO_BITSTREAM(p, n) { *(p)++ = (uint8_t)(n); *(p)++ = (uint8_t)((n) >> 8); \
 *(p)++ = (uint8_t)((n) >> 16); *(p)++ = (uint8_t)((n) >> 24); }

#define UINT32_TO_FLOAT(m, e) (((uint32_t)(m) & 0x00FFFFFFU) | (uint32_t)((int32_t)(e) << 24))
// BLE Data Structure, save all of our private BT data in here.
// Modern C (circa 2021 does it this way)
// typedef ble_data_struct_t is referred to as an anonymous struct definition

#define BUFFER_SIZE 15
#define ERROR_EMPTY 0
#define ERROR_FULL 0xFF

typedef struct{
  uint16_t charHandle;  //char handle from the gatt_db.h
  size_t bufferLength;  //length of buffer in bytes to send
  uint8_t buffer[5];    //the actual data buffer for indication //5 for HTM and 2 for indications

}indication_circular_buffer_t;

typedef struct{
  indication_circular_buffer_t indication_circular_buffer[15];
  int tail;
  int head;
  int buffer_size;

}circular_buffer_t;*/

typedef struct {
 // values that are common to servers and clients

 bd_addr clientAddress;
 // values unique for server
   bd_addr serverAddress;
   uint8_t connectionHandle;
   uint8_t serverAddressType;
   uint8_t BondingHandle;
   uint32_t passkey;
   // Server side flags
     //bool htmIndicationEnable;
     //bool inFlight;
     bool connectionOpenServer;
     bool isBonded;
     bool buttonStatus;
     bool buttonStateIndicationEnable;
     //values unique for smoke detector
       bool smokeDetectorIndicationEnable;
     uint32_t externalSignals;
     float temperatureCelsius;
     float MQ9bvalues;
     bool datainflight;

 // values unique for client
   uint8_t clientAddressType;
   uint8_t connectionHandleClient;
   uint8_t discoveredCharacteristicHandle;
   uint32_t discoveredServiceHandle;
   int32_t receivedTemperatureValue;
   uint8_t connectionHandleClient_Open;
   uint8_t connectionHandleClient_Service;
   uint8_t connectionHandleClient_Characteristic;
   uint8_t connectionHandleClient_Confirmation;
   // Client side flags
     bool connectionOpenClient;
     bool gattProcedureCompleted;
     //bool AlreadyReadOpDone;
     //bool PBOFirstPB1Second;
} ble_data_struct_t;

ble_data_struct_t*  getBleDataPtr(void);
static const uint8_t btnPress[1] = {0x01};
static const uint8_t btnRelease[1] = {0x00};
#define temperature_measurement_indicate true;

void handle_ble_event(sl_bt_msg_t *evt);

//void temperatureIndicate(uint32_t temperature_in_c);

int32_t gattFloat32ToInt(const uint8_t *value_start_little_endian);

//void writeQueue(circular_buffer_t *q, indication_circular_buffer_t i);

//indication_circular_buffer_t* readQueue(circular_buffer_t *q);

/*indication_circular_buffer_t* fifoRead(circular_buffer_t *q);
void fifoWrite(circular_buffer_t *q, indication_circular_buffer_t i);
void fifoInitialise(circular_buffer_t *q);*/

#endif //SRC_BLE_H
