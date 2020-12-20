/*
!!!Bu testi gerçekleştirdikten sonra, scheduler yapısını default hale geri getirmezseniz 
daha önceden çalıştırdığımız kodların çalışmadığını görürsünüz.

Adımlar
FreeRTOS kütüphanesini bulunduğu klasöre giriyoruz
FreeRTOSConfig.h dosyasını açıyoruz
configUSE_PREEMPTION değerini 0 ile değiştiriyoruz

taskların arasında bir öncelik sıralaması yapılmıyorsa (aynı öncelikteler)
ve preemption kapatılmışsa
İlk task ilk yaratıldığı için sonsuza dek koşar
yoksa önceliği yüksek olan sonsuza dek koşar


*/

#include <Arduino_FreeRTOS.h>

#define RED       6
#define YELLOW    7
#define GREEN     8


void setup(){

  pinMode(RED, OUTPUT);
  pinMode(YELLOW, OUTPUT);
  pinMode(GREEN, OUTPUT);

  xTaskCreate(greenBlink, "greenBlink", 96, NULL, 1, NULL);
  xTaskCreate(yellowBlink, "yellowBlink", 96, NULL, 1, NULL);
  xTaskCreate(redBlink, "redBlink", 96, NULL, 1, NULL);
  
}

void greenBlink(void *pvParameters){
  while(1){
    digitalWrite(GREEN, digitalRead(GREEN)^1);
    //vTaskDelay(pdMS_TO_TICKS(1));
  }
}

void yellowBlink(void *pvParameters){
  while(1){
    digitalWrite(YELLOW, digitalRead(YELLOW)^1);
    //vTaskDelay(pdMS_TO_TICKS(1));
  }
}

void redBlink(void *pvParameters){
  while(1){
    digitalWrite(RED, digitalRead(RED)^1);
    //vTaskDelay(pdMS_TO_TICKS(1));
  }
}

void loop(){
  
}
