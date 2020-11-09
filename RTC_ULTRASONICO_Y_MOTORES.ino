//entradas de motores
int IN1=8;
int IN2=7;
int ENA=9;
int IN3=13;
int IN4=12; 
int ENB=11;
//entradas de ultrasonico
int trigger=5;
int echo=3;
long tiempo_de_espera;
long distancia;
//rtc
#include <Wire.h>
#include <RTClib.h>
RTC_DS3231 rtc;

bool inicio=true;
bool fin=true;


void setup() 
{
  //motores
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(ENA, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(ENB, OUTPUT);
  //ultrasonico
  Serial.begin(9600);
  pinMode(trigger, OUTPUT);
  pinMode(echo, INPUT);
  //rtc
  //Wire.begin();
  if(! rtc.begin())
  {
    Serial.println("Modulo RTC no encontrado!");
    while(1);
  }
    rtc.adjust(DateTime(2020,11,8,20,55,0));
}


void loop() 
{
  long tiempo_de_espera=0;
  long distancia=0;

  digitalWrite(trigger, LOW);   
  delayMicroseconds(5);
  digitalWrite(trigger, HIGH);   
  delayMicroseconds(10);
  digitalWrite(trigger, LOW);   
  tiempo_de_espera=pulseIn(echo,HIGH);
  distancia = tiempo/58;

  Serial.print(distancia);
  Serial.println("cm");
  delay(1000);
  //////////////
  if(distancia>30 && distancia<400)
  //motores
  {
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, LOW);
    analogWrite(ENA, 0);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, LOW);
    analogWrite(ENB, 0);
    
  }
  else if(distancia>8 && distancia<30)
  {
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    analogWrite(ENA, 155);
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
    analogWrite(ENB, 255);
  }  
  //rtc
  DateTime fecha= rtc.now();
  //rtc definiendo la hora de encendido y apagado del alimentador
  if(fecha.hour()== 6 && fecha.minute()== 0)
  {
    if(inicio == true)
    {
      digitalWrite(IN1, HIGH);
      digitalWrite(IN2, LOW);
      analogWrite(ENA, 155);
      digitalWrite(IN3, HIGH);
      digitalWrite(IN4, LOW);
      analogWrite(ENB, 255);
      delay(2000);
      analogWrite(ENB, 180);
      delay(3000);
      analogWrite(ENB, 90);
      delay(2000),
      Serial.println("Alimentador encendido");
      inicio=false;
    }
  }
  if(fecha.hour()==6 && fecha.minute()== 15)
  {
    if(fin==true)
    {
      digitalWrite(IN1, LOW);
      digitalWrite(IN2, LOW);
      analogWrite(ENA, 0);
      digitalWrite(IN3, LOW);
      digitalWrite(IN4, LOW);
      analogWrite(ENB, 0);
      Serial.println("Alimentador apagado");
      fin= false;
    }
  }

  Serial.print(fecha.day());
  Serial.print("/");
  Serial.print(fecha.month());
  Serial.print("/");
  Serial.print(fecha.year());
  Serial.print(" ");
  Serial.print(fecha.hour());
  Serial.print(":");
  Serial.print(fecha.minute());
  Serial.print(":");
  Serial.print(fecha.second());
  Serial.println();
  delay(1000);

    
  if(fecha.hour()==17 && fecha.minute()==0)
  {
    if(inicio== true)
    {
      digitalWrite(IN1, HIGH);
      digitalWrite(IN2, LOW);
      analogWrite(ENA, 155);
      digitalWrite(IN3, HIGH);
      digitalWrite(IN4, LOW);
      analogWrite(ENB, 255);
      delay(2000);
      analogWrite(ENB, 180);
      delay(3000);
      analogWrite(ENB, 90);
      delay(2000);
      Serial.println("Alimentador encendido");
      inicio=false;
     }
   }
   if(fecha.hour()==17 && fecha.minute()== 15)
   {
     if(fin==true)
     {
       digitalWrite(IN1, LOW);
       digitalWrite(IN2, LOW);
       analogWrite(ENA, 0);
       digitalWrite(IN3, LOW);
       digitalWrite(IN4, LOW);
       analogWrite(ENB, 0);
       Serial.println("Alimentador apagado");
       fin= false;
     }
   }
 
  Serial.print(fecha.day());
  Serial.print("/");
  Serial.print(fecha.month());
  Serial.print("/");
  Serial.print(fecha.year());
  Serial.print(" ");
  Serial.print(fecha.hour());
  Serial.print(":");
  Serial.print(fecha.minute());
  Serial.print(":");
  Serial.print(fecha.second());
  Serial.println();
  delay(1000);

  if(fecha.hour()==1 && fecha.minute()== 0)
  {
    inicio=true;
    fin=true;
  }
}
