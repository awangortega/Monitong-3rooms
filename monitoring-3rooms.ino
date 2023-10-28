#define BLYNK_PRINT Serial
#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
#include <Wire.h>

BlynkTimer timer;

char auth[] =   //alamat blynk
char ssid[] =   //nama WiFi
char pass[] =   //password WiFi

int pir1 = 23;
int pir2 = 4;
int pir3 = 35;
int ldr1 = 34;
int ldr2 = 36;
int ldr3 = 39;
int r1 = 25;  //For kamar 1
int r2 = 16;  //For kamar 2
int r3 = 27;  //For kamar 3
int r4 = 26;  //For kamar 1
int r5 = 17;  //For kamar 2
int r6 = 14;  //For kamar 3
int idkamar1 =5;
int idkamar2 =13;
int idkamar3 =12;
int npir1, npir2, npir3,
    nldr1, nldr2, nldr3;
int IN1, IN2, IN3;
String info1, info2, info3;


void setup (){
  pinMode(pir1,INPUT);
  pinMode(pir2,INPUT);
  pinMode(pir3,INPUT);
  pinMode(ldr1,INPUT);
  pinMode(ldr2,INPUT);
  pinMode(ldr3,INPUT);
  pinMode(r1,OUTPUT);
  pinMode(r2,OUTPUT);
  pinMode(r3,OUTPUT);
  pinMode(r4,OUTPUT);
  pinMode(r5,OUTPUT);
  pinMode(r6,OUTPUT);
  pinMode(idkamar1,OUTPUT);
  pinMode(idkamar2,OUTPUT);
  pinMode(idkamar3,OUTPUT);
  
  Serial.begin(115200);
  Blynk.begin(auth, ssid, pass);
  timer.setInterval(1000L,senddata);

  
}

void senddata(){  
  Blynk.virtualWrite(V0, npir1);
  Blynk.virtualWrite(V1, npir2);
  Blynk.virtualWrite(V2, npir3);
  Blynk.virtualWrite(V3, nldr1);
  Blynk.virtualWrite(V4, nldr2);
  Blynk.virtualWrite(V5, nldr3);
  Blynk.virtualWrite(V6,IN1);
  Blynk.virtualWrite(V7,IN2);
  Blynk.virtualWrite(V8,IN3);
}

void Out(){
  if (npir1 == 1){
  digitalWrite(r1,LOW);
  delay (1000);
  }
  else{
    digitalWrite(r1,HIGH);
    delay(100);
  }
  if (npir2 == 1){
    digitalWrite(r2,LOW);
    delay (1000);
  }
  else{
    digitalWrite(r2,HIGH);
    delay(100);
  }
  if (npir3 == 1){
    digitalWrite(r3,LOW);
    delay (100);
  }
  else{
    digitalWrite(r3,HIGH);
    delay(1000);
  }
  
  //pengkodean sensor ldr
  if (nldr1 > 90){
    digitalWrite(r4,HIGH);
  }
  else{
    digitalWrite(r4,LOW);
  }
  if (nldr2 > 90){
    digitalWrite(r5,HIGH);
  }
  else{
    digitalWrite(r5,LOW);
  }
  if (nldr3 > 90){
    digitalWrite(r6,HIGH);
  }
  else{
    digitalWrite(r6,LOW);
  }
}

void kondisi1(){
  //Tidak ada orang tapi mendeteksi cahaya
  if (digitalRead(r1)==HIGH && digitalRead(r4)==HIGH){ 
    digitalWrite(idkamar1,HIGH);
  }
  else if(digitalRead(r1)==HIGH && digitalRead(r4)==LOW){
    digitalWrite(idkamar1,LOW);
  }
  else if(digitalRead(r1)==LOW && digitalRead(r4)==HIGH){
    digitalWrite(idkamar1,HIGH);
  }
  else{
    digitalWrite(idkamar1,HIGH);
  }
}
void kondisi2(){
  if (digitalRead(r2)==HIGH && digitalRead(r5)==HIGH){
    digitalWrite(idkamar2,HIGH);
  }
  else if(digitalRead(r2)==HIGH && digitalRead(r5)==LOW){
    digitalWrite(idkamar2,LOW);
  }
  else if(digitalRead(r2)==LOW && digitalRead(r5)==HIGH){
    digitalWrite(idkamar2,HIGH);
  }
  else{
    digitalWrite(idkamar2,HIGH);
  }
}
void kondisi3(){
  if (digitalRead(r3)==HIGH && digitalRead(r6)==HIGH){
    digitalWrite(idkamar3,HIGH);
  }
  else if(digitalRead(r3)==HIGH && digitalRead(r6)==LOW){
    digitalWrite(idkamar3,LOW);
  }
  else if(digitalRead(r3)==LOW && digitalRead(r6)==HIGH){
    digitalWrite(idkamar3,HIGH);
  }
  else{
    digitalWrite(idkamar3,HIGH);
  }
}
void lamp(){
  //Program untuk berubah type data menjadi bentuk biner
    if (digitalRead(idkamar1) == HIGH){
      IN1 = 1;
      info1 = "NYALA";
    }
    else{
      IN1 = 0;
      info2 = "MATI";
    }
    if (digitalRead(idkamar2) == HIGH){
      IN2 = 1;
      info2 = "NYALA";
    }
    else{
      IN2 = 0;
      info2 = "MATI";
    }
    if (digitalRead(idkamar3) == HIGH){
      IN3 = 1;
      info3 = "NYALA";
    }
    else{
      IN3 = 0;
      info3 = "MATI";
    }  
}

void loop(){
  timer.run();
  Blynk.run();
  Out();
  kondisi1();
  kondisi2();
  kondisi3();
  lamp();
  npir1 = digitalRead(pir1);
  npir2 = digitalRead(pir2);
  npir3 = digitalRead(pir3);
  nldr1 = analogRead(ldr1)/40.95;
  nldr2 = analogRead(ldr2)/40.95;
  nldr3 = analogRead(ldr3)/40.95;
  Serial.print("nilai pir1 =");
  Serial.println(npir1);
  Serial.print("nilai pir2 =");
  Serial.println(npir2);
  Serial.print("nilai pir3 =");
  Serial.println(npir3);
  Serial.print("nilai ldr1 =");
  Serial.println(nldr1);
  Serial.print("nilai ldr2 =");
  Serial.println(nldr2);
  Serial.print("nilai ldr3 =");
  Serial.println(nldr3);
  Serial.println("");
  Serial.print("Kondisi Kamar 1 : ");
  Serial.println(info1);
  Serial.print("Kondisi Kamar 2 : ");
  Serial.println(info2);   
  Serial.print("Kondisi Kamar 3 : ");
  Serial.println(info3);
  Serial.println("*****************************************************");        
}
