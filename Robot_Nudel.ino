// Piny czujników IR
#define IR_Lewy 8
#define IR_Srodek_Lewy 7
#define IR_Srodek_Prawy 4
#define IR_Prawy 2

// Piny silników
#define LIN1 5
#define LIN2 3
#define RIN1 9
#define RIN2 6

void setup() {
  pinMode(IR_Lewy, INPUT);
  pinMode(IR_Srodek_Lewy, INPUT);
  pinMode(IR_Srodek_Prawy, INPUT);
  pinMode(IR_Prawy, INPUT);

  pinMode(LIN1, OUTPUT);
  pinMode(LIN2, OUTPUT);
  pinMode(RIN1, OUTPUT);
  pinMode(RIN2, OUTPUT);

  digitalWrite(LIN1, LOW);
  digitalWrite(LIN2, LOW);
  digitalWrite(RIN1, LOW);
  digitalWrite(RIN2, LOW);

  Serial.begin(9600);
  Serial.println("Start");
}

void loop() {
  // Algorytm sterowania
  if (digitalRead(IR_Srodek_Prawy) == HIGH && digitalRead(IR_Srodek_Lewy) == HIGH && digitalRead(IR_Prawy) == HIGH && digitalRead(IR_Lewy) == HIGH) {
    stop();
  } else if (digitalRead(IR_Srodek_Prawy) == HIGH && digitalRead(IR_Srodek_Lewy) == HIGH) {
    doPrzodu();
  } else if (digitalRead(IR_Srodek_Prawy) == HIGH) {
    lekkoLewo();
  } else if (digitalRead(IR_Srodek_Lewy) == HIGH) {
    lekkoPrawo();
  } else if (digitalRead(IR_Prawy) == HIGH) {
    lewo();
  } else if (digitalRead(IR_Lewy) == HIGH) {
    prawo();
  } else {
    stop();
  }

}

// Sterowanie
void doPrzodu () {
  analogWrite(LIN1, 50);
  analogWrite(RIN1, 50);
  digitalWrite(LIN2, LOW);
  digitalWrite(RIN2, LOW);
  delay(0);
}

void lekkoPrawo() {
  analogWrite(LIN1, 80);
  analogWrite(RIN1, 0);
  digitalWrite(LIN2, LOW);
  digitalWrite(RIN2, LOW);
  delay(0);
}

void lekkoLewo() {
  analogWrite(LIN1, 0);
  analogWrite(RIN1, 80);
  digitalWrite(LIN2, LOW);
  digitalWrite(RIN2, LOW);
  delay(0);
}

void lewo(){
  analogWrite(LIN2, 100);
  analogWrite(RIN1, 110);
  digitalWrite(LIN1, LOW);
  digitalWrite(RIN2, LOW);
  delay(0);
}

void prawo(){
  analogWrite(LIN1, 110);
  analogWrite(RIN2, 100);
  digitalWrite(LIN2, LOW);
  digitalWrite(RIN1, LOW);
  delay(0);
}

void stop() {
  digitalWrite(LIN1, LOW);
  digitalWrite(LIN2, LOW);
  digitalWrite(RIN1, LOW);
  digitalWrite(RIN2, LOW);

}