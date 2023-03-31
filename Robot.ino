// this is the code for our minimate, running on an arduino! this version is very bare, so a lot more comments and features will be added soon
// TODO: exploration function
// TODO: crash prevention
// TODO: use serial over Bluetooth not USB

const int motor1Forward = 9, motor1Backward = 8, motor1Pwm = 3;
const int motor2Forward = 7, motor2Backward = 6, motor2Pwm = 5;
const int STBY = 2;
int speed = 100;

char action;
int rotunit = 10, movunit = 10;

void walk(char dir, int amt, int speed=150) {
  switch (dir) {
    case 'f':
      move(1,speed,'f');
      move(2,speed,'f');
      delay(amt*movunit);
      stop();
      break;
    case 'b':
      move(1,speed,'b');
      move(2,speed,'b');
      delay(amt*movunit);
      stop();
      break;
    case 'l':
      move(1,speed,'b');
      move(2,speed,'f');
      delay(amt*rotunit);
      stop();
      break;
    case 'r':
      move(1,speed,'f');
      move(2,speed,'b');
      delay(amt*rotunit);
      stop();
      break;
  }
}

void snowflake(int length, int levels) {
  if (levels==0) {
    walk('f',length);
  } else {
    length /= 3.0;
    snowflake(length, levels-1);
    walk('l',60);
    snowflake(length, levels-1);
    walk('r',120);
    snowflake(length, levels-1);
    walk('l',60);
    snowflake(length, levels-1);
  }
}

void setup() {
  pinMode(motor1Forward, OUTPUT);
  pinMode(motor1Backward, OUTPUT);
  pinMode(motor1Pwm, OUTPUT);
  pinMode(motor2Forward, OUTPUT);
  pinMode(motor2Backward, OUTPUT);
  pinMode(motor2Pwm, OUTPUT);
  pinMode(STBY, OUTPUT);
  Serial.begin(115200);
}

void loop() {
  if (Serial.available() > 0) {
    action = Serial.read();
    Serial.write(action);
    switch (action) {
      case 'd':
        for (int i=0;i<=3;i++) {
          snowflake(300,4);
          walk('r',120);
        }
        break;
      case 's':
        int randir[] = {'l','r'};
        walk(randir[random(0,2)],random(1000,5000),random(150,240));
        break;
      case 'j':
        break;
    }
  }
}

// this is a function to move a specific motor at a specific speed in a specific direction
void move(int motor, int speed, char direction){
  /*
  Paramaters:
    motor (integer) - which motor to turn:
      1 will move the first motor (motor1) (walk 'l',motor).
      2 will move the second motor (motor2) (right motor).
    speed (integer) - the speed, the pwm:
      0 is stop.
      255 is the fastest.
      NOTE: in my case, I needed at least 60 speed (pwm) to turn the motors
    direction (character) - the direction to turn:
      'f' is forward (clockwise)
      'b' is backward (anticlockwise)
      NOTE: if some other character is given for direction, it will default to moving forward.
  NOTE: you can also have one motor going forward and another going backward to turn around.
  */
  boolean motorPinOneState;
  boolean motorPinTwoState;
  digitalWrite(STBY, HIGH);
  switch (direction) { // which pin needs to be HIGH and which one LOW to turn clockwise or anticlockwise
    case 'f':
      motorPinOneState = HIGH;
      motorPinTwoState = LOW;
      break;
    case 'b':
      motorPinOneState = LOW;
      motorPinTwoState = HIGH;
      break;
    default:
      motorPinOneState = HIGH;
      motorPinTwoState = LOW;
    break;
  }
  switch (motor) { // moves the required motor
    case 1:
      digitalWrite(motor1Forward, motorPinOneState);
      digitalWrite(motor1Backward, motorPinTwoState);
      analogWrite(motor1Pwm, speed);
      break;
    case 2:
      digitalWrite(motor2Forward, motorPinOneState);
      digitalWrite(motor2Backward, motorPinTwoState);
      analogWrite(motor2Pwm, speed);
      break;
  }
}

// this is a function to stop all the motors
void stop() {
  digitalWrite(STBY, LOW); 
}