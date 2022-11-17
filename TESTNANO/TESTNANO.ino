#include <Servo.h>

#define PIN_TRIG A0
#define PIN_ECHO1 A1
#define PIN_ECHO2 A2
#define PIN_ECHO3 A3
#define PIN_ECHO4 A4
#define buz A4
#define servoPin1 A5
#define servoPin2 A6

Servo Servo1;
Servo Servo2;

long duration1, cm1, duration2, cm2, duration3, cm3, duration4, cm4;

void setup() {

  // Инициализируем взаимодействие по последовательному порту

  Serial.begin (9600);
  //Определяем вводы и выводы
  pinMode(PIN_TRIG, OUTPUT);
  pinMode(PIN_ECHO1, INPUT);
  pinMode(PIN_ECHO2, INPUT); 
  pinMode(PIN_ECHO3, INPUT); 
  pinMode(PIN_ECHO4, INPUT);

  Servo1.attach(servoPin1);
  Servo2.attach(servoPin2);
}

void buzzer()
{
    for(int i=0;i<50;i++)
    {
    digitalWrite(buz,HIGH);
    delay(1);
    digitalWrite(buz,LOW);
    delay(1);
    }
    delay(50);
    for(int i=0;i<50;i++)
    {
    digitalWrite(buz,HIGH);
    delay(1);
    digitalWrite(buz,LOW);
    delay(1);
    }
}

void loop() {

  // Сначала генерируем короткий импульс длительностью 2-5 микросекунд.

  digitalWrite(PIN_TRIG, LOW);
  delayMicroseconds(5);
  digitalWrite(PIN_TRIG, HIGH);

  // Выставив высокий уровень сигнала, ждем около 10 микросекунд. В этот момент датчик будет посылать сигналы с частотой 40 КГц.
  delayMicroseconds(10);
  digitalWrite(PIN_TRIG, LOW);

  //  Время задержки акустического сигнала на эхолокаторе.
  duration1 = pulseIn(PIN_ECHO1, HIGH);
  duration2 = pulseIn(PIN_ECHO2, HIGH);
  duration3 = pulseIn(PIN_ECHO3, HIGH);
  duration4 = pulseIn(PIN_ECHO4, HIGH);

  // Теперь осталось преобразовать время в расстояние
  cm1 = (duration1 / 2) / 29.1;
  cm2 = (duration2 / 2) / 29.1;
  cm3 = (duration3 / 2) / 29.1;
  cm4 = (duration4 / 2) / 29.1;

  if(cm1<5 or cm2<5 or cm3<5 or cm4<5) {
    buzzer();
    if (cm1<5) {
      Servo1.write();
    }
  }
  Serial.print(cm1);
    

  // Задержка между измерениями для корректной работы скеча
  delay(250);
}
