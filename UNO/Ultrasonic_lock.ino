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
int val;  

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(tooFarPin, OUTPUT);
  pinMode(relay, OUTPUT);
  pinMode(esp, INPUT);
  pinMode(closedButton, INPUT);
  Serial.begin(115200);
  prodZero = 5;
  isOpen = 0; 
}

void loop() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  distance = (duration*.0343)/2;

  val = digitalRead(esp);
  if (val == HIGH) {
    isOpen = 1;
    digitalWrite(relay, HIGH);
    //delay(100) 
  } else {
    digitalWrite(relay, LOW);
    isOpen = 0;
  }

  if (digitalRead(closedButton) == HIGH) {
    isOpen = 0;
  } else if(isOpen == 1){
    int cont = 0;
    if (distance > (prodZero + 5)) {
      cont++;
    }
    if (distance > (prodZero + 10)) {
      cont++;
    }
    if (distance > (prodZero + 15)) {
      cont++;  
    }
    Serial.print("Contador: "); 
    Serial.println(cont);  
  }

  delay(50);
}
