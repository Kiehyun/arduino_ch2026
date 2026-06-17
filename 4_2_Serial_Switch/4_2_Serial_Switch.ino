void setup() {
 pinMode(5,INPUT_PULLUP); 
 Serial.begin(9600); 
}

void loop() {
  int d_sig = digitalRead(5); 

  Serial.println(d_sig); 
  delay(50);
}
