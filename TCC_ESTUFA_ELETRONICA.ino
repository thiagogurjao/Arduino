/* 
 * PROJETO ESTUFA ELETRÔNICA: CULTIVO INTELIGENTE DO TOMATE-CEREJA
 * TRABALHO DE CONCLUSÃO DE CURSO - ENGENHARIA ELETRÔNICA - CEFET/RJ
 * IVAN AZEVEDO BARROSO E THIAGO GURJÃO DE SANT'ANA
 * 
 * DISPLAY LCD 16X2
 * VSS ---- GND
 * VDD ---- 5V
 * V0 ----- PINO CENTRAL POTENCIÔMETRO
 * RS ----- 02 ARDUINO
 * RW ----- GND
 * E ------ 03 ARDUINO
 * D0 ----- X
 * D1 ----- X
 * D2 ----- X
 * D3 ----- X
 * D4 ----- 04 ARDUINO
 * D5 ----- 05 ARDUINO
 * D6 ----- 06 ARDUINO
 * D7 ----- 07 ARDUINO
 * A ------ 5V
 * K ------ GND
 * 
 * POTENCIÔEMTRO 10K
 * ESQ ---- GND
 * MEI ---- V0 DISPLAY LCD
 * DIR ---- VCC
 * 
 * SENSOR DHT11
 * P1 ----- VCC
 * P2 ----- A0
 * P3 ----- X
 * P4 ----- GND
 * 
 * COOLER 5V
 * VCC ---- 30
 * GND ---- GND
 * 
 * LDR COM RESISTOR 10K
 * P1 ----- VCC
 * P2 ----- 10K
 * P2 ----- A2
 * 10K ---- GND
 * 
 * LEDS
 * VCC ---- 40
 * GND ---- 200 OHMS
 * 200 ---- GND
 * 
 * HIGROMETRO
 * AO ----- PINO A1
 * D0 ----- X
 * GND ---- GND
 * VCC ---- 5V
 * 
 * BOMBA
 * VCC ---- 50
 * GND ---- GND
 *  
 */

// PROGRAMA PROJETO ESTUFA ELETRÔNICA

// DECLARAÇÕES DO DISPLAY LCD
#include <LiquidCrystal.h>  // INCLUINDO BIBLIOTECA DO DISPLAY LCD
LiquidCrystal lcd (2, 3, 4, 5, 6, 7);  // DECLARANDO ENTRADAS DO DISPLAY LCD


// DECLARAÇÕES DO SISTEMA DE TEMPERATURA
#include <dht.h>  // INCLUINDO BIBLIOTECA DO DHT11
dht DHT;  // DECLARANDO O DHT11 COMO UM OBJETO
int COOLER = 30;  // DECLARANDO O COOLER NO PINO 30
int TEMP_MAX = 26;  // DEFININDO A TEMPERATURA IDEAL COMO 26 GRAUS


// DECLARAÇÕES DO SISTEMA DE ILUMINAÇÃO
#define pinoLDR A1  // DECLARANDO ENTRADA ANALÓGICA DO LDR
int valorLDR = 0;  // ZERANDO A VARIÁVEL DE MEDIÇÃO DO LDR
int ILUM = 0;  // DEFININDO VARIÁVEL QUE RECEBE A % DA ILUMINAÇÃO
int LED = 40;  // DECLARANDO O LED NO PINO 40 
int ILUM_MIN = 30; // DEFININDO A ILUMINAÇÃO MÍNIMA COMO 30%


// DECLARAÇÕES DO SISTEMA DE IRRIGAÇÃO
#define pinoHIGRO A2  // DECLARANDO ENTRADA ANALÓGICA DO HIGROMETRO
int valorHIGRO = 0;  // ZERANDO A VARIÁVEL DE MEDIÇÃO DO HIGROMETRO
int UMID = 0;  // DEFININDO VARIÁVEL QUE RECEBE A % DA UMIDADE 
int BOMBA = 50;  // DECLARANDO A BOMBA NO PINO 50
int UMID_MIN = 40;  // DEFININDO A UMIDADE MÍNIMA COMO 40%



