/*
 * ble_device_type.h
 *
 *  Created on: Feb 16, 2019
 *      Author: dan walkes
 *
 *      Editor: Mar 14, 2021, Dave Sluiter
 *      Change: Added some vertical white space and bd_addr array indices
 */

#ifndef SRC_BLE_DEVICE_TYPE_H_
#define SRC_BLE_DEVICE_TYPE_H_
#include <stdbool.h>

/*
 * Students:
 * Set to 1 to configure this build as a BLE server.
 * Set to 0 to configure as a BLE client
 */
#define DEVICE_IS_BLE_SERVER 1

// For your Bluetooth Client implementations.
// Set this #define to the bd_addr of the Gecko that will be your Server.
//                   bd_addr  [0]   [1]   [2]   [3]   [4]   [5] <- array indices
#define SERVER_BT_ADDRESS {{ 0x18, 0x63, 0x17, 0x57, 0xB, 0x0 }}
//#define SERVER_BT_ADDRESS {{ 0x23, 0x2C, 0x61, 0xCC, 0xCC, 0xCC }} - test data
//#define CLIENT_BT_ADDRESS {{ 0xFB, 0X4B, 0XEC, 0X14, 0X2E, 0X84}}


#if DEVICE_IS_BLE_SERVER

#define BUILD_INCLUDES_BLE_SERVER 1
#define BUILD_INCLUDES_BLE_CLIENT 0
#define BLE_DEVICE_TYPE_STRING "Server"
static inline bool IsServerDevice() { return true; }
static inline bool IsClientDevice() { return false; }

#else

#define BUILD_INCLUDES_BLE_SERVER 0
#define BUILD_INCLUDES_BLE_CLIENT 1
#define BLE_DEVICE_TYPE_STRING "Client"
static inline bool IsClientDevice() { return true;}
static inline bool IsServerDevice() { return false; }

#endif

#endif /* SRC_BLE_DEVICE_TYPE_H_ */
