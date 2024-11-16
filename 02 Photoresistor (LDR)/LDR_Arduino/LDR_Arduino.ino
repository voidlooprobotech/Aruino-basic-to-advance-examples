
#define LDR A0
#define LIGHT 2
int Threshold = 700;

void setup() {
 Serial.begin(9600);
 pinMode(LIGHT,OUTPUT);

}

void loop() {
  int Value = analogRead(A0);
  Serial.println(Value);
  if(Value >= Threshold)
  {
    digitalWrite(LIGHT, HIGH);
  }
  else
  {
    digitalWrite(LIGHT, LOW);
  }
  delay(500);
 
}
