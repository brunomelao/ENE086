#define pwm 5
#define pinio 6
float sine;
int sine_1i;
void setup() {
  pinMode(pwm, OUTPUT);
  pinMode(pinio, OUTPUT);

}

void loop() {
  for(int i=-180;i<180;i+=1){
    sine=sin(i* (3.1415 / 180));
    sine_1i = 127 + int(sine * 255.0/2.0);
    analogWrite(pwm,sine_1i);
    analogWrite(pinio, sine_1i);
    delay(5);
  }
}
