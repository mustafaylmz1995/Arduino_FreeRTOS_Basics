
#include <Arduino_FreeRTOS.h>
#include "queue.h"


typedef int TaskProfiler;
TaskProfiler  senderTaskProfiler;
TaskProfiler  receiverTaskProfiler;

typedef enum{
  eSender1,
  eSender2,
}DataSource_t;

typedef struct{
  uint8_t ucValue;
  DataSource_t eDataSource;
}Data_t;

static const Data_t xStructToSend[2]={
  {100, eSender1},
  {50, eSender2}
};

QueueHandle_t xQueue;


void setup(){
  Serial.begin(9600);
  
  xQueue = xQueueCreate(3, sizeof(Data_t));

  xTaskCreate(vSenderTask, "Sender Task1", 128, &xStructToSend[0], 2, NULL);
  xTaskCreate(vSenderTask, "Sender Task2", 128, &xStructToSend[1], 2, NULL);

  xTaskCreate(vReceiverTask, "Receiver Task", 128, NULL, 1, NULL);
    
} 

void vSenderTask(void *pvParameters){
  BaseType_t xStatus;
  const TickType_t xTicksToWait = pdMS_TO_TICKS(100);
  
  while(1){
    xStatus = xQueueSend(xQueue, pvParameters, xTicksToWait);

    if(xStatus != pdPASS){
      Serial.print("Could not send to the queue! ");
    }
    
  }
  
}

void vReceiverTask(void *pvParameters){
  BaseType_t xStatus;
  Data_t xReceivedStructure;
  
  while(1){
    xStatus = xQueueReceive(xQueue, &xReceivedStructure, 0);

    if(xStatus == pdPASS){
      if(xReceivedStructure.eDataSource == eSender1){
        Serial.print("This is from Sender 1!");
        Serial.println(xReceivedStructure.ucValue);
      }else{
        Serial.print("This is from Sender 2!");
        Serial.println(xReceivedStructure.ucValue);  
      }

    }else{
      Serial.println("Could not send to the queue! ");      
    }
    
  }
  
}

void loop(){


}
