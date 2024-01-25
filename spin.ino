#define button  34
#define a 26
#define b 32
#define c 33
#define d 25
const int STEPS = 2056;
int pins[]={a,b,c,d};
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(button, INPUT);
  pinMode(a, OUTPUT);
  pinMode(b, OUTPUT);
  pinMode(c, OUTPUT);
  pinMode(d, OUTPUT);
}
int currentStep=0;
int currentMotor=0;
void loop() {
  // put your main code here, to run repeatedly:
  if(digitalRead(button)==HIGH){
    currentStep = 0;
    while(currentStep<STEPS){
      currentMotor = currentStep % 4;
      digitalWrite(pins[currentMotor],HIGH);
      delay(2);
      digitalWrite(pins[currentMotor],LOW);
      currentStep++;
    }
    Serial.print("Current Step : ");
    Serial.println(currentStep);
  }
}
