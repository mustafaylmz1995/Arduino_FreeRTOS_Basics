#include <Arduino_FreeRTOS.h>

#define RED     6
#define YELLOW  7
#define GREEN   8


typedef int TaskProfiler;
TaskProfiler RedLEDProfiler;
TaskProfiler YellowLEDProfiler;
TaskProfiler GreenLEDProfiler;


void setup(){

  Serial.begin(9600);
  
  /*create tasks*/
  xTaskCreate(redLedControllerTask, "RED LED Task", 128, NULL, 1, NULL);
  //xTaskCreate(yellowLedControllerTask, "YELLOW LED Task", 128, NULL, 1, NULL);  
  xTaskCreate(greenLedControllerTask, "GREEN LED Task", 128, NULL, 1, NULL);
}

void redLedControllerTask(void *pvParameters){
  pinMode(RED, OUTPUT);
  while(1){
    RedLEDProfiler++;
    Serial.print("RedLEDProfiler\t\t :");
    Serial.println(RedLEDProfiler);
    //digitalWrite(RED, digitalRead(RED)^1);
    delay(250);
  }
}

void yellowLedControllerTask(void *pvParameters){
  pinMode(YELLOW, OUTPUT);
  while(1){
    YellowLEDProfiler++;
    Serial.print("YellowLEDProfiler\t :");
    Serial.println(YellowLEDProfiler);
    //digitalWrite(YELLOW, digitalRead(YELLOW)^1);
    delay(250);
  }
}

void greenLedControllerTask(void *pvParameters){
  pinMode(GREEN, OUTPUT);
  while(1){
    GreenLEDProfiler++;
    Serial.print("GreenLEDProfiler\t :");
    Serial.println(GreenLEDProfiler);
    //digitalWrite(GREEN, digitalRead(GREEN)^1);
    delay(250);
  }
}


void loop(){

}
