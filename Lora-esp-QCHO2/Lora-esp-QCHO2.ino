
#define led 4
#define sirena 5
#define swiche 6

byte val;
byte refle;
byte z1;
byte bandera;

void setup() {
  Serial.begin(115200);
  pinMode(led,OUTPUT);
  pinMode(sirena,OUTPUT);
  pinMode(swiche,INPUT_PULLUP);

  bandera=0;
}

void loop() {
  // put your main code here, to run repeatedly:
if(Serial.available()){
  val=Serial.read();
  Serial.print("Valor lect serial: ");
  Serial.println(val);
  switch (val){
    case 49:
      digitalWrite(led,1);
      break;
    case 50:
      digitalWrite(led, 0);
      break;
    case 51:
      digitalWrite(sirena, 1);
      break;
    case 52:
      digitalWrite(sirena, 0);
      break;
  }  
}
  z1=digitalRead(swiche);

  if(z1==1 && bandera==1){
    Serial.println("11");
    bandera=0;
    delay(1000);
  }else if(z1==0 && bandera==0){
    Serial.println("10");
    bandera=1;
    delay(1000);
  }



}
