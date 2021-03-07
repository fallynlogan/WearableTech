#include <Stepper.h>

#define PIN_GATE_IN 2
#define IRQ_GATE_IN  0
#define PIN_LED_OUT 13
#define PIN_ANALOG_IN A0
#define in1Pin 12
#define in2Pin 11
#define in3Pin 10
#define in4Pin 9

const int stepVal = 3500;
bool hasSpun = false;

Stepper motor(512, in1Pin, in2Pin, in3Pin, in4Pin);  

// soundISR()
// This function is installed as an interrupt service routine for the pin
// change interrupt.  When digital input 2 changes state, this routine
// is called.
// It queries the state of that pin, and sets the onboard LED to reflect that 
// pin's state.
void soundISR()
{
  int pin_val;

  pin_val = digitalRead(PIN_GATE_IN);
  digitalWrite(PIN_LED_OUT, pin_val);   
}

void setup()
{
  pinMode(in1Pin, OUTPUT);
  pinMode(in2Pin, OUTPUT);
  pinMode(in3Pin, OUTPUT);
  pinMode(in4Pin, OUTPUT);
  pinMode(PIN_LED_OUT, OUTPUT);
  pinMode(PIN_GATE_IN, INPUT);
  attachInterrupt(IRQ_GATE_IN, soundISR, CHANGE);

  while (!Serial);
  
  Serial.begin(9600);
  motor.step(stepVal);
  motor.setSpeed(20);
}

void loop()
{
  int value;

  // Check the envelope input
  value = analogRead(PIN_ANALOG_IN);

  Serial.println(value);
  
  if ((value > 20) && (hasSpun == false))
  {
    motor.step(-stepVal);
    hasSpun = true;  
  }

  if ((value < 20) && (hasSpun == true))
  {
    motor.step(stepVal);
    hasSpun = false;
  }
  
  delay(1000);
}
