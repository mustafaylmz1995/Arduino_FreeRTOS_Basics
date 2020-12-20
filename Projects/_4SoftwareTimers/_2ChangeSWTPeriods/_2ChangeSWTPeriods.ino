#include <Arduino_FreeRTOS.h>
#include <timers.h>

#define RED     6
#define YELLOW  7
#define GREEN   8


#define RED_TIMER_PERIOD          (pdMS_TO_TICKS(70))
#define GREEN_TIMER_PERIOD        (pdMS_TO_TICKS(170))
#define RED_TIMER_PERIOD2         (pdMS_TO_TICKS(310))
#define GREEN_TIMER_PERIOD2       (pdMS_TO_TICKS(430))


TimerHandle_t xGreenTimer, xRedTimer;
uint32_t GreenExecutionCount, RedExecutionCount;


void setup(){
  Serial.begin(9600);
  pinMode(RED, OUTPUT);
  pinMode(GREEN, OUTPUT);
  
  BaseType_t xGreenTimerStarted, xRedTimerStarted;
  
  xGreenTimer = xTimerCreate("Green Timer",
                              GREEN_TIMER_PERIOD, 
                              pdTRUE,
                              0,  //timerID
                              prvTimerCallback
                              ); 
                              
  xRedTimer = xTimerCreate("Red Timer",
                            RED_TIMER_PERIOD, 
                            pdTRUE,
                            0,  //timerID
                            prvTimerCallback
                            ); 

  if( (xGreenTimer != NULL) && (xRedTimer != NULL) ){

    xGreenTimerStarted = xTimerStart(xGreenTimer, 0);
    xRedTimerStarted = xTimerStart(xRedTimer, 0);

    while( (xGreenTimerStarted != pdPASS) && (xRedTimerStarted != pdPASS) ){
      //do nothing
    }
  }

}



void prvTimerCallback(TimerHandle_t xTimer){
  static TickType_t xTimeNow;
  xTimeNow = xTaskGetTickCount();

  if(xTimer == xGreenTimer){
    GreenExecutionCount++;
    Serial.print("Green Timer execution : ");
    Serial.println(xTimeNow);
    digitalWrite(GREEN, digitalRead(GREEN)^1);
    if(GreenExecutionCount == 30){
      GreenExecutionCount =0;
      if(xTimerGetPeriod(xTimer) == GREEN_TIMER_PERIOD )
        xTimerChangePeriod(xGreenTimer, GREEN_TIMER_PERIOD2, 0);
      else
        xTimerChangePeriod(xGreenTimer, GREEN_TIMER_PERIOD, 0);
    }
    
  }else{
    
    RedExecutionCount++;
    Serial.print("Red Timer execution : ");
    Serial.println(xTimeNow);
    digitalWrite(RED, digitalRead(RED)^1);
    if(RedExecutionCount == 30){
      RedExecutionCount =0;
      if(xTimerGetPeriod(xTimer) == RED_TIMER_PERIOD )
        xTimerChangePeriod(xRedTimer, RED_TIMER_PERIOD2, 0);
      else
        xTimerChangePeriod(xRedTimer, RED_TIMER_PERIOD, 0);
    }
  }

}

void loop(){

  
}
