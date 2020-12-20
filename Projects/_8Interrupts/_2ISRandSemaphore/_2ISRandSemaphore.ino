#include <Arduino_FreeRTOS.h>
#include <semphr.h>

#define GREEN   8
#define YELLOW  7
#define RED     6

const uint16_t *LED_ARR[]   = {
  (uint16_t *)GREEN,
  (uint16_t *)YELLOW,
  (uint16_t *)RED
};


SemaphoreHandle_t intrSemt;

int timer1_cnt;

void setup(){
  
  Serial.begin(230400);
  
  pinMode(GREEN, OUTPUT);
  pinMode(YELLOW, OUTPUT);
  pinMode(RED, OUTPUT);

  xTaskCreate(onTask, "GREEN LED on Task", 96, (void *)LED_ARR[0], 1, NULL);
  xTaskCreate(onTask, "YELLOW LED on Task", 96, (void *)LED_ARR[1], 1, NULL);
  xTaskCreate(onTask, "RED LED on Task", 96, (void *)LED_ARR[2], 1, NULL);

  xTaskCreate(offTask, "GREEN LED off Task", 96, (void *)LED_ARR[0], 1, NULL);
  xTaskCreate(offTask, "YELLOW LED off Task", 96, (void *)LED_ARR[1], 1, NULL);
  xTaskCreate(offTask, "RED LED off Task", 96, (void *)LED_ARR[2], 1, NULL);

  intrSemt = xSemaphoreCreateBinary();
  if(NULL != intrSemt){
    InterruptInit();
  }
}

void onTask(void *pvParameters){
  while(1){    
    if( pdPASS == xSemaphoreTake(intrSemt, portMAX_DELAY)){
      vTaskDelay(1);
      digitalWrite((uint16_t)pvParameters, HIGH);
      Serial.print((uint16_t)pvParameters);
      Serial.println(" is Opened!");
            
    }
  }
}

void offTask(void *pvParameters){

  while(1){ 
    if( pdPASS == xSemaphoreTake(intrSemt, portMAX_DELAY)){
      vTaskDelay(1);
      digitalWrite((uint16_t)pvParameters, LOW);
      Serial.print((uint16_t)pvParameters);
      Serial.println(" is Closed!");
      
    }
  }
}

ISR(TIMER1_OVF_vect){
  TCNT1 = timer1_cnt;
  xSemaphoreGiveFromISR(intrSemt, pdTRUE);
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
