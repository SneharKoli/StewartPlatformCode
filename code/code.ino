/* Stewart Platform
 * Actuation of the 6DOF platform in open loop configuration using a
 * joystick (potentiometer).
 * 
 * Original Code Used: "MultiStepper" example included within the
 * AccelStepper library.
 * 
 * Contributions made by
 * - Navin Sridhar
 * - Snehar Koli
 * - Shivam Pandit
*/

/* Include library files.
 *  
 * Multistepper.h has to be included in order
 * to be able to use multiple stepper motors
 * simultaneously.
 * 
*/
#include <AccelStepper.h>
#include <MultiStepper.h>


/* Declare stepper objects with the class AccelStepper.
 * Use DRIVER if the motor is connected using a stepper motor driver.
 * If driver is connected but FULLWIRE is declared, direction
 * control won't be achieved at all!
 * 
 * First number corresponds to step pin on the driver.
 * Second number corresponds to the direction pin.
*/
AccelStepper stepper1(AccelStepper::DRIVER, 2, 3);
AccelStepper stepper2(AccelStepper::DRIVER, 4, 5);
AccelStepper stepper3(AccelStepper::DRIVER, 6, 7);
AccelStepper stepper4(AccelStepper::DRIVER, 8, 9);
AccelStepper stepper5(AccelStepper::DRIVER, 10, 11);
AccelStepper stepper6(AccelStepper::DRIVER, 22, 23);

MultiStepper steppers;

void setup() {
  Serial.begin(9600);

  stepper1.setMaxSpeed(1000);
  stepper2.setMaxSpeed(1000);
  stepper3.setMaxSpeed(1000);
  stepper4.setMaxSpeed(1000);
  stepper5.setMaxSpeed(1000);
  stepper6.setMaxSpeed(1000);
  
  // Add the six stepper motors to the set of managed steppers.
  steppers.addStepper(stepper1);
  steppers.addStepper(stepper2);
  steppers.addStepper(stepper3);
  steppers.addStepper(stepper4);
  steppers.addStepper(stepper5);
  steppers.addStepper(stepper6);
}

void loop() {
  // Array containing position of each stepper motor
  long positions[6];

  // Reading the joystick (potentiometer) value
  int potValue = analogRead(A5);
  for (int i = 0; i < 6; i++) {
    positions[i] = potValue;
  }
  
  /* Set the target positions of all managed steppers
   * according to a coordinate array. New speeds will be
   * computed for each stepper so they will all arrive at
   * their respective targets at very close to the same time.
   */
  steppers.moveTo(positions);

  /* Runs all managed steppers until they acheived their target position.
   * CAUTION: BLOCKS FURTHER CODE FROM GETTING EXECUTED UNTIL ALL
   * STEPPER MOTORS ARE POSITIONED COMPLETELY.
   */
  steppers.runSpeedToPosition();
  delay(500);
}