void setup() {  
  // INICIALIZAÇÃO DO DISPLAY LCD
  lcd.begin(16,2);  // ATIVANDO O DISPLAY

  // INICIALIZAÇÃO DO SISTEMA DE TEMPERATURA
  pinMode(COOLER, OUTPUT);  // DEFININDO O COOLER COMO SAÍDA

  // INICIALIZAÇÃO DO SISTEMA DE ILUMINAÇÃO
  pinMode(pinoLDR, INPUT);  // DECLARANDO O LDR COMO ENTRADA
  pinMode(LED, OUTPUT);  // DECLARANDO O LED COMO SAÍDA
  
  // INICIALIZAÇÃO DO SISTEMA DE IRRIGAÇÃO
  pinMode(pinoHIGRO, INPUT);  // DEFININDO O HIGROMETRO COMO ENTRADA
  pinMode(BOMBA, OUTPUT);  // DEFININDO A BOMBA COMO SAÍDA

  // DESLIGANDO OS ATUADORES
  digitalWrite(COOLER, HIGH);
  digitalWrite(LED, HIGH);
  digitalWrite(BOMBA, HIGH);
}



void loop() {  
  // CICLO DO DISPLAY LCD
  lcd.clear();  // LIMPANDO O TEXTO ANTERIOR
  lcd.setCursor(0,0);  // POSICIONANDO O CURSOR
  lcd.print("PROJETO ESTUFA");  // IMPRIMINDO
  lcd.setCursor(0, 1);  // POSICIONANDO O CURSOR
  lcd.print("ELETRONICA");  // IMPRIMINDO
  delay(2000);  // AGUARDANDO 2 SEGUNDOS

  
  // CICLO DO SISTEMA DE TEMPERATURA
  DHT.read11(A0);  // INICIANDO A LEITURA DO DHT11 NA ENTRADA A0
  float TEMP = DHT.temperature;  // FAZENDO A MEDIÇÃO DA TEMPERATURA
  
  if (TEMP > TEMP_MAX) {  // CASO A TEMPERATURA ESTEJA ALTA
    digitalWrite(COOLER, LOW);  // LIGANDO O COOLER 
    lcd.clear();  // LIMPANDO O TEXTO ANTERIOR
    lcd.setCursor(0,0);  // POSICIONANDO O CURSOR
    lcd.print("TEMPERATURA= ");  // IMPRIMINDO
    lcd.setCursor(12,0);  // POSICIONANDO O CURSOR
    lcd.print(TEMP,0);  // IMPRIMINDO
    lcd.setCursor(14,0);  // POSICIONANDO O CURSOR
    lcd.print((char)223);  // IMPRIMINDO
    lcd.setCursor(15,0);  // POSICIONANDO O CURSOR
    lcd.print("C");  // IMPRIMINDO
    lcd.setCursor(0,1);  // POSICIONANDO O CURSOR
    lcd.print("COOLER LIGADO");  // IMPRIMINDO
    delay(2000);  // AGUARDANDO 2 SEGUNDOS
  }
  else {  // CASO A TEMPERATURA ESTEJA BAIXA
    digitalWrite(COOLER, HIGH);  // DESLIGANDO O COOLER 
    lcd.clear();  // LIMPANDO O TEXTO ANTERIOR
    lcd.setCursor(0,0);  // POSICIONANDO O CURSOR
    lcd.print("TEMPERATURA= ");  // IMPRIMINDO
    lcd.setCursor(12,0);  // POSICIONANDO O CURSOR
    lcd.print(TEMP,0);  // IMPRIMINDO
    lcd.setCursor(14,0);  // POSICIONANDO O CURSOR
    lcd.print((char)223);  // IMPRIMINDO
    lcd.setCursor(15,0);  // POSICIONANDO O CURSOR
    lcd.print("C");  // IMPRIMINDO
    lcd.setCursor(0,1);  // POSICIONANDO O CURSOR
    lcd.print("COOLER DESLIGADO");  // IMPRIMINDO
    delay(2000);  // AGUARDANDO 2 SEGUNDOS
  }

  
  // CICLO DO SISTEMA DE ILUMINAÇÃO
  valorLDR = analogRead(pinoLDR);  // FAZENDO A MEDIÇÃO DA ILUMINAÇÃO
  ILUM = map(valorLDR, 0, 1023, 0, 100);  // MAPEANDO O VALOR ANALÓGICO PARA %
  
  if (ILUM < ILUM_MIN) {  // CASO A ILUMINAÇÃO ESTEJA BAIXA
    digitalWrite(LED,LOW);  // LIGANDO O CONJUNTO DE LEDS
    lcd.clear();  // LIMPANDO O TEXTO ANTERIOR
    lcd.setCursor(0,0);  // POSICIONANDO O CURSOR
    lcd.print("ILUMINACAO =");  // IMPRIMINDO
    lcd.setCursor(13,0);  // POSICIONANDO O CURSOR
    lcd.print(ILUM);  // IMPRIMINDO
    lcd.setCursor(15,0);  // POSICIONANDO O CURSOR
    lcd.print("%");  // IMPRIMINDO
    lcd.setCursor(0,1);  // POSICIONANDO O CURSOR
    lcd.print("LED LIGADO");  // IMPRIMINDO
    delay(2000);  // AGUARDANDO 2 SEGUNDOS
  }
  else {  // CASO A ILUMINAÇÃO ESTEJA ALTA
    digitalWrite(LED,HIGH);  // DESLIGANDO O CONJUNTO DE LEDS
    lcd.clear();  // LIMPANDO O TEXTO ANTERIOR
    lcd.setCursor(0,0);  // POSICIONANDO O CURSOR
    lcd.print("ILUMINACAO =");  // IMPRIMINDO
    lcd.setCursor(13,0);  // POSICIONANDO O CURSOR
    lcd.print(ILUM);  // IMPRIMINDO
    lcd.setCursor(15,0);  // POSICIONANDO O CURSOR
    lcd.print("%");  // IMPRIMINDO
    lcd.setCursor(0,1);  // POSICIONANDO O CURSOR
    lcd.print("LED DESLIGADO");  // IMPRIMINDO
    delay(2000);  // AGUARDANDO 2 SEGUNDOS
  }


  // CICLO DO SISTEMA DE IRRIGAÇÃO
  valorHIGRO = analogRead(pinoHIGRO);  // FAZENDO A MEDIÇÃO DA UMIDADE DO SOLO
  UMID = map(valorHIGRO, 0, 1023, 100, 0);  // MAPEANDO O VALOR ANALÓGICO PARA %
  
  if (UMID < UMID_MIN) {  // CASO A UMIDADE ESTEJA BAIXA
    digitalWrite(BOMBA, LOW);  // LIGANDO A BOMBA
    lcd.clear();  // LIMPANDO O TEXTO ANTERIOR
    lcd.setCursor(0,0);  // POSICIONANDO O CURSOR
    lcd.print("UMIDADE = ");  // IMPRIMINDO
    lcd.setCursor(10,0);  // POSICIONANDO O CURSOR
    lcd.print(UMID);  // IMPRIMINDO
    lcd.setCursor(12,0);  // POSICIONANDO O CURSOR
    lcd.print("%");  // IMPRIMINDO
    lcd.setCursor(0,1);  // POSICIONANDO O CURSOR
    lcd.print("BOMBA LIGA 2 SEG");  // IMPRIMINDO
    delay(2000);  // AGUARDANDO 2 SEGUNDOS
    digitalWrite(BOMBA, HIGH);  // DESLIGANDO A BOMBA
  }
  else {  // CASO A UMIDADE ESTEJA ALTA
    digitalWrite(BOMBA, HIGH);  // DESLIGANDO A BOMBA
    lcd.clear();  // LIMPANDO O TEXTO ANTERIOR
    lcd.setCursor(0,0);  // POSICIONANDO O CURSOR
    lcd.print("UMIDADE = ");  // IMPRIMINDO
    lcd.setCursor(10,0);  // POSICIONANDO O CURSOR
    lcd.print(UMID);  // IMPRIMINDO
    lcd.setCursor(12,0);  // POSICIONANDO O CURSOR
    lcd.print("%");  // IMPRIMINDO
    lcd.setCursor(0,1);  // POSICIONANDO O CURSOR
    lcd.print("BOMBA DESLIGADA");  // IMPRIMINDO
    delay(2000);  // AGUARDANDO 2 SEGUNDOS
  }
}
