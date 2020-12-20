
const byte LED = 13;
const byte INT = 2;

volatile byte state = LOW;


void setup(){

  pinMode(LED, OUTPUT);
  pinMode(INT, INPUT_PULLUP);

  attachInterrupt(digitalPinToInterrupt(INT), glow, CHANGE);

  digitalWrite(LED, HIGH);
  delay(2000);
  digitalWrite(LED, LOW);
  
  
}


void loop(){
  digitalWrite(LED, state);
}


void glow(){
  state = !state;
}
