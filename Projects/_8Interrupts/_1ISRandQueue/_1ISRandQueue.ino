#include <Arduino_FreeRTOS.h>
#include "queue.h"

QueueHandle_t que_hand;
int timer1_cnt;


void setup(){

  Serial.begin(9600);
  
  xTaskCreate(vStringPrinter, "vStringPrinter", 128, NULL, 1, NULL);
  que_hand = xQueueCreate(5, sizeof(char *));

  InterruptInit();  
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
  static int i =0;
  i = (i+1)%5;

  static const char *pcString[]={
    "Hello\r\n",
    "Hi\r\n",
    "I\r\n",
    "am\r\n",
    "here\r\n"
  };

  xQueueSendToBackFromISR(que_hand, &pcString[i], pdFALSE);
}


void loop(){
  
}


void InterruptInit(){
  noInterrupts();
  TCCR1A = 0;
  TCCR1B = 0;
  
  timer1_cnt = 32768;
  TCNT1 = timer1_cnt;

  TCCR1B |= (1 << CS12);
  TIMSK1 |= (1 << TOIE1);

  interrupts();
}
