# define IR_PIN 2

void setup() {
  pinMode(IR_PIN, INPUT);
  Serial.begin(9600);


}

void loop() {
  int ir_status = digitalRead(IR_PIN);
  if(ir_status == 1){
    Serial.println("The door is opened ");
    delay(1000);

  }
  else{
    Serial.println("The door is closed ");
    delay(1000);
  }

}
