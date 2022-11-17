#include <Servo.h>

#define PIN_TRIG A0  //подача сигнала на все датчики дистанции
#define PIN_ECHO1 A1 //вход датчика дистанции 1
#define PIN_ECHO2 A2 //вход датчика дистанции 2
#define PIN_ECHO3 A3 //вход датчика дистанции 3
#define PIN_ECHO4 A4 //вход датчика дистанции 4

#define buz A4       //пищалка

#define servoPin1 A5 //серва вращения1
#define servoPin2 A6 //серва вращения2
#define servoPin3 A7 //серва сброса мусора

#define L1 4 //индикаторные светодиоды
#define L2 5
#define L3 6
#define L4 7

int l = 10; //расстояние до руки


Servo Servo1; //обЪявление сервопривода
Servo Servo2; 
Servo Servo3; 

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
  Servo3.attach(servoPin3);

  pinMode(L1, OUTPUT);
  pinMode(L2, OUTPUT);
  pinMode(L3, OUTPUT);
  pinMode(L4, OUTPUT);
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

void lamp(int x){
  digitalWrite(x,HIGH);
  delay(300);
  digitalWrite(x,LOW);
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

  if(cm1<l or cm2<l or cm3<l or cm4<l) {
    buzzer();
    Servo3.write(90);
    if (cm1<l) {
      Servo1.write(0); //0
      Servo2.write(0);
      lamp(L1);
      Servo3.write(0);
      //cm1=100;
    } else if (cm2<l) {
      Servo1.write(90); //90
      Servo2.write(0);
      lamp(L2);
      Servo3.write(0);
      //cm2=100;
    } else if (cm3<l) {
      Servo1.write(180); //180
      Servo2.write(0);
      lamp(L3);
      Servo3.write(0);
      //cm3=100;
    } else if (cm4<l) {
      Servo1.write(180); //270
      Servo2.write(90);
      lamp(L4);
      Servo3.write(0);
      //cm4=100;
    }
    
    
    
  }
  Serial.print(cm1);
  //Servo3.write(0);  

  // Задержка между измерениями для корректной работы скеча
  delay(150);
}
