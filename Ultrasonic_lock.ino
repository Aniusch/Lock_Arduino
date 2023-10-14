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
int val;  // Adicionada a declaração da variável val

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(tooFarPin, OUTPUT);
  pinMode(relay, OUTPUT);
  pinMode(esp, INPUT);
  pinMode(closedButton, INPUT);
  Serial.begin(9600);
  prodZero = 5;
  isOpen = 0;  // Inicialização de isOpen
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
  } else {
    digitalWrite(relay, LOW);
  }

  if (digitalRead(closedButton) == HIGH) {
    isOpen = 0;
  } else {
    int cont = 0;
    if (distance > (prodZero + 5)) {
      cont++;
    }
    if (distance > (prodZero + 10)) {
      cont++;
    }
    if (distance > (prodZero + 15)) {
      cont++;  // Corrigido para cont em vez de Cont
    }
    Serial.print("Contador: ");  // Mensagem de depuração
    Serial.println(cont);  // Alterado para Serial.println para visualização de texto
  }

  delay(10);
}