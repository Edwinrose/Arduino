int ledPin = 2; //GPIO2 (ESP-12E pin D4)
void setup() 
{
  pinMode(ledPin, OUTPUT);
}

void loop()
{
  digitalWrite(ledPin, HIGH); 
  delay(100); 
  digitalWrite(ledPin, LOW); 
  delay(100); 
}
