#include <Arduino_FreeRTOS.h>
#include "queue.h"

QueueHandle_t que_hand, que_hand2;
int timer1_cnt;


void setup(){

  Serial.begin(9600);
  
  xTaskCreate(vStringPrinter, "vStringPrinter", 128, NULL, 1, NULL);
  xTaskCreate(vIntegerSender, "vIntegerSender", 128, NULL, 1, NULL);

  que_hand = xQueueCreate(5, sizeof(char *));
  que_hand2 = xQueueCreate(20, sizeof(uint32_t));

  InterruptInit();  
}


void vIntegerSender(void *pvParameters){
  static uint32_t sendNumber = 0;
  TickType_t xLastExecutionTime;
  const TickType_t xDelay200ms = pdMS_TO_TICKS(200);

  
  
  while(1){
    xLastExecutionTime = xTaskGetTickCount();
    for(int i =0; i<5; i++){
      xQueueSendToBack(que_hand2, &sendNumber, pdFALSE);  
      sendNumber = (sendNumber+1)%5;
    }
      
    vTaskDelayUntil(&xLastExecutionTime, xDelay200ms);
  }
}

void vStringPrinter(void *pvParameters){
  char *pcString;
  while(1){
    xQueueReceive(que_hand, &pcString, portMAX_DELAY);
    Serial.println(pcString);   
  }
}


ISR(TIMER1_OVF_vect){
  TCNT1 = timer1_cnt;
  uint32_t receivedNumber;

  static const char *pcString[]={
    "Hello\r\n",
    "Hi\r\n",
    "I\r\n",
    "am\r\n",
    "here\r\n"
  };
  xQueueReceiveFromISR(que_hand2, &receivedNumber, pdFALSE);
  xQueueSendToBackFromISR(que_hand, &pcString[receivedNumber], pdFALSE);
}


void loop(){
  
}


void InterruptInit(){
  noInterrupts();
  // Clear registers
  TCCR1A = 0;
  TCCR1B = 0;

  timer1_cnt = 64999;
  TCNT1 = timer1_cnt;
  
  // Prescaler 1024
  TCCR1B |= (1 << CS12) | (1 << CS10);
  TIMSK1 |= (1 << TOIE1);
  interrupts();
}
