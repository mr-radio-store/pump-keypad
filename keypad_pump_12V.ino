/*
Control pumping with keypad

Wire connection
    Keypad 1x4:
        1 Row (connected together), 4 Columns (separate buttons).
    Motor:
        Use a motor driver (like L298N, L9110, or a simple N-MOSFET) 
        to control the motor safely from Arduino PWM pin.
    Connections:
        4 Arduino pins → 4 keypad columns
        Motor control pin → PWM-capable Arduino pin (e.g., D9 on Uno)

How It Works
    Button 0 pressed → Motor OFF (speed = 0)
    Button 1 pressed → Motor ~33% speed
    Button 2 pressed → Motor ~66% speed
    Button 3 pressed → Motor full speed (100%)
Each button press directly changes the PWM output to the motor.
*/


// 1x4 Keypad pins
const int buttonPins[4] = {2, 3, 4, 5};  // Connect columns to Arduino pins

// Motor control pin
const int motorPin = 9; // Must be a PWM capable pin

// Motor speeds
int motorSpeeds[4] = {0, 85, 170, 255}; // 0%, ~33%, ~66%, 100%

void setup() {
  // Setup button pins
  for (int i = 0; i < 4; i++) {
    pinMode(buttonPins[i], INPUT_PULLUP); // Use internal pull-up resistors
  }
  
  // Setup motor control pin
  pinMode(motorPin, OUTPUT);

  // Start motor OFF
  analogWrite(motorPin, 0);

  Serial.begin(9600);
}

void loop() {
  // Check buttons
  for (int i = 0; i < 4; i++) {
    if (digitalRead(buttonPins[i]) == LOW) {  // Button pressed (active low)
      analogWrite(motorPin, motorSpeeds[i]);
      Serial.print("Button ");
      Serial.print(i);
      Serial.print(" pressed. Motor speed set to ");
      Serial.println(motorSpeeds[i]);
      delay(300); // Debounce delay
    }
  }
}
