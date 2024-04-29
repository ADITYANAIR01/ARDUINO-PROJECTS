# define  FIREPIN 2
# define LED 3 

void setup(){
  pinMode(FIREPIN, INPUT);
  pinMode(LED, OUTPUT);

}

void loop() {
  Serial.begin(9600);
 char firestatus = digitalRead(FIREPIN);
  if(firestatus == LOW){
    Serial.println("THERE IS FIRE !!! ");
    digitalWrite(LED, HIGH);
    delay(2000);
  }
  else{
    Serial.println("There is no fire :)  ");
    digitalWrite(LED, LOW);
    delay(2000);
  }
}