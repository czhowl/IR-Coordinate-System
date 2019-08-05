#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

// called this way, it uses the default address 0x40
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

void setup() {
  Serial.begin(9600);
  Serial.println("GPIO test!");
  pinMode(6, OUTPUT);
  digitalWrite(6, LOW);
  pwm.begin();
  pwm.setPWMFreq(40);  // 40Hz
  Wire.setClock(400000);
}

void loop() {
  // ==================================================================== all 0
  for (uint8_t pwmnum = 0; pwmnum < 16; pwmnum++) {
    pwm.setPWM(pwmnum, 0, 4096);
  }
  delay(100);  // t = 100ms
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
