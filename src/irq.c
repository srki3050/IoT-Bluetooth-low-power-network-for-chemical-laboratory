/***************************************************************************//**
 * @file
 * @brief Interrupt logic.
 * @resources https://siliconlabs.github.io/Gecko_SDK_Doc/efr32bg1/html/em__timer_8h.html
 *
 * Date:        09-09-2021
 * Author:      Abijith Ananda Krishnan
 * Description: This code was created by me call the interrupts based on the
 * source of interrupts as a flag
 *
 ******************************************************************************/

#include "irq.h"

uint32_t rollOverCount = 0;
bool button_pressed = false;
void LETIMER0_IRQHandler (void)
{
  //high speed event logger
  //struct temperature_event *temperatureData;

  //static event_index = 0;
  //static struct temperature_event temperature_event_array[32];

  //This is how you service the interrupt
  // 1. determine source of IRQ
  uint32_t interruptSource = LETIMER_IntGetEnabled(LETIMER0);

  // 2. clear source of IRQ set in step 3
  LETIMER_IntClear(LETIMER0,interruptSource); //clears interrupts
  //actually UF or COMP1

  //check if we need to call  NVIC_EnableIRQ()

  // 3. calling the schedulerSetReadTemperatureEvent function on an LETIMER0 underflow event
  if(interruptSource & LETIMER_IF_UF){ //will result in true if U
      //letimerCounter
      schedulerSetUFEvent();
      //LOG_INFO(loggerGetTimestamp());
      //rollOverCount += 1;
      //interruptSource = LETIMER_IntGetEnabled(LETIMER0);
      //do ADC interrupt
      ADC_IntEnable(ADC0, ADC_IEN_SINGLE);
      //ADC_Start(ADC0, adcStartSingle);
  }
  /*if(interruptSource & LETIMER_IF_COMP1){ //will result in true if U
        //letimerCounter
        schedulerSetCOMP1Event();
        //LOG_INFO(loggerGetTimestamp());
        //rollOverCount += 1;
        LETIMER_IntDisable(LETIMER0,LETIMER_IF_COMP1);
        //interruptSource = LETIMER_IntGetEnabled(LETIMER0);
  }*/

  //Abijith's edit:
  // Start next ADC conversion
  //ADC_Start(ADC0, adcStartSingle);

}

uint32_t letimerMilliseconds(){
  uint32_t letimerCounter = LETIMER_CounterGet(LETIMER0);
  return rollOverCount*3000 + (3000-letimerCounter);
}

/*void I2C0_IRQHandler(void){
  I2C_TransferReturn_TypeDef transferStatus;
  transferStatus = I2C_Transfer(I2C0);

  if (transferStatus == i2cTransferDone) {
      schedulerSetI2CEvent();
      NVIC_DisableIRQ(I2C0_IRQn);
      //sl_power_manager_remove_em_requirement(SL_POWER_MANAGER_EM1);
    }

    if (transferStatus < i2cTransferDone) {
     LOG_ERROR ("I2C_TransferInit() write error = %d", transferStatus);
    }
}*/

void GPIO_EVEN_IRQHandler(){
  if(GPIO_IntGet() & 1<<PB0_pin){
      schedulerSetButtonPB0ClickEvent();
      GPIO_IntClear(1<<PB0_pin);
  }
}

void GPIO_ODD_IRQHandler(){
  if(GPIO_IntGet() & 1<<PB1_pin){
      schedulerSetButtonPB1ClickEvent();
      GPIO_IntClear(1<<PB1_pin);
  }
}

//Abijith's edit:
/**************************************************************************//**
 * @brief ADC Handler
 *****************************************************************************/
void ADC0_IRQHandler(void)
{

  uint32_t interruptSource = ADC_IntGetEnabled(ADC0);

  ADC_IntClear(ADC0,interruptSource); //clears interrupts

  if(interruptSource & ADC_IF_SINGLE){ //will result in true if U
      schedulerSetADCEvent();
  }

}
