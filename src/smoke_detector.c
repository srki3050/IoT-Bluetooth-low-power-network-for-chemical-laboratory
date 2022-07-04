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

#define INCLUDE_LOG_DEBUG 1
#include "src/log.h"
#include "smoke_detector.h"
#include "ble.h"

volatile uint32_t sample;
volatile float ppmValues;
void takeSmokeDetectorReading(void){
  // Get ADC result
  sample = ADC_DataSingleGet(ADC0);
  ble_data_struct_t *ble_data = getBleDataPtr();
  // Calculate input voltage in ppm
  ppmValues = ((sample * 9700) + 1228800) / 4096;
  ble_data->MQ9bvalues = ppmValues;
  printf("%f",ppmValues);
  /*
    4096(x2) - 10000(y2)
    0(x1)   - 300(y1)

    y-300     10000 - 300
   ------- =  --------------
    x-0         4096 - 0


    4096y - 1228800 = 9700x

    y = 9700x + 1228800
       -----------------
          4096
  */
  schedulerSetSmokeSensorOffEvent();
}
