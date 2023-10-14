// codigo sensor ultrasonico + lock pica

const int trigPin = 10;
const int echoPin = 11;
const int tooFarPin = 9;
const int relay = 7;
const int esp = 8;
int lockState;
int prodZero;
int isOpen;
const int closedButton = 12;

float duration, distance;

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(tooFarPin, OUTPUT);
  pinMode(relay, OUTPUT);
  pinMode(esp, INPUT);
  pinMode(closedButton, INPUT);
  Serial.begin(9600);
  prodZero = 5;
}

void loop() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  distance = (duration*.0343)/2;
  //Serial.print("Distance: ");
  //Serial.println(distance);

  lockState = digitalRead(esp);
  if (lockState == HIGH) {
    isOpen = 1;
    digitalWrite(relay, HIGH);
  } else{
    digitalWrite(relay, LOW);
  }

  if(digitalRead(closedButton) == HIGH){
    isOpen = 0;
  }
  else {
    if(distance > (prodZero + 5)){
        Serial.write('1');
    } 
    if( distance > (prodZero + 10)){
        Serial.write('1');
    } 
    if( distance > (prodZero + 15)){
        Serial.write('1');
    }
    /*
    if( distance > prodZero + 20){

    }
    if( distance > prodZero + 25){

    }
    */
  }
/*
  if(distance >= 10 && lockState == HIGH){
    digitalWrite(tooFarPin, HIGH);
    Serial.write(10);
  }else{
    digitalWrite(tooFarPin, LOW);
  }

  if (lockState == HIGH) {
    digitalWrite(relay, HIGH);
  }
  else{
    digitalWrite(relay, LOW);
  }
*/
  delay(10);
}