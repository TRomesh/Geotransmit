#include <SPI.h>
int in1 = 12;


//the following are all ~PWM capable ports 
int enable1 = 11;
int rc_channel4 = 3;


void setup() {
  pinMode(rc_channel4, INPUT);
 
  pinMode(in1, OUTPUT);
;
  pinMode(enable1, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  
  int pwm = 0;

  int rc4 = pulseIn(rc_channel4, HIGH, 25000);
 
  Serial.print(" raw channel4: ");
  Serial.print(rc4);
  
  if(rc4<1070){
      Serial.println(" no signal");
      digitalWrite(in1, LOW);
      
      analogWrite(enable1, 0);
  }
  else if(rc4 > 1070){ //right stick
      pwm = map(rc4, 1070, 2000, 0, 255); //map our speed to 0-255 range
      digitalWrite(in1, LOW);
      analogWrite(enable1, pwm);
      Serial.print(" mptor speed: ");
      Serial.println(pwm);
  }
  else if(rc4 > 1180){
      pwm = map(rc4, 1350, 2000, 0, 255); //map our speed to 0-255 range
      digitalWrite(in1, LOW);
      analogWrite(enable1, pwm);
      Serial.print(" motor speed: ");
      Serial.println(pwm);
  }
  else if(rc4 > 1350){
      pwm = map(rc4, 1480, 2000, 0, 255); //map our speed to 0-255 range
      digitalWrite(in1, LOW);
      analogWrite(enable1, pwm);
      Serial.print(" motor speed: ");
      Serial.println(pwm);
      Serial.print("stick centered");
  }   
  else if(rc4 > 1480){
      pwm = map(rc4, 1660, 2000, 0, 255); //map our speed to 0-255 range
      digitalWrite(in1, LOW);
      analogWrite(enable1, pwm);
      Serial.print(" motor speed ");
      Serial.println(pwm);
  }

   else if(rc4 > 1660){
      pwm = map(rc4, 1805, 2000, 0, 255); //map our speed to 0-255 range
      digitalWrite(in1, LOW);
      analogWrite(enable1, pwm);
      Serial.print(" motor speed ");
      Serial.println(pwm);
  }
   else if(rc4 > 1805){
      pwm = map(rc4, 1920, 2000, 0, 255); //map our speed to 0-255 range
      digitalWrite(in1, HIGH);
      analogWrite(enable1, pwm);
      Serial.print(" motor speed ");
      Serial.println(pwm);
  }
  delay(10);
}