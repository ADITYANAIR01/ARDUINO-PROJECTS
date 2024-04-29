# define MQ2 A0
# define LED 3

void setup(){
  pinMode(MQ2 , INPUT);
  pinMode(LED, OUTPUT);

}

void loop(){
  Serial.begin(9600);
  Serial.println(analogRead(MQ2));
 int gasstatus = analogRead(MQ2);
 if(gasstatus <=100 ){
  Serial.println("THERE IS NO GAS LEAK :) ");
  digitalWrite(LED, LOW);
  delay(1000);
 }

 else {
  Serial.println("THERE IS GAS LEAK !!! ");
  digitalWrite(LED, HIGH);
  delay(1000);
 }
}