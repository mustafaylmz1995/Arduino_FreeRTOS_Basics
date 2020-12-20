#include <Arduino_FreeRTOS.h>
#include "event_groups.h"

#define   RED     6
#define   YELLOW  7
#define   GREEN   8


EventGroupHandle_t  xEventGroup;
#define TASK1_BIT (1UL << 0UL)
#define TASK2_BIT (1UL << 1UL)

void setup(){
  Serial.begin(9600);
  pinMode(RED, OUTPUT);
//  pinMode(YELLOW, OUTPUT);
  pinMode(GREEN, OUTPUT);

  xEventGroup = xEventGroupCreate();

  xTaskCreate(EventBitSettingTask, "Bit Setter", 128, NULL, 1, NULL);
  xTaskCreate(EventBitReadingTask, "Bit Reader", 128, NULL, 1, NULL);
  
}

void EventBitSettingTask(void *pvParameters){
  const TickType_t xDelay200ms = pdMS_TO_TICKS(200);

  while(1){
    xEventGroupSetBits(xEventGroup, TASK1_BIT);
    
    xEventGroupSetBits(xEventGroup, TASK2_BIT);
    vTaskDelay(xDelay200ms);

  }
    
}


void EventBitReadingTask(void *pvParameters){
  
  const EventBits_t xBitsToWaitFor = (TASK1_BIT | TASK2_BIT);
  EventBits_t xEventGroupValue;
  
  while(1){
   xEventGroupValue = xEventGroupWaitBits(xEventGroup, 
                                           xBitsToWaitFor,
                                           pdTRUE,
                                           pdTRUE,
                                           portMAX_DELAY
                                           );

    if((xEventGroupValue & TASK1_BIT) != 0){
      digitalWrite(RED, digitalRead(RED)^1);                                           
    }
    
    if((xEventGroupValue & TASK2_BIT) != 0){
      digitalWrite(GREEN, digitalRead(GREEN)^1);                                           
    }
  }
}


void loop(){
  
}
