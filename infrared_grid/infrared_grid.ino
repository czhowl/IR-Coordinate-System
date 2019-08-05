#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

// called this way, it uses the default address 0x40
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();
// you can also call it with a different address you want
//Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver(0x41);
// you can also call it with a different address and I2C interface
//Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver(&Wire, 0x40);

void setup() {
  Serial.begin(9600);
  Serial.println("GPIO test!");
  pinMode(6, OUTPUT);
  digitalWrite(6, LOW);
  pwm.begin();
  pwm.setPWMFreq(40);  // Set to whatever you like, we don't use it in this demo!

  // if you want to really speed stuff up, you can go into 'fast 400khz I2C' mode
  // some i2c devices dont like this so much so if you're sharing the bus, watch
  // out for this!
  Wire.setClock(400000);
}

void loop() {
  //  pwm.setPWM(0, 4096, 0);
  //  delay(100);
  //  pwm.setPWM(0, 0, 4096);
  //  delay(100);
  //  pwm.setPWM(0, 0, 64);
  //  delay(100);
  //  pwm.setPWM(0, 0, 256);
  //  delay(100);
  //  pwm.setPWM(0, 0, 1024);
  //  delay(100);
  // ==================================================================== all 0
  for (uint8_t pwmnum = 0; pwmnum < 16; pwmnum++) {
    pwm.setPWM(pwmnum, 0, 4096);
  }
  delay(100);
  for (uint8_t pwmnum = 0; pwmnum < 16; pwmnum++) {
    pwm.setPWM(pwmnum, 4096, 0);
  }
//  delay(1);
  // ====================================================================   X
  for (uint8_t pwmnum = 0; pwmnum < 8; pwmnum++) {
    pwm.setPWM(pwmnum, 0, (4096/8)*pwmnum);
  }
  for (uint8_t pwmnum = 8; pwmnum < 16; pwmnum++) {
    pwm.setPWM(pwmnum, 0, 4096);
  }
  delay(100);
  // ==================================================================== all 1
//  for (uint8_t pwmnum = 0; pwmnum < 16; pwmnum++) {
//    pwm.setPWM(pwmnum, 4096, 0);
//  }
//  delay(100);
  // ====================================================================   Y
  for (uint8_t pwmnum = 0; pwmnum < 8; pwmnum++) {
    pwm.setPWM(pwmnum, 0, 4096);
  }
  for (uint8_t pwmnum = 8; pwmnum < 16; pwmnum++) {
    pwm.setPWM(pwmnum, 0, (4096/8)*(16 - pwmnum));
  }
  delay(100);


}
