//the following are all ~PWM capable ports 

int rc = 3;
int pc = 5;

void setup() {
  pinMode(rc, INPUT);
  pinMode(pc, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  
  int pwm = 0;
  int rc4 = pulseIn(rc, HIGH, 25000);
  
  Serial.print("switch: ");
  Serial.print(swd);
  Serial.print(" raw channel4: ");
  Serial.print(rc4);
  
//   if(rc4==0){
//       Serial.println(" no signal");
//       digitalWrite(in1, LOW);
//       digitalWrite(in2, LOW);
//       analogWrite(enable1, 0);
//   }
//   else if(rc4 > 1530){ //right stick
//       pwm = map(rc4, 1530, 2000, 0, 255); //map our speed to 0-255 range
//       digitalWrite(in1, LOW);
//       digitalWrite(in2, HIGH);
//       analogWrite(enable1, pwm);
//       Serial.print(" right stick speed: ");
//       Serial.println(pwm);
//   }
//   else if(rc4 < 1460){
//       pwm = map(rc4, 1460, 1000, 0, 255); //map our speed to 0-255 range
//       digitalWrite(in1, HIGH);
//       digitalWrite(in2, LOW);
//       analogWrite(enable1, pwm);
//       Serial.print(" left stick speed: ");
//       Serial.println(pwm);
//   }else{
//       Serial.println(" stick centered");
//       digitalWrite(in1, LOW);
//       digitalWrite(in2, LOW);
//       analogWrite(enable1, 0);
//   }


  if(rc4==0){
      Serial.println(" no signal");
  }
  else if(rc4 > 1530){ //right stick
      pwm = map(rc4, 1530, 2000, 0, 255); //map our speed to 0-255 range
      Serial.println(pwm);
  }
  else if(rc4 < 1460){
      pwm = map(rc4, 1460, 1000, 0, 255); //map our speed to 0-255 range
      Serial.println(pwm);
  }else{
      Serial.println(" stick centered");
  }
  
  
  delay(10);

}