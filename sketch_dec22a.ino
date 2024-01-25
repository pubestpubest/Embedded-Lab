#define LDR  35
#define LED  27
int LDR_Value=0;
int thresh_hold_on = 500;
int thresh_hold_off = 700;
void setup() {
  Serial.begin(9600);
  pinMode(LED, OUTPUT);
}

void loop() {
  LDR_Value = analogRead(LDR);
  if(LDR_Value<thresh_hold_on){
    digitalWrite(LED, HIGH);
  }else
  if(LDR_Value>=thresh_hold_off){
    digitalWrite(LED, LOW);
  }

  Serial.print("LDR:");
  Serial.print(LDR_Value);
  Serial.print(",");
  Serial.print("Thresh hold on:");
  Serial.print(thresh_hold_on);
  Serial.print(",");
  Serial.print("Thresh hold off:");
  Serial.println(thresh_hold_off);
  delay(20);
}