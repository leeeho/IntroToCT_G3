#include <Servo.h>

Servo myServo;
Servo myservo2;

const int servoPin = 6;
const int tactileSwitchPin = 7; // Assuming the tactile switch is connected to pin 7

int clockwiseAngle = 0; // Adjust as needed
int stopAngle = 90;     // Adjust as needed
int moveDuration;

int val;
int prevVal = 0; // Variable to store the previous value of val

void setup()
{
  Serial.begin(9600);

  myServo.attach(servoPin);
  myservo2.attach(9);

  pinMode(tactileSwitchPin, INPUT_PULLUP); // Set the tactile switch pin as INPUT_PULLUP
}

void loop()
{

  moveDuration = 30;

  // Check if the tactile switch is pressed
  if (digitalRead(tactileSwitchPin) == HIGH)
  {
    Serial.println("Button Pressed!");
    rotateClockwise();
  }
  else
  {
    // Check if a key is pressed
    if (Serial.available() > 0)
    {
      char key = Serial.read();

      // Perform action based on the key pressed
      if (key == 'a')
      {
        rotateClockwise();
      }
      else
      {
        stopServo();
      }
    }
  }

  servo2Control();
}

void rotateClockwise()
{
  myServo.write(clockwiseAngle);
  // delay(moveDuration);
  delay(30);
  stopServo();
}

void stopServo()
{
  myServo.write(stopAngle);
}

void servo2Control()
{
val = analogRead(A0); // reads the value of the potentiometer (value between 0 and 1023)
  val = map(val, 5, 1023, 120, 50); // scale it for use with the servo (value between 0 and 180)
  val = round(val / 10.0) * 10;    // round to the nearest multiple of ten
  Serial.println("Camera motor distance" + val);

  myservo2.write(val); // Set the servo position according to the scaled value

  delay(15);
}
