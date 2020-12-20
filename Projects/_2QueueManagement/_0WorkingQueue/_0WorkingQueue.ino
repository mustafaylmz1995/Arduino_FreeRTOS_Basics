#include <Arduino_FreeRTOS.h>
#include "queue.h"

QueueHandle_t yearQueue;


void setup(){
  Serial.begin(9600);
  yearQueue = xQueueCreate(5, sizeof(int32_t));

  xTaskCreate(vSenderTask, "Sender Task", 100, NULL, 1, NULL);
  xTaskCreate(vReceiverTask, "Receiver Task", 100, NULL, 1, NULL);

}

void vSenderTask(void* pvParameters){

  BaseType_t qStatus;
  int32_t val2Send = 1999;
  
  while(1){
    qStatus = xQueueSend(yearQueue, &val2Send, 0);  
  }
}

void vReceiverTask(void *pcParameters){

  int32_t valReceived;
  const TickType_t xTicksToWait = pdMS_TO_TICKS(10);

  BaseType_t qStatus;
  
  while(1){
    xQueueReceive(yearQueue, &valReceived, xTicksToWait);
    Serial.print("Received Value: ");
    Serial.println(valReceived);
    vTaskDelay(5);
  }
}


void loop(){
  
}
