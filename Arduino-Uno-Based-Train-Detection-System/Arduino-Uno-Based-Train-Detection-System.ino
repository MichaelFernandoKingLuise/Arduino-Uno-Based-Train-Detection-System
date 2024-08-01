#include <Servo.h>

Servo myservo1;
Servo myservo2;

int pos = 0;
boolean cek1 = 0;
boolean cek2 = 0;
boolean kedip = false;

#define echoPin1 0
#define trigPin1 1
#define echoPin2 2
#define trigPin2 3
#define pinBuzzer1 4
#define pinBuzzer2 5
#define pinServo1 6
#define pinServo2 7
#define pinLed1 8
#define pinLed2 9

void setup() {
  Serial.begin(9600);  //inisialisasi komunikasi serial

  myservo1.attach(pinServo1);
  myservo2.attach(pinServo2);

  pinMode(echoPin1, INPUT);
  pinMode(trigPin1, OUTPUT);
  pinMode(echoPin2, INPUT);
  pinMode(trigPin2, OUTPUT);

  pinMode(pinBuzzer1, OUTPUT);
  pinMode(pinBuzzer2, OUTPUT);

  pinMode(pinLed1, OUTPUT);
  pinMode(pinLed2, OUTPUT);
}

void moveServo(int targetPos) {
  for (int pos = 0; pos <= targetPos; pos += 1) {
    myservo1.write(pos);
    myservo2.write(pos);
    delay(5);
  }
}

void openBarrier() {
  for (int pos = 90; pos >= 0; pos -= 1) {
    myservo1.write(pos);
    myservo2.write(pos);
    delay(5);
  }
}

void kedips() {
  tone(pinBuzzer1, 330);
  digitalWrite(pinLed1, HIGH);
  digitalWrite(pinLed2, HIGH);
  delay(600);
  noTone(pinBuzzer1);
  digitalWrite(pinLed1, LOW);
  digitalWrite(pinLed2, LOW);
  tone(pinBuzzer2, 262);  // Nada G5
  digitalWrite(pinLed1, HIGH);
  digitalWrite(pinLed2, HIGH);
  delay(400);
  noTone(pinBuzzer2);
  digitalWrite(pinLed1, LOW);
  digitalWrite(pinLed2, LOW);
}

void loop() {
  long duration1, duration2, jarak1, jarak2;

  Serial.print("cek 1 TRUE / FALSE : ");
  Serial.println(cek1);
  Serial.println("===============");

  Serial.print("cek 2 TRUE / FALSE : ");
  Serial.println(cek2);
  Serial.println("===============");

  digitalWrite(trigPin1, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin1, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin1, LOW);
  duration1 = pulseIn(echoPin1, HIGH);

  digitalWrite(trigPin2, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin2, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin2, LOW);
  duration2 = pulseIn(echoPin2, HIGH);

  jarak1 = duration1 * 0.034 / 2;
  jarak2 = duration2 * 0.034 / 2;

  Serial.println("Jarak 1 :");
  Serial.print(jarak1);
  Serial.println(" cm");

  Serial.println("Jarak 2 :");
  Serial.print(jarak2);
  Serial.println(" cm");

  if (kedip) {
    kedips();
  }

  // TANPA KAMERA (KERETA DARI SENSOR 1)
  if (jarak1 >= 2 && jarak1 <= 10 && cek2 == 0 && cek1 == 0) {
    cek1 = true;
    kedip = true;

    moveServo(90);
  }

  // TANPA KAMERA (KERETA DARI SENSOR 2)
  if (jarak2 >= 2 && jarak2 <= 10 && cek1 == 0 && cek2 == 0) {
    cek2 = true;
    kedip = true;

    moveServo(90);
  }

  // BUKA PALANG JIKA KERETA DARI 1
  if (jarak2 >= 2 && jarak2 <= 10 && cek1 == 1) {
    noTone(pinBuzzer1);
    noTone(pinBuzzer2);
    delay(1500);
    kedip = false;
  

    digitalWrite(pinLed1, LOW);
    digitalWrite(pinLed2, LOW);

    openBarrier();
    cek1 = 0;
    delay(1500);
  }

  // BUKA PALANG JIKA KERETA DARI 2
  if (jarak1 >= 2 && jarak1 <= 10 && cek2 == 1) {
    noTone(pinBuzzer1);
    noTone(pinBuzzer2);
    delay(1500);
    kedip = false;
    noTone(pinBuzzer1);
    noTone(pinBuzzer2);


    digitalWrite(pinLed1, LOW);
    digitalWrite(pinLed2, LOW);

    openBarrier();
    cek2 = 0;
    delay(1500);
  }

  delay(200);
}
