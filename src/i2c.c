#include "i2c.h"
#define INCLUDE_LOG_DEBUG 1
#include "src/log.h"

I2C_TransferSeq_TypeDef  transferSequence;
uint8_t                  cmd_data = 0xF3; // make this global for IRQs in A4
uint16_t                 read_data; // make this global for IRQs in A4

void myI2CINIT(){

  I2CSPM_Init_TypeDef I2C_Config = {
      .port = I2C0,
      .sclPort = gpioPortC,
      .sclPin = 10,
      .sdaPort = gpioPortC,
      .sdaPin = 11,
      .portLocationScl = 14,
      .portLocationSda = 16,
      .i2cRefFreq = 0,
      .i2cMaxFreq = I2C_FREQ_STANDARD_MAX,
      .i2cClhr = i2cClockHLRStandard
  }; //to be validated

  I2CSPM_Init(&I2C_Config); //initialized the I2CSPM peripheral
  //can be used instead of I2C_Init
  //i2c_bus_frequency = I2C_BusFreqGet(I2C0); //check value
}

void takeTemperatureReading(){
  I2C_TransferReturn_TypeDef transferStatus;

  myI2CINIT(); //just to make sure bits are set before the transfer

  transferSequence.addr = 0x40 << 1; //0x80 - make room for R/W bit
  transferSequence.flags =  I2C_FLAG_WRITE;
  transferSequence.buf[0].data = &cmd_data;
  transferSequence.buf[0].len = sizeof(cmd_data);
  //if(InterruptSource & LETIMER_IF_COMP1)
  NVIC_EnableIRQ(I2C0_IRQn);//IEN->1

  //should this code be in the IRQHandler
  transferStatus = I2C_TransferInit(I2C0, &transferSequence);

  if (transferStatus < i2cTransferDone) {
     LOG_ERROR ("I2CSPM_Transfer: I2C bus read cmd failed");
  }

} // takeTemperatureReading()


void readTemperatureReading(){
  I2C_TransferReturn_TypeDef transferStatus;

  transferSequence.addr = 0x40 << 1; //how does left shift work here
  transferSequence.flags =  I2C_FLAG_READ;
  transferSequence.buf[0].data = &read_data; //how to take 2 bytes
  transferSequence.buf[0].len = sizeof(read_data);

  NVIC_EnableIRQ(I2C0_IRQn);//IEN->1

  transferStatus = I2C_TransferInit(I2C0, &transferSequence);

  if (transferStatus < i2cTransferDone) {
      LOG_ERROR ("I2CSPM_Transfer: I2C bus write cmd failed");
  }

} // readTemperatureReading()

void convertReadTempToC() {
  ble_data_struct_t *ble_data = getBleDataPtr();
  float     temperatureCelsius;
  uint16_t  read_data_first_half;
  uint16_t  read_data_second_half;

  read_data_first_half = read_data & 0xFF00;
  read_data_first_half = read_data_first_half >> 8;

  read_data_second_half = read_data & 0x00FF;
  read_data_second_half = read_data_second_half << 8;

  read_data = read_data_first_half | read_data_second_half;

  temperatureCelsius = ((read_data*175.72)/65536.0) - 46.85;
  ble_data->temperatureCelsius = temperatureCelsius;
  displayPrintf( DISPLAY_ROW_TEMPVALUE, "Temp = %.0f C", temperatureCelsius );
  temperatureIndicate((uint32_t)temperatureCelsius);

} // convertReadTempToC()

//Abijith's edit:
//Do it in Smoke.c
//Add AnalogToPPM
//Do mathematical calculation
//Call function SmokeIndicate to send values to local GATT Server
