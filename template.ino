#define a 26
void setup() {
  // put your setup code here, to run once:
  pinMode(a, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(a,HIGH);
  delay(5000);  
  digitalWrite(a,LOW);
  delay(5000);

}
