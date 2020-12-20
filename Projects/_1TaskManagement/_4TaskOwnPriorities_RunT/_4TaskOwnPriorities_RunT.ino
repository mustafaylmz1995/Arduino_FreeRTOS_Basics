#include <Arduino_FreeRTOS.h>

#define RED     6
#define YELLOW  7
#define GREEN   8

typedef int TaskProfiler;

TaskProfiler redLEDProfiler;
TaskProfiler yellowLEDProfiler;
TaskProfiler greenLEDProfiler;

TaskHandle_t red_Handle, yellow_Handle, green_Handle;


const uint8_t *redLed    = (uint8_t *)RED;
const uint8_t *yellowLed = (uint8_t *)YELLOW;
const uint8_t *greenLed  = (uint8_t *)GREEN;


void setup(){
  xTaskCreate(LEDControllerTask, "RED LED Task", 100, (void *)redLed, 2, &red_Handle);
  xTaskCreate(LEDControllerTask, "YELLOW LED Task", 100, (void *)yellowLed, 2, &yellow_Handle);
  xTaskCreate(LEDControllerTask, "GREEN LED Task", 100, (void *)greenLed, 2, &green_Handle);

}

void LEDControllerTask(void *pvParameter){
  
  static uint8_t c = 0, b=0, a=0;
  c+=1;
  b+=2;
  a+=3;
  pinMode((uint8_t)pvParameter, OUTPUT);
  while(1){
    digitalWrite((uint8_t)pvParameter,digitalRead((uint8_t)pvParameter)^1);
    vTaskPrioritySet(red_Handle, (c++)%4);
    vTaskPrioritySet(yellow_Handle, (b++)%4);
    vTaskPrioritySet(green_Handle, (a++)%4);
    delay(150);
  }
}

void loop(){
  
}
