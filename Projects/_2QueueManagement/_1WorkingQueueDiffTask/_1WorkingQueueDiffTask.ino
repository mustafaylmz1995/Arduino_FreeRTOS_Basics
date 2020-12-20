
#include <Arduino_FreeRTOS.h>
#include "queue.h"


#define RED     6
#define YELLOW  7
#define GREEN   8

typedef int TaskProfiler;
TaskProfiler  senderTaskProfiler;
TaskProfiler  receiverTaskProfiler;

QueueHandle_t yearQueue;


void setup(){
  Serial.begin(9600);
  pinMode(RED, OUTPUT);
  yearQueue = xQueueCreate(5, sizeof(int32_t));
    
  xTaskCreate(vSenderTask, "Sender Task 1", 128, (void *)2020, 1, NULL);
  xTaskCreate(vSenderTask, "Sender Task 2", 128, (void *)1999, 1, NULL);

  xTaskCreate(vReceiverTask, "Receiver Task", 128, NULL, 2, NULL);
} 


void vSenderTask(void *pvParameters){

  BaseType_t qStatus;
  int32_t value2Send;

  value2Send = (int32_t)pvParameters;
  
  while(1){
    delay(50);
    qStatus = xQueueSend(yearQueue, &value2Send, 0);

    if(qStatus != pdPASS){
      Serial.println("Could not send to the queue!");
    }else{
      Serial.println("Send to the queue!");
    }
    digitalWrite(RED, HIGH);
  }
}

void vReceiverTask(void *pvParameters){
  BaseType_t qStatus;
  int32_t valueReceived;

  const TickType_t xTicksToWait = pdMS_TO_TICKS(100);

  while(1){
    delay(50);
    qStatus = xQueueReceive(yearQueue, &valueReceived, xTicksToWait);  

    if(qStatus == pdPASS){
      Serial.print("Data received successfully!");
      Serial.println(valueReceived);
    }else{
      Serial.print("Could not receive from queue!");
    }
    digitalWrite(RED, LOW);  
  }
}

void loop(){

  
}
