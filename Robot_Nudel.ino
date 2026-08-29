// Piny czujników IR
#define IR_Lewy 8
#define IR_Srodek_Lewy 7
#define IR_Srodek_Prawy 4
#define IR_Prawy 2

// Piny silników
#define AIN1 5
#define AIN2 3
#define BIN1 6
#define BIN2 9

void setup() {
  pinMode(IR_Lewy, INPUT);
  pinMode(IR_Srodek_Lewy, INPUT);
  pinMode(IR_Srodek_Prawy, INPUT);
  pinMode(IR_Prawy, INPUT);

  pinMode(AIN1, OUTPUT);
  pinMode(AIN2, OUTPUT);
  pinMode(BIN1, OUTPUT);
  pinMode(BIN2, OUTPUT);

  digitalWrite(AIN1, LOW);
  digitalWrite(AIN2, LOW);
  digitalWrite(BIN1, LOW);
  digitalWrite(BIN2, LOW);

  Serial.begin(9600);
  Serial.println("Start");
}

void loop() {
  doPrzodu();
  delay(1000);
  stop();
  delay(100000);
}

void doPrzodu () {
  analogWrite(AIN1, 150);
  analogWrite(BIN1, 150);
  digitalWrite(AIN2, LOW);
  digitalWrite(BIN2, LOW);
}

void stop() {
  digitalWrite(AIN1, LOW);
  digitalWrite(AIN2, LOW);
  digitalWrite(BIN1, LOW);
  digitalWrite(BIN2, LOW);
}